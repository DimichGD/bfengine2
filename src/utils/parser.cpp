#include "parser.hpp"
#include "core/log.hpp"
#include <map>

BF_BEGIN_NAMESPACE

Parser::Parser(std::vector<char> &buffer): lexer(buffer)
{
	//
}

std::map<std::string, ShaderDesc> Parser::DoStuff()
{
	if (!lexer.Parse())
		return {};

	it = lexer.Tokens().begin();
	end = lexer.Tokens().end();
	std::map<std::string, ShaderDesc> shaders;

	while (it != end)
	{
		switch (it->GetType())
		{
			case Token::Type::KEYWORD:
				if (it->GetKeyword() == Keyword::SHADER)
				{
					std::string name = std::string(Next()->GetLiteral());
					shaders[name] = ReadShader();
				}

				break;

			default:
				Error() << "Unsupported type" << int(it->GetType());
		}

		Next();
	}

	//Log();

	return shaders;
}

std::map<std::string, std::vector<std::pair<std::string, Texture::Format>>> Parser::DoStuff2()
{
	if (!lexer.Parse())
		return {};

	it = lexer.Tokens().begin();
	end = lexer.Tokens().end();
	std::map<std::string, std::vector<std::pair<std::string, Texture::Format>>> materials;

	while (it != end)
	{
		switch (it->GetType())
		{
			case Token::Type::KEYWORD:
				if (it->GetKeyword() == Keyword::MATERIAL)
				{
					std::string name = std::string(Next()->GetLiteral());
					materials[name] = ReadMaterial();
				}

				break;

			default:
				Error() << "Unsupported type" << int(it->GetType());
		}

		Next();
	}

	//Log();

	return materials;
}

/*ShaderDesc &Parser::GetShaderDesc(const std::string &name)
{
	return shaders[name];
}*/

