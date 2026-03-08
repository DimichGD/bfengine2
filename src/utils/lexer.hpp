#pragma once
#include "core/defines.hpp"
#include "io/file.hpp"
#include <map>

BF_BEGIN_NAMESPACE

enum class Keyword
{
	SHADER,
	TYPE,
	FILE,
	INPUT,
	OUTPUT,
	UNIFORMS,
	BUFFER,
	CONSTANT,
	TEXTURE,
	MATERIAL,
};

class Token
{
public:
	enum class Type
	{
		// single character tokens
		OPEN_PARENTHESES, CLOSE_PARENTHESES, OPEN_BRACKET, CLOSE_BRACKET, OPEN_BRACE, CLOSE_BRACE,
		COMMA, DOT, SEMICOLON, PLUS, MINUS, SLASH, STAR,

		// comparison identifiers
		EQUAL, EQUAL_EQUAL,
		NOT, NOT_EQUAL,
		GREATER, GREATER_EQUAL,
		LESS, LESS_EQUAL,

		// literals
		IDENTIFIER, NUMBER, STRING,
		KEYWORD, // use actual enums?

		// keywords
		VAR, FUNC, RETURN,

		END,
	};

	Token(Type type)
	{
		this->type = type;
	}


	Token(Type type, Keyword keyword)
	{
		this->type = type;
		this->keyword = keyword;
	}

	Token(Type type, std::string_view literal)
	{
		this->type = type;
		this->literal = literal;
	}

	Type GetType() const
	{
		return type;
	}

	Keyword GetKeyword() const
	{
		return keyword;
	}

	std::string_view GetLiteral() const
	{
		return literal;
	}

	/*void Dump()
	{
		Log() << int(type) << literal;
	}*/

private:
	Type type;
	Keyword keyword;
	std::string_view literal;
};

class Lexer
{
public:
	Lexer(std::vector<char> &buffer);
	bool Parse();
	void Dump();
	std::vector<Token> &Tokens() { return tokens; }

protected:
	void ParseIdentifier();
	void ParseString();

	void AddToken(Token::Type type);
	void AddToken(Token::Type type, std::string_view literal);

	bool IsDigit(char c);
	bool IsAlpha(char c);
	bool IsAlphaNumeric(char c);

private:
	std::vector<char>::iterator current;
	std::vector<char>::iterator end;

	std::vector<Token> tokens;
	size_t line = 0;

	std::map<std::string, Keyword> keywords;
};

BF_END_NAMESPACE
