/**
 * Netero sources under BSD-3-Clause
 * see LICENSE.txt
 */

#pragma once

#include <vector>

#include <vulkan/vulkan.h>

#include <netero/graphics/descriptor_set.hpp>
#include <netero/graphics/shader.hpp>
#include <netero/graphics/texture.hpp>
#include <netero/graphics/vertex.hpp>

namespace netero::graphics {

class Device;
class Instance;

/**
 * @brief Any model to render
 * Contain assets and data to be rendered.
 * @details Only one model exist per instance. Models are used to
 * hold vertices, shaders, textures...
 */
class Model {
    friend class Pipeline;
    friend class Context;

    Model(VkInstance, Device*);

    void build(size_t, std::vector<VkBuffer>&, VkRenderPass, VkExtent2D);
    void rebuild(size_t, std::vector<VkBuffer>&, VkRenderPass, VkExtent2D);
    void release(size_t);

    void createInstanceBuffer(size_t);
    void createDescriptors(uint32_t);
    void writeToDescriptorSet(uint32_t, std::vector<VkBuffer>&);
    void createGraphicsPipeline(VkRenderPass, VkExtent2D);
    void commitRenderCommand(VkCommandBuffer, size_t);
    void update(uint32_t);

    VkInstance             _instance;
    Device*                _device;
    VertexBuffer           _vertexBuffer;
    VkPipelineLayout       _pipelineLayout;
    VkPipeline             _graphicsPipeline;
    std::vector<Shader>    _shaderModules;
    std::vector<Instance*> _modelInstances;

    // Instance Buffer
    VkBuffer       _instanceBuffer;
    VkDeviceMemory _instanceBufferMemory;

    // Texture
    Texture _textures;

    // Descriptors
    DescriptorSets _descriptorSets;
    Descriptor     _uboDescriptor;
    Descriptor     _textureDescriptor;

    public:
    Model(const Model&) = delete;
    Model(Model&&) = delete;
    Model& operator=(const Model&) = delete;
    Model& operator=(Model&&) = delete;
    ~Model();

    /**
     * @brief Create a new instance of the model.
     */
    Instance* createInstance();

    /**
     * @brief Delete a given instance of the model.
     */
    void deleteInstance(Instance*);

    /**
     * @brief Add vertices to the model
     * @param vertices Vertices to be added to the model.
     * @details This method will generate automatically indices for the given vertices
     * @attention This method will not automatically optimize vertices/indices
     */
    void addVertices(std::vector<Vertex>& vertices);

    /**
     * @brief Add vertices and indices to the model.
     * @param vertices Vertices to be added to the model.
     * @param indices Related indices to be added to the model.
     */
    void addVertices(std::vector<Vertex>& vertices, std::vector<uint32_t>& indices);

    /**
     * @brief Load the given shader to the model's pipeline.
     * @param path A valid path to the shader *.spv file
     * @param stage The pipeline stage to load the shader to.
     */
    int loadShader(const std::string& path, ShaderStage stage);

    /**
     * @brief Load the given texture to the model.
     * @attention The model must have a fragment shader that accept a 2D sampler as uniform binding 1.
     * @param path A valid path to a texture.
     * @param samplingMode A valid sampling mode.
     */
    void loadTexture(const std::string& path, TextureSamplingMode samplingMode);
};
} // namespace netero::graphics
