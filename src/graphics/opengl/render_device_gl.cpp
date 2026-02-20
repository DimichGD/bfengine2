#include "render_device_gl.hpp"
#include "graphics/opengl/convert_enum_gl.hpp"
//#include "opengl_gen.hpp"
#include "core/log.hpp"
#include "io/file.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/integer.hpp>
//#include <utility>

extern "C"
{
	__declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
	__declspec(dllexport) DWORD AmdPowerXpressRequestHighPerformance = 0x00000001;
}

BF_BEGIN_NAMESPACE

static const std::string glsl_version = "#version 460 core\n";
static std::vector<char> glsl_defines;

void OpenGLMessage(const char *message)
{
	Log() << message;
}

void MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
					 const GLchar *message, const void *userData)
{
	(void)source;
	(void)type;
	(void)id;
	(void)severity;
	(void)length;
	(void)userData;

	if (severity == GL_DEBUG_SEVERITY_NOTIFICATION)
		return;

	OpenGLMessage(message);
}

RenderDeviceGL::RenderDeviceGL(Config *config)
{
	this->config = config;
}

RenderDeviceGL::~RenderDeviceGL()
{
	//
}

void RenderDeviceGL::Create()
{
	gl_load_functions();

	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(MessageCallback, nullptr);

	glGetIntegerv(GL_MAX_UNIFORM_BLOCK_SIZE, &limits.max_ubo_size);
	glGetIntegerv(GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT, &limits.ubo_alignment);
	glGetIntegerv(GL_SHADER_STORAGE_BUFFER_OFFSET_ALIGNMENT, &limits.ssbo_alignmemt);

	/*Log() << "GL_MAX_UNIFORM_BLOCK_SIZE" << limits.max_ubo_size;
	Log() << "GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT" << limits.ubo_alignment;
	Log() << "GL_SHADER_STORAGE_BUFFER_OFFSET_ALIGNMENT" << limits.ssbo_alignmemt;*/

	File defines_file("../../data/shaders/forward/defines.h"); // TODO: idk
	defines_file.Open();
	glsl_defines = defines_file.Read();

	GLuint sampler;
	glCreateSamplers(1, &sampler);
	glSamplerParameteri(sampler, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glSamplerParameteri(sampler, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // GL_LINEAR_MIPMAP_LINEAR
	glBindSampler(0, sampler);
}

void RenderDeviceGL::BeginRenderPass(glm::ivec4 viewport, RenderPass::Clear clear_flags)
{
	//glClearColor(clear_flags.color.r, clear_flags.color.g, clear_flags.color.b, clear_flags.color.a);
	//glClearDepth(clear_flags.depth);

	glViewport(viewport[0], viewport[1], viewport[2], viewport[3]);
	glClear(gl::ConvertEnum(clear_flags));
}

void RenderDeviceGL::EndRenderPass()
{
	//
}

Pipeline RenderDeviceGL::CreatePipeline(const PipelineDesc &desc)
{
	Pipeline pipeline
	{
		.prog = CreateProgram(desc.shaders),
		.vao = CreateVertexLayout(desc.vertex_attribs),
		.topology = gl::ConvertEnum(desc.topology),
		.raster = desc.raster,
	};

	return pipeline;
}

void RenderDeviceGL::BindPipeline(Pipeline pipeline)
{
	current_pipeline = pipeline;
	glUseProgram(pipeline.prog.handle);
	glBindVertexArray(pipeline.vao.handle);
	//glVertexArrayElementBuffer(pipeline.vao.handle, 0);

	pipeline.raster.depth_test ? glEnable(GL_DEPTH_TEST) : glDisable(GL_DEPTH_TEST);

	switch (pipeline.raster.blend)
	{
		case Blend::NONE:
			glDisable(GL_BLEND);
			break;

		case Blend::ADD:
			glEnable(GL_BLEND);
			glBlendFunc(GL_ONE, GL_ONE);
			break;

		case Blend::MULTIPLY:
			glEnable(GL_BLEND);
			glBlendFunc(GL_DST_COLOR, GL_ZERO);
			break;

		case Blend::ALPHA:
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			break;
	}

	glEnable(GL_CULL_FACE);
	//glEnable(GL_MULTISAMPLE);
}

void RenderDeviceGL::BindVertexBuffer(GPUBuffer buffer)
{
	assert(buffer.type == GPUBuffer::Type::VERTEX);
	glBindVertexBuffer(0, buffer.handle, 0, current_pipeline.vao.stride);
}

void RenderDeviceGL::BindIndexBuffer(GPUBuffer buffer)
{
	assert(buffer.type == GPUBuffer::Type::INDEX);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer.handle);
	glVertexArrayElementBuffer(current_pipeline.vao.handle, buffer.handle);
}

Shader RenderDeviceGL::CreateShader(Shader::Type type, const std::vector<char> &source)
{
	GLint length[] = { static_cast<GLint>(glsl_version.length()),
					   static_cast<GLint>(glsl_defines.size()),
					   static_cast<GLint>(source.size()) };
	GLchar const *strings[] = { glsl_version.data(), glsl_defines.data(), source.data() };

	GLuint shader = glCreateShader(gl::ConvertEnum(type));
	glShaderSource(shader, 3, strings, length);
	glCompileShader(shader);

	GLint status = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status != GL_TRUE)
	{
		GLint len;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);

		std::string log(len, '\0');
		glGetShaderInfoLog(shader, len, nullptr, log.data());

		Log() << "Shader compilation failed";
		Log() << log;
		return {};
	}

	return Shader(shader, type);
}

