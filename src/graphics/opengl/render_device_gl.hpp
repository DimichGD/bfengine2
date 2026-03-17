#pragma once
#include "graphics/render_device.hpp"
#include "core/config.hpp"
#include "io/file.hpp"
#include <glm/mat4x4.hpp>
#include <variant>
#include <vector>

BF_BEGIN_NAMESPACE

class RenderDeviceGL: public RenderDevice
{
public:
	struct DeviceLimits
	{
		int max_ubo_size = 0;
		int ubo_alignment = 0;
		int ssbo_alignmemt = 0;
	};

	RenderDeviceGL(Config *config, FileSystem *fs);
	~RenderDeviceGL();

	BF_NON_COPYABLE(RenderDeviceGL)
	BF_NON_MOVABLE(RenderDeviceGL)

	const DeviceLimits &Limits() const { return limits; }

	bool Create(SDL_Window *window_handle) override;
	void Destroy() override;
	void BeginRenderPass(FramebufferID framebuffer_id, RenderPass::Clear clear_flags) override;
	void EndRenderPass(FramebufferID framebuffer_id) override;

	PipelineID CreatePipeline(const std::string &name, const PipelineDesc &desc) override;
	void BindPipeline(PipelineID pipeline_id) override;
	void BindVertexBuffer(GPUBuffer buffer) override;
	void BindIndexBuffer(GPUBuffer buffer) override;

	void SetCullMode(uint32_t mode) override;
	void LayoutTransition(Texture texture, ImageLayout from, ImageLayout to) override {}
	void BeginFrame() override {}
	void EndFrame() override {}
	DescriptorSet CreateDescriptorSet(PipelineID pipeline, Descriptor2::Set set) override;
	void WriteDescriptor(DescriptorSet set, uint32_t binding, GPUBuffer value) override;
	void WriteDescriptor(DescriptorSet set, uint32_t binding, Texture value, uint32_t index = 0) override;
	void BindDescriptorSet(Descriptor2::Set index, DescriptorSet descriptor_set) override; // TODO: rename arguments
	//void Push(Shader::Type type, uint32_t offset, int value) override;
	void PushConstant(EngineConstants slot, int value) override;
	void PushConstant(EngineConstants slot, float value) override;

	FramebufferID CreateFramebuffer(const FramebufferDesc &desc) override;

	Shader LoadShader(Shader::Type type, const std::string &name) override;
	//void WriteUniform(const Uniform &uniform);

	template<typename T>
	GPUBuffer CreateBuffer(GPUBuffer::Type type, const std::vector<T> &vector)
		{ return CreateBuffer(type, vector.size() * sizeof(T), vector.data()); }

	template<typename T>
	void UpdateBuffer(GPUBuffer buffer, const std::vector<T> &vector)
		{ return UpdateBuffer(buffer, vector.size() * sizeof(T), vector.data()); }

	/*template<typename T>
	std::span<T> MapBuffer(GPUBuffer buffer)
	{
		T *t = reinterpret_cast<T*>(MapBuffer(buffer));
		return { t, size_t(buffer.size / sizeof(T)) };
	}*/

	GPUBuffer CreateBuffer(GPUBuffer::Type type, uint32_t size, const void *data = nullptr) override;
	void UpdateBuffer(GPUBuffer buffer, uint32_t size, const void *data, uint32_t offset = 0) override;
	std::span<std::byte> MapBuffer(GPUBuffer buffer) override;
	void UnMapBuffer(GPUBuffer buffer) override;

	Texture CreateTexture(const std::string &name, const TextureDesc &desc) override;

	void Draw(const std::vector<DrawCommand> &commands);
	void Draw(uint32_t first, uint32_t count) override;
	void DrawIndexed(uint32_t first, uint32_t count) override;

protected:
	Program CreateProgram(const std::vector<Shader> &shaders);
	VertexLayout CreateVertexLayout(Vertex::Attrib attribs);

private:
	Config *config = nullptr;
	FileSystem *fs = nullptr;

	DeviceLimits limits;
	Pipeline current_pipeline {};

	/*struct Descriptor
	{
		int location = -1;
		std::variant<Texture, glm::vec4> value;
	};*/

	struct Descriptor3
	{
		int location = -1;
		std::variant<Texture, GPUBuffer> value;
	};

	//std::vector<Descriptor> descriptors;
	std::vector<std::map<uint32_t, Descriptor3>> descriptors2;
	std::vector<Pipeline> pipelines;
};

BF_END_NAMESPACE
