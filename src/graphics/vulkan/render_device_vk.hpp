#pragma once
#include "core/config.hpp"
#include "graphics/render_device.hpp"
#include "io/file.hpp"

struct SDL_Window;

BF_BEGIN_NAMESPACE

struct TrackedResource
{
	ImageLayout prev = ImageLayout::UNDEFINED;
	//ImageLayout next = ImageLayout::UNDEFINED;
};

class RenderDeviceVK /*: public RenderDevice*/
{
public:
	RenderDeviceVK(Config *config, FileSystem *fs);
	~RenderDeviceVK();
	BF_NON_COPYABLE(RenderDeviceVK)
	BF_NON_MOVABLE(RenderDeviceVK)

	bool Create(SDL_Window *window_handle);
	void Destroy();

	//Shader CreateShader(const std::string &name, Shader::Type type, const std::vector<char> &source);
	Shader LoadShader(Shader::Type type, const std::string &name);
	PipelineID CreatePipeline(const std::string &name, const PipelineDesc &desc);
	void Test();
	//void CreatePipelineLayout(const std::map<Descriptor::Set, std::vector<Descriptor>> &descriptors);
	//void CreatePipelineLayout(const PipelineLayout &layout);
	void BindPipeline(PipelineID pipeline);
	void Draw(uint32_t first, uint32_t count);

	void BeginFrame();
	void BeginRenderPass(FramebufferID framebuffer_id, RenderPass::Clear clear_flags);
	void SetViewport(glm::ivec4 viewport);
	void EndRenderPass(FramebufferID framebuffer_id);
	bool EndFrame();
	void LayoutTransition(Texture texture, ImageLayout from, ImageLayout to);

	GPUBuffer CreateBuffer(GPUBuffer::Type type, uint32_t size);
	void UpdateBuffer(GPUBuffer buffer, uint32_t size, const void *data, uint32_t offset);
	void *MapBuffer(GPUBuffer buffer);
	void UnMapBuffer(GPUBuffer buffer);

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

	void BindVertexBuffer(GPUBuffer buffer);

	DescriptorSet CreateDescriptorSet(PipelineID pipeline, Descriptor2::Set set);
	void WriteDescriptor(DescriptorSet set, uint32_t binding, GPUBuffer value);
	void WriteDescriptor(DescriptorSet set, uint32_t binding, Texture value, uint32_t index = 0);
	void BindDescriptorSet(Descriptor2::Set set, DescriptorSet index); // TODO: rename index
	//void Push(Shader::Type type, uint32_t offset, glm::vec4 value);
	void Push(Shader::Type type, uint32_t offset, int value);
	//void Push(size_t size, size_t offset, void *value);
	/*void SetUniform1i(int value);
	void SetUniform2i(std::array<int, 2> values);*/

	Texture CreateTexture(const std::string &name, const TextureDesc &desc);
	FramebufferID CreateFramebuffer(const FramebufferDesc &desc);
	Framebuffer GetFramebuffer(FramebufferID framebuffer);
	Texture GetDepthTexture();
	//void SetDepthTexture(Texture depth_texture);

	//void SetDebugName(Texture texture, const char *name);
	void SetTrackedResource(Texture texture);
	void ResetResourceTransition(Texture texture);
	void MakeResourceTransition(Texture texture, ImageLayout next_layout);

	/*void BeginRenderPass(glm::ivec4 viewport, RenderPass::Clear clear_flags) override;
	void EndRenderPass() override;

	Pipeline CreatePipeline(const PipelineDesc &desc) override;
	void BindPipeline(Pipeline pipeline) override;
	void BindVertexBuffer(GPUBuffer buffer) override;
	void BindIndexBuffer(GPUBuffer buffer) override;

	Shader CreateShader(Shader::Type type, const std::vector<char> &source) override;

	GPUBuffer CreateBuffer(GPUBuffer::Type type, uint32_t size, const void *data) override;
	void UpdateBuffer(GPUBuffer buffer, uint32_t size, const void *data, uint32_t offset) override;

	Texture CreateTexture(const TextureDesc &desc, bool generate_mipmaps) override;

	void Draw(uint32_t first, uint32_t count) override;
	void DrawIndexed(uint32_t first, uint32_t count) override;

	void CreateDescriptor(Uniform::Texture name, Texture value) override;
	void CreateDescriptor(Uniform::Name name, glm::vec4 value) override;
	void BindDescriptors(size_t index, size_t count) override;*/

private:
	Config *config = nullptr;
	FileSystem *fs = nullptr;

	struct Internal;
	Internal *vk = nullptr;

	struct Storage;
	Storage *store = nullptr;

	bool stop = false;
	std::map<Handle, TrackedResource> tracked_resources;
	std::vector<ImageLayout> swapchain_image_prev_layouts;
	//std::vector<Texture> swapchain_textures;
};

BF_END_NAMESPACE
