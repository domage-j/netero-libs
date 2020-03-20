/**
 * Netero sources under BSD-3-Clause
 * see LICENCE.txt
 */

#pragma once

#include <exception>
#include <stdexcept>
#include <functional>
#include <type_traits>
#include <thread>
#include <atomic>
#include <memory>

#include <objbase.h>
#include <Audioclient.h>
#include <audiopolicy.h>
#include <mmdeviceapi.h>
#include <Mmreg.h>
#include <avrt.h>
#include <comdef.h>

#include <netero/audio/audio.hpp>
#include <netero/audio/engine.hpp>

class netero::audio::engine::impl {
private:
	IMMDeviceEnumerator* _d_enumerator = nullptr;
	IMMDevice* _device = nullptr;
	IAudioClient* _audio_client = nullptr;
	IAudioRenderClient* _audio_rendering = nullptr;
	WAVEFORMATEX* _wfx = nullptr;
	WAVEFORMATEXTENSIBLE* _wfx_ext = nullptr;
	HANDLE _event = nullptr;
	HANDLE _task = nullptr;
	REFERENCE_TIME _latency;
	unsigned _frameCount;

	std::function<void(float*, size_t)> _cb;

	enum state {
		OFF,
		STOP,
		RUNNING,
		TIMEOUT,
		ERR,
	};

	std::atomic<state>	_state = state::OFF;
	std::unique_ptr<std::thread>	_thread;

	//--------------------
	// Helpers
	//--------------------

	void	test_result(HRESULT result) {
		if (FAILED(result)) {
			_com_error	err(result);
			WASAPI_cleanup();
			throw std::runtime_error("WASAPI Error: " + std::string(err.ErrorMessage()));
		}
	}

	template<class T,
		typename = std::enable_if<std::is_base_of<IUnknown, T>::value>>
		inline void WASAPI_release(T** ptr) {
		if (*ptr) {
			(*ptr)->Release();
			*ptr = nullptr;
		}
	}

	//--------------------
	//	WASAPI
	//--------------------

	void WASAPI_init();
	void WASAPI_cleanup();

public:
	impl();
	~impl();

	void	registerHandle(std::function<void(float*, size_t)> cb) {
		_cb = cb;
	}

	WaveFormat	getFormat();
	RtCode	start();
	RtCode	stop();
	RtCode	poll();

	RtCode	async_start();
	RtCode	async_stop();
	void	handle();

};