void RenderDeviceGL::SetUniform(Uniform::Name name, int value)
{
	glUniform1i(std::to_underlying(name), value);
}

void RenderDeviceGL::SetUniform(Uniform::Name name, const glm::mat4 &value)
{
	glUniformMatrix4fv(std::to_underlying(name), 1, GL_FALSE, glm::value_ptr(value));
}

void RenderDeviceGL::SetUniform(Uniform::Name name, const glm::vec4 &value)
{
	glUniform4fv(std::to_underlying(name), 1, glm::value_ptr(value));
}

void RenderDeviceGL::SetUniform(Uniform::Texture name, const Texture &value)
{
	glBindTextureUnit(std::to_underlying(name), value.handle);
}

void RenderDeviceGL::SetUniform(Uniform::Buffer name, const GPUBuffer &value)
{
	glBindBufferBase(gl::ConvertEnum(value.type), std::to_underlying(name), value.handle);
}

/*void RenderDevice::WriteUniform(const Uniform &uniform)
{
	int unit = int(uniform.name) - int(Uniform::Name::TEXTURE_0);
	int location = current_pipeline.prog.uniforms[size_t(uniform.name)];
	switch (Uniform::types[size_t(uniform.name)])
	{
		case Uniform::Type::INT:
			glUniform1i(location, *uniform.value_int);
			break;

		case Uniform::Type::FLOAT:
			glUniform1f(location, *uniform.value_float);
			break;

		case Uniform::Type::VEC2:
			glUniform2fv(location, 1, uniform.value_float);
			break;

		case Uniform::Type::VEC3:
			glUniform3fv(location, 1, uniform.value_float);
			break;

		case Uniform::Type::VEC4:
			glUniform4fv(location, 1, uniform.value_float);
			break;

		case Uniform::Type::MAT4:
			glUniformMatrix4fv(location, 1, GL_FALSE, uniform.value_float);
			break;

		case Uniform::Type::TEXTURE_2D:
			glUniform1i(location, unit);
			glActiveTexture(GL_TEXTURE0 + unit);
			glBindTexture(GL_TEXTURE_2D, *uniform.value_int);
			break;

		case Uniform::Type::BUFFER:
			glBindBufferBase(uniform.value_buffer->target, 0, uniform.value_buffer->handle);
			break;
	};
}*/

GPUBuffer RenderDeviceGL::CreateBuffer(GPUBuffer::Type type, uint32_t size, const void *data)
{
	//GLenum target = ConvertEnum(type);
	GLuint buffer;
	glCreateBuffers(1, &buffer);

	GLbitfield flags = 0;
	if (data == nullptr)
		flags = GL_DYNAMIC_STORAGE_BIT | GL_MAP_WRITE_BIT;

	glNamedBufferStorage(buffer, size, data, flags);

	return GPUBuffer { { buffer }, size, type };
}

void RenderDeviceGL::UpdateBuffer(GPUBuffer buffer, uint32_t size, const void *data, uint32_t offset)
{
	if (size > buffer.size)
	{
		Log() << "size" << size <<  ">" << "buffer.size" << buffer.size;
		return;
	}

	glNamedBufferSubData(buffer.handle, offset, size, data);
}

void *RenderDeviceGL::MapBuffer(GPUBuffer buffer)
{
	return glMapNamedBuffer(buffer.handle, GL_WRITE_ONLY);
}

void RenderDeviceGL::UnmapBuffer(GPUBuffer buffer)
{
	glUnmapNamedBuffer(buffer.handle);
}

