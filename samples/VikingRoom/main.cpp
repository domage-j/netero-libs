/**
 * Netero sources under BSD-3-Clause
 * see LICENSE.txt
 */

#include <chrono>
#include <iostream>
#include <unordered_map>

int main()
{
    return 0;
}

/*
#include <Netero/Graphics/Application.hpp>
#include <Netero/Graphics/Context.hpp>
#include <Netero/Graphics/Instance.hpp>
#include <Netero/Graphics/vertex.hpp>
#include <Netero/Os.hpp>
#include <Netero/extra/tiny_obj_loader.hpp>

const std::string VikingHouseVertexShaderPath =
    netero::os::getBundlePath() + "/shaders/VikingRoomVertexShader.spv";
const std::string VikingHouseFragmentShaderPath =
    netero::os::getBundlePath() + "/shaders/VikingRoomFragmentShader.spv";
const std::string VikingHouseModelPath =
    netero::os::getBundlePath() + "/resources/VikingRoomAsset/vikingRoom.OBJ";
const std::string VikingHouseTexturePath =
    netero::os::getBundlePath() + "/resources/VikingRoomAsset/vikingRoom.png";

struct GraphicSampleApp {
    netero::graphics::Application* handle = nullptr;
    netero::graphics::Context*     context = nullptr;
    netero::graphics::Model*       vikingHouse = nullptr;
    netero::graphics::Instance*    vikingHouseInstance = nullptr;
};

void RunApplication(GraphicSampleApp* myApp)
{
    const auto startTime = std::chrono::high_resolution_clock::now();
    myApp->context->build();
    while (!myApp->context->shouldClose()) {
        auto        now = std::chrono::high_resolution_clock::now();
        const float time =
            std::chrono::duration<float, std::chrono::seconds::period>(now - startTime).count();
        myApp->vikingHouseInstance->z.rotate((std::sin(time * glm::radians(30.f)) - 0.80f) * 0.85f);
        myApp->context->update();
    }
    myApp->context->release();
}

void InitializeApp(GraphicSampleApp* myApp)
{
    myApp->handle = netero::graphics::Application::Initialize("Viking Room");
    myApp->context =
        myApp->handle->newWindowedContext(800, 600, netero::graphics::WindowMode::RESIZABLE);
    myApp->vikingHouse = myApp->context->createModel();
    myApp->vikingHouse->loadShader(VikingHouseVertexShaderPath,
                                   netero::graphics::ShaderStage::VERTEX);
    myApp->vikingHouse->loadShader(VikingHouseFragmentShaderPath,
                                   netero::graphics::ShaderStage::FRAGMENT);
    myApp->vikingHouse->loadTexture(VikingHouseTexturePath,
                                    netero::graphics::TextureSamplingMode::REPEAT);
    {
        tinyobj::attrib_t                     attrib;
        std::vector<netero::graphics::Vertex> vertices;
        std::vector<uint32_t>                 indices;
        std::vector<tinyobj::shape_t>         shapes;
        std::vector<tinyobj::material_t>      materials;
        std::string                           warn, err;
        if (!tinyobj::LoadObj(&attrib,
                              &shapes,
                              &materials,
                              &warn,
                              &err,
                              VikingHouseModelPath.c_str())) {
            throw std::runtime_error(warn + err);
        }
        std::unordered_map<netero::graphics::Vertex, uint32_t> uniqueVertices {};
        for (const auto& shape : shapes) {
            for (const auto& index : shape.mesh.indices) {
                netero::graphics::Vertex vertex {};
                vertex.pos = { attrib.vertices[3 * index.vertex_index + 0],
                               attrib.vertices[3 * index.vertex_index + 1],
                               attrib.vertices[3 * index.vertex_index + 2] };
                vertex.texCord = { attrib.texcoords[2 * index.texcoord_index + 0],
                                   1.0f - attrib.texcoords[2 * index.texcoord_index + 1] };
                vertex.color = { 1.0f, 1.0f, 1.0f };
                if (uniqueVertices.count(vertex) == 0) {
                    uniqueVertices[vertex] = static_cast<uint32_t>(vertices.size());
                    vertices.push_back(vertex);
                }
                indices.push_back(uniqueVertices.at(vertex));
            }
        }
        myApp->vikingHouse->addVertices(vertices, indices);
    }
    myApp->vikingHouseInstance = myApp->vikingHouse->createInstance();
    myApp->vikingHouseInstance->y.rotate(glm::radians(20.f));
}

void CleanUpApp(GraphicSampleApp* myApp)
{
    myApp->vikingHouse->deleteInstance(myApp->vikingHouseInstance);
    myApp->context->deleteModel(myApp->vikingHouse);
    netero::graphics::Application::Release();
}

#if defined(WIN_APP)
#include <WinBase.h>
#include <windows.h>
int WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
#else
int main()
{
#endif
    int              rtCode = 0;
    GraphicSampleApp myApp {};
    try {
        InitializeApp(&myApp);
        RunApplication(&myApp);
        CleanUpApp(&myApp);
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        rtCode = 1;
    }
    catch (...) {
        std::cerr << "Fatal error." << std::endl;
        rtCode = 2;
    }
    return rtCode;
}
*/