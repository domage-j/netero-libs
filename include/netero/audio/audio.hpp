/**
 * Netero sources under BSD-3-Clause
 * see LICENCE.txt
 */

#pragma once

#include <vector>
#include <string>

/**
 * @file audio.hpp
 * @brief Default audio declarations
 */

namespace netero::audio {

	/**
	 * @enum RtCode
	 * @brief Return code for native audio interfaces.
	 */
	enum class RtCode {
		OK = 0, /**< Success. Issued if native call success. */
		ERR_MISSING_CALLBACK = 1, /**< Audio callback is missing. You forget to setup the audio callback. */
		ERR_NATIVE = 2, /**< Native error. Issued while native call failed. */
		ABILITY_NOT_SUPPORTED = 3, /**< Functionality not supported. Issued while the native device does not support the call. */
		FORMAT_NOT_SUPPORTED = 4, /**< The native device does not support the requested format. */
		DEVICE_TIMEOUT = 5, /**< The time out while accessing/getting device's ressource. The device is probably busy, try later. */
		ERR_ALREADY_RUNNING = 6, /**< You already have start the device */
	};

	/**
	 * @struct WaveFormat
	 * @brief Hold information relative to the audio native device.
	 * The buffer is a set of Frames, each frames contains samples.
	 * The number of samples per frame is defined by the number of channels.
	 * The size in byte of the buffer is determinate by
	 * the number of bytes per samples time the number of samples.
	 */
	struct WaveFormat {
		std::string	name; /**< The audio device name. */
		std::string manufacturer; /**< The audio manufacturer name. */
		unsigned	framesCount; /**< Number of frames in contained in the shared buffer with the device. */
		unsigned	bytesPerFrame; /**< Size in byte for one frame. */
		unsigned	bytesPerSample; /**< Size in byte for one sample. */
		unsigned	channels; /**< Number of sample per frames */
		unsigned	samplingFrequency; /**< Actual sampling frequency of the native audio device. */
		std::vector<float> supportedSamplingRate; /**< Supported sampling frequency of the native audio device */
	};

	/**
	 * @interface AudioOutStream
	 * @brief For any audio stream capable of generating a signal.
	 */
	class AudioOutStream {
	public:
		/**
		 * @pure setFormat
		 * @see netero::audio::device
		 * @remarks You can retrieve the format in ctor via a netero::audio::device's methode
		 *			to preallocate internal buffer you may use for rendering.
		 * It is called by a device or a parent node while the waveFormat need to be updated
		 */
		virtual void setFormat(const WaveFormat &) = 0;

		/**
		 * @pure render
		 * @warning This methode is called by a parent node in a seperate thread.
		 *			You must not perform any allocation nor blocking call or it might
		 *			impact severly the audio rendering of your application.
		 * @warning Becarfull, the buffer size may differ between call. Do not assume
					that it is the same as the shared size provided threw WaveFormat struct.
		 * @param[in] buffer The rendering buffer.
		 * @param[in] frames The number of frames the buffer contain.
		 */
		virtual void render(float *buffer, size_t frames) = 0;

		/**
		 * @pure play
		 * @see pause
		 * Allow the audio stream to produce a signal.
		 * In case of previous call of stop the stream should start at
		 * a previously saved offset.
		 */
		virtual void play() = 0;

		/**
		 * @pure pause
		 * Stop the signal generation from the stream and save the offset.
		 * If play() is called again the stream must start again from the saved offset.
		 */
		virtual void pause() = 0;

		/**
		 * @pure stop
		 * Stop the signal generation from the stream.
		 * The offset may not be saved and be reseted.
		 */
		virtual void stop() = 0;
	};

	/**
	 * @interface AudioOutStream
	 * @brief for any input audio stream
	 */
	class AudioInStream {
	public:
		/**
		 * @pure capture
		 * @warning This methode is called by a parent node in a seperate thread.
		 *			You must not perform any allocation nor blocking call or it might
		 *			impact severly the audio rendering of your application.
		 * @warning Becarfull, the buffer size may differ between call. Do not assume
					that it is the same as the shared size provided threw WaveFormat struct.
		 * @param[in] buffer The rendering buffer.
		 * @param[in] frames The number of frames the buffer contain.
		 */
		virtual void capture(const float* buffer, const size_t frames) = 0;

		/**
		 * @pure play
		 * Allow the audio stream to recive a signal.
		 */
		virtual void startRecord() = 0;

		/**
		 * @pure stop
		 * Stop reciving a signal from the stream.
		 */
		virtual void stopRecord() = 0;

	};
}

