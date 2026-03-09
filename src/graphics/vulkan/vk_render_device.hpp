#pragma once
#include "core/config.hpp"
#include "graphics/render_device.hpp"
#include "graphics/shader_description.hpp"
#include "io/file.hpp"

struct SDL_Window;

BF_BEGIN_NAMESPACE

class RenderDeviceVK: public RenderDevice
{
public:
	RenderDeviceVK(Config *config, FileSystem *fs);
	~RenderDeviceVK();
	BF_NON_COPYABLE(RenderDeviceVK)
	BF_NON_MOVABLE(RenderDeviceVK)

	bool Create(SDL_Window *window_handle) override;
	void Destroy() override;

	//Shader CreateShader(const std::string &name, Shader::Type type, const std::vector<char> &source);
	Shader LoadShader(Shader::Type type, const std::string &name) override;
	Shader LoadShader(const std::string &name, const ShaderDesc &desc);
	Shader LoadShader(const std::string &name, ShaderDesc &desc, const std::vector<uint32_t> &binary);
	void LoadMaterialDefinition(const std::string &filename);
	PipelineID CreatePipeline(const std::string &name, const PipelineDesc &desc) override;
	//void CreatePipelineLayout(const std::map<Descriptor::Set, std::vector<Descriptor>> &descriptors);
	//void CreatePipelineLayout(const PipelineLayout &layout);
	void BindPipeline(PipelineID pipeline) override;
	void Draw(uint32_t first, uint32_t count) override;
	void DrawIndexed(uint32_t first, uint32_t count) override;

	void BeginFrame() override;
	void BeginRenderPass(FramebufferID framebuffer_id, RenderPass::Clear clear_flags) override;
	void BeginRenderPass(FramebufferID framebuffer_id, RenderPass::Clear clear_flags, Texture resolve_depth);
	void SetViewport(glm::ivec4 viewport);
	void SetCullMode(uint32_t mode) override;
	void EndRenderPass(FramebufferID framebuffer_id) override;
	void EndFrame() override;
	void LayoutTransition(Texture texture, ImageLayout from, ImageLayout to) override;
	void LayoutTransition2(Texture texture, uint32_t step);

	GPUBuffer CreateBuffer(GPUBuffer::Type type, uint32_t size, const void *data = nullptr) override;
	void UpdateBuffer(GPUBuffer buffer, uint32_t size, const void *data, uint32_t offset) override;
	void *MapBuffer(GPUBuffer buffer) override;
	void UnMapBuffer(GPUBuffer buffer) override;

	template<typename T>
	GPUBuffer CreateBuffer(GPUBuffer::Type type, const std::vector<T> &data)
	{
		GPUBuffer buffer = CreateBuffer(type, sizeof(T) * data.size());
		UpdateBuffer(buffer, sizeof(T) * data.size(), data.data(), 0);
		return buffer;
	}

	template<typename T>
	std::span<T> MapBuffer(GPUBuffer buffer)
	{
		T *t = reinterpret_cast<T*>(MapBuffer(buffer));
		return { t, size_t(buffer.size / sizeof(T)) };
	}

	void BindVertexBuffer(GPUBuffer buffer) override;
	void BindIndexBuffer(GPUBuffer buffer) override {}

	DescriptorSet CreateDescriptorSet(PipelineID pipeline, Descriptor2::Set set) override;
	void WriteDescriptor(DescriptorSet set, uint32_t binding, GPUBuffer value) override;
	void WriteDescriptor(DescriptorSet set, uint32_t binding, Texture value, uint32_t index = 0) override;
	void BindDescriptorSet(Descriptor2::Set index, DescriptorSet descriptor_set) override; // TODO: rename index
	//void Push(Shader::Type type, uint32_t offset, glm::vec4 value);
	//void Push(Shader::Type type, uint32_t offset, int value) override;
	void PushConstant(EngineConstants slot, int value) override;
	void PushConstant(EngineConstants slot, float value) override;
	//void Push(size_t size, size_t offset, void *value);
	/*void SetUniform1i(int value);
	void SetUniform2i(std::array<int, 2> values);*/

	Texture CreateTexture(const std::string &name, const TextureDesc &desc) override;
	FramebufferID CreateFramebuffer(const FramebufferDesc &desc) override;
	Framebuffer GetFramebuffer(FramebufferID framebuffer);

	uint32_t GetFrameIndex() const;
	uint32_t GetFrameCount() const;
	//Texture GetDepthTexture();
	//void SetDepthTexture(Texture depth_texture);

	//void SetDebugName(Texture texture, const char *name);

private:
	Config *config = nullptr;
	FileSystem *fs = nullptr;

	struct Internal;
	Internal *vk = nullptr;

	struct Storage;
	Storage *store = nullptr;

	uint32_t times[32] {};

	std::map<uint32_t, ShaderDesc> shader_desc_map;

	//std::map<Handle, TrackedResource> tracked_resources;
	//std::vector<ImageLayout> swapchain_image_prev_layouts;
	//std::vector<Texture> swapchain_textures;
};

BF_END_NAMESPACE