Texture RenderDeviceGL::CreateTexture(const TextureDesc &desc, bool generate_mipmaps)
{
	if (!desc.width || !desc.height || std::to_underlying(desc.format) == 0 || !desc.levels)
	{
		Log() << "Invalid texture description";
		return {};
	}

	gl::TextureFormat format = gl::ConvertEnum(desc.format);

	int levels = desc.levels;
	if (generate_mipmaps)
		levels = glm::floor(glm::log2(glm::max(desc.width, desc.height))) + 1;

	GLuint tex;
	glCreateTextures(GL_TEXTURE_2D, 1, &tex);

	glTextureStorage2D(tex, levels, format.internal_format, desc.width, desc.height);

	if (desc.pixels != nullptr)
		glTextureSubImage2D(tex, 0, 0, 0, desc.width, desc.height, format.format, format.type, desc.pixels);

	if (generate_mipmaps)
		glGenerateTextureMipmap(tex);

	return Texture { tex };
}

void RenderDeviceGL::Draw(const std::vector<DrawCommand> &commands)
{
	for (auto &command: commands)
		glDrawArrays(current_pipeline.topology, command.first, command.count);
}

void RenderDeviceGL::Draw(uint32_t first, uint32_t count)
{
	glDrawArrays(current_pipeline.topology, first, count);
}

void RenderDeviceGL::DrawIndexed(uint32_t first, uint32_t count)
{
	//glDrawElementsBaseVertex(current_pipeline.topology, count, GL_UNSIGNED_INT, nullptr, first);
	const void *offset = (void*)(sizeof(uint32_t) * first);
	//glDrawElements(current_pipeline.topology, count, GL_UNSIGNED_INT, offset);
	glDrawElementsInstancedBaseInstance(current_pipeline.topology, count, GL_UNSIGNED_INT, offset, 1, 0);
}

void RenderDeviceGL::BindDescriptors(size_t index, size_t count)
{
	for (size_t i = index; i < index + count; i++)
	{
		Descriptor &descriptor = descriptors.at(i);
		switch (descriptor.value.index())
		{
			case 0:
			{
				Texture &texture = std::get<0>(descriptor.value);
				glBindTextureUnit(descriptor.location, texture.handle);
				break;
			}

			case 1:
			{
				glm::vec4 &value = std::get<1>(descriptor.value);
				glUniform4fv(descriptor.location, 1, glm::value_ptr(value));
				break;
			}
		}
	}
}

Program RenderDeviceGL::CreateProgram(const std::vector<Shader> &shaders)
{
	GLuint prog = glCreateProgram();

	//glAttachShader(prog, shaders.handle);
	//glAttachShader(prog, fs.handle);
	for (auto &shader: shaders)
		glAttachShader(prog, shader.handle);

	glLinkProgram(prog);

	for (auto &shader: shaders)
		glDetachShader(prog, shader.handle);

	//glDetachShader(prog, shaders.handle);
	//glDetachShader(prog, fs.handle);

	GLint status = 0;
	glGetProgramiv(prog, GL_LINK_STATUS, &status);
	if (status != GL_TRUE)
	{
		Log() << "Program link failed";
		return {};
	}

	//glDeleteShader(vs);
	//glDeleteShader(fs);

	/*GLint uniform_count = 0;
	glGetProgramInterfaceiv(prog, GL_PROGRAM_INPUT, GL_ACTIVE_RESOURCES, &uniform_count);
	std::vector<GLenum> properties { GL_TYPE, GL_NAME_LENGTH, GL_LOCATION };
	for (int i = 0; i < uniform_count; i++)
	{
		std::vector<GLint> values(properties.size());
		glGetProgramResourceiv(prog, GL_PROGRAM_INPUT, i, properties.size(), properties.data(), values.size(), nullptr, values.data());

		std::string name(values[1] - 1, '\0');
		glGetProgramResourceName(prog, GL_PROGRAM_INPUT, i, values[1], nullptr, name.data());
		Log() << "Attrib" << i << "name:" << name << "type:" << values[0] << "location:" << values[2];
	}*/

	//Program result;
	//result.handle = prog;

	//for (size_t i = 0; i < result.uniforms.size(); i++)
	//	result.uniforms[i] = glGetUniformLocation(prog, Uniform::names[i]); // TODO: check for overflow

	return { prog };
}


VertexLayout RenderDeviceGL::CreateVertexLayout(Vertex::Attrib attribs)
{
	GLuint vao;
	glCreateVertexArrays(1, &vao);

	uint32_t offset = 0;
	for (uint32_t i = 0; i < 8; i++)
	{
		if (attribs & (1 << i))
		{
			glEnableVertexArrayAttrib(vao, i);
			glVertexArrayAttribBinding(vao, i, 0);
			glVertexArrayAttribFormat(vao, i, Vertex::sizes[i], GL_FLOAT, GL_FALSE, offset);

			offset += Vertex::sizes[i] * sizeof(float);
		}
	}

	return VertexLayout { { vao }, offset };
}

BF_END_NAMESPACE
