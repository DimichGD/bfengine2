#pragma once
#include "core/defines.hpp"
#include "io/file.hpp"

BF_BEGIN_NAMESPACE

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

		// keywords
		VAR, FUNC, RETURN,

		END,
	};

	Token(Type type)
	{
		this->type = type;
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
	std::string_view literal;
};

class Lexer
{
public:
	Lexer(std::vector<char> &buffer);
	bool Parse();
	void Dump();
	const std::vector<Token> &Tokens() const { return tokens; }

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
};

BF_END_NAMESPACE