ShaderDesc Parser::ReadShader()
{
	std::map<std::string, bf::Shader::Type> shader_type_map
	{
		{ "vertex", bf::Shader::Type::VERTEX },
		{ "fragment", bf::Shader::Type::FRAGMENT },
	};

	std::map<std::string, EngineDescriptor> descriptor_map
	{
		{ "CAMERA_MATRICES", EngineDescriptor::CAMERA_MATRICES },
		{ "UI_CAMERA_MATRIX", EngineDescriptor::UI_CAMERA_MATRIX },
		{ "MODEL_MATRICES", EngineDescriptor::MODEL_MATRICES },
		{ "COLORS", EngineDescriptor::COLORS },
		{ "TEXTURES", EngineDescriptor::TEXTURES },
		//{ "MATERIAL_DATA", EngineDescriptor::MATERIAL_DATA },
		{ "LIGHT_CAMERA_DATA", EngineDescriptor::LIGHT_CAMERA_DATA },
		{ "POINT_LIGHTS", EngineDescriptor::POINT_LIGHTS },
		{ "SPOT_LIGHTS", EngineDescriptor::SPOT_LIGHTS },
		{ "BONE_MATRICES", EngineDescriptor::BONE_MATRICES },
	};

	std::map<std::string, EngineUniform> uniform_map
	{
		{ "CAMERA_MATRICES", EngineUniform::CAMERA_MATRICES },
		{ "UI_CAMERA_MATRIX", EngineUniform::UI_CAMERA_MATRIX },
		{ "MODEL_MATRICES", EngineUniform::MODEL_MATRICES },
		{ "COLORS", EngineUniform::COLORS },
		//{ "MATERIAL_DATA", EngineDescriptor::MATERIAL_DATA },
		{ "LIGHT_CAMERA_DATA", EngineUniform::LIGHT_CAMERA_DATA },
		{ "POINT_LIGHTS", EngineUniform::POINT_LIGHTS },
		{ "SPOT_LIGHTS", EngineUniform::SPOT_LIGHTS },
		{ "BONE_MATRICES", EngineUniform::BONE_MATRICES },

		{ "OBJECT_INDEX", EngineUniform::OBJECT_INDEX },
		{ "MATERIAL_INDEX", EngineUniform::MATERIAL_INDEX },
		{ "FACTOR", EngineUniform::FACTOR },
		{ "TIME", EngineUniform::TIME },
	};

	std::map<std::string, EngineConstants> constant_map
	{
		{ "OBJECT_INDEX", EngineConstants::OBJECT_INDEX },
		{ "MATERIAL_INDEX", EngineConstants::MATERIAL_INDEX },
		{ "FACTOR", EngineConstants::FACTOR },
		{ "TIME", EngineConstants::TIME },
	};

	std::map<std::string, uint32_t> vertex_attrib_map
	{
		{ "POSITION", uint32_t(Vertex::Attrib::POSITION) },
		{ "TEXCOORD_0", uint32_t(Vertex::Attrib::TEXCOORD_0) },
		{ "TEXCOORD_1", uint32_t(Vertex::Attrib::TEXCOORD_1) },
		{ "COLOR", uint32_t(Vertex::Attrib::COLOR) },
		{ "NORMAL", uint32_t(Vertex::Attrib::NORMAL) },
		{ "TANGENT", uint32_t(Vertex::Attrib::TANGENT) },
		{ "BONES", uint32_t(Vertex::Attrib::BONES) },
		{ "WEIGHTS", uint32_t(Vertex::Attrib::WEIGHTS) },
	};

	if (Next()->GetType() != Token::Type::OPEN_BRACE)
		throw std::runtime_error("Expected {");

	ShaderDesc shader;

	while (Next()->GetType() != Token::Type::CLOSE_BRACE)
	{
		if (it->GetType() != Token::Type::KEYWORD)
			throw std::runtime_error("Expecting KEYWORD");

		switch (it->GetKeyword())
		{
			case Keyword::TYPE:
				shader.type = shader_type_map[std::string(Next()->GetLiteral())];
				break;

			case Keyword::FILE:
				shader.filename = Next()->GetLiteral();
				break;

			case Keyword::INPUT:
				if (Next()->GetType() != Token::Type::OPEN_BRACKET)
					throw std::runtime_error("Expected [");

				while (Next()->GetType() != Token::Type::CLOSE_BRACKET)
					shader.input = Vertex::Attrib(uint32_t(shader.input) | vertex_attrib_map[std::string(it->GetLiteral())]);

				break;

			case Keyword::OUTPUT:
				break;

			case Keyword::UNIFORMS:
				if (Next()->GetType() != Token::Type::OPEN_BRACKET)
					throw std::runtime_error("Expected [");

				while (Next()->GetType() != Token::Type::CLOSE_BRACKET)
					shader.uniforms.push_back(uniform_map[std::string(it->GetLiteral())]);

				break;

			case Keyword::BUFFER:
				shader.buffers.push_back(descriptor_map[std::string(Next()->GetLiteral())]);
				break;

			case Keyword::CONSTANT:
				shader.constants.push_back(constant_map[std::string(Next()->GetLiteral())]);
				break;

			case Keyword::TEXTURE:
			{
				std::string name = std::string(Next()->GetLiteral());
				uint32_t samples = Next()->GetLiteral() == "1" ? 1 : 4; // TODO: check type
				shader.textures.emplace_back(name, samples);
				break;
			}

			default:
				throw std::runtime_error("Unexpected KEYWORD");
		}
	}

	return shader;
}

std::vector<std::pair<std::string, Texture::Format>> Parser::ReadMaterial()
{
	if (Next()->GetType() != Token::Type::OPEN_BRACE)
		throw std::runtime_error("Expected {");

	std::vector<std::pair<std::string, Texture::Format>> material;

	while (Next()->GetType() != Token::Type::CLOSE_BRACE)
	{
		if (it->GetType() != Token::Type::KEYWORD)
			throw std::runtime_error("Expecting KEYWORD");

		switch (it->GetKeyword())
		{
			case Keyword::TEXTURE:
			{
				std::string name = std::string(Next()->GetLiteral());
				Texture::Format format = Next()->GetLiteral() == "srgba" ? Texture::Format::SRGBA8 : Texture::Format::RGBA8;
				material.push_back(std::make_pair(name, format));
				break;
			}

			default:
				throw std::runtime_error("Unexpected KEYWORD");
		}
	}

	return material;
}

std::vector<Token>::iterator &Parser::Next()
{
	if (it == end)
		throw std::runtime_error("Unexpected end of stream");

	return ++it;
}

BF_END_NAMESPACE
