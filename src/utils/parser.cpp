#include "parser.hpp"
#include "core/log.hpp"

BF_BEGIN_NAMESPACE

Parser::Parser(Lexer *lexer)
{
	this->lexer = lexer;
}

void Parser::DoStuff()
{
	auto begin = lexer->Tokens().begin();
	auto end = lexer->Tokens().end();


}

BF_END_NAMESPACE
