#include "lexer.hpp"
#include "core/log.hpp"

BF_BEGIN_NAMESPACE

Lexer::Lexer(std::vector<char> &buffer)
{
	current = buffer.begin();
	end = buffer.end();
}

bool Lexer::Parse()
{
	while (current != end)
	{
		switch (*current)
		{
			case '(': AddToken(Token::Type::OPEN_PARENTHESES); break;
			case ')': AddToken(Token::Type::CLOSE_PARENTHESES); break;
			case '[': AddToken(Token::Type::OPEN_BRACKET); break;
			case ']': AddToken(Token::Type::CLOSE_BRACKET); break;
			case '{': AddToken(Token::Type::OPEN_BRACE); break;
			case '}': AddToken(Token::Type::CLOSE_BRACE); break;

			case '"': ParseString(); break;

			case ' ':  break;
			case '\r': break;
			case '\t': break;
			case '\n':
				line++;
				break;

			default:
				if (IsAlpha(*current))
					ParseIdentifier();
				else
					Error() << "Parsing error at line" << line << "character" << *current;
				break;
		}

		++current;
	}

	return true;
}

void Lexer::Dump()
{
	for (auto &token: tokens)
	{
		Log() << (int)token.GetType() << token.GetLiteral();
	}
}

void Lexer::ParseIdentifier()
{
	auto start = current;
	while (current != end && IsAlphaNumeric(*(current + 1)))
		++current;

	std::string_view text = { start, current + 1 };
	AddToken(Token::Type::IDENTIFIER, text);

	/*auto it = keywords.find(text);
		if (it != keywords.end())
			AddToken(Token::Type::IDENTIFIER, text);
		else
			AddToken(it->second);*/
}

void Lexer::ParseString()
{
	auto start = ++current;
	while (current != end && *current != '"')
	{
		if (*current == '\n')
			line++;

		++current;
	}

	if (current == end)
		Error() << "end of file";

	AddToken(Token::Type::STRING, { start, current });
}

void Lexer::AddToken(Token::Type type)
{
	tokens.emplace_back(type);
}

void Lexer::AddToken(Token::Type type, std::string_view literal)
{
	tokens.emplace_back(type, literal);
}

bool Lexer::IsDigit(char c)
{
	return c >= '0' && c <= '9';
}

bool Lexer::IsAlpha(char c)
{
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

bool Lexer::IsAlphaNumeric(char c)
{
	return IsAlpha(c) || IsDigit(c);
}

BF_END_NAMESPACE
