#pragma once
#include "lexer.hpp"
#include "graphics/shader_description.hpp"

BF_BEGIN_NAMESPACE

class Parser
{
public:
	Parser(std::vector<char> &buffer);
	std::map<std::string, ShaderDesc> DoStuff();
	std::map<std::string, std::vector<std::pair<std::string, Texture::Format>>> DoStuff2();
	//ShaderDesc &GetShaderDesc(const std::string &name);

protected:
	ShaderDesc ReadShader();
	std::vector<std::pair<std::string, Texture::Format> > ReadMaterial();
	[[maybe_unused]] std::vector<Token>::iterator &Next();

private:
	Lexer lexer;

	std::vector<Token>::iterator it;
	std::vector<Token>::iterator end;
};

BF_END_NAMESPACE
