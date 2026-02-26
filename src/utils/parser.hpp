#pragma once
#include "lexer.hpp"

BF_BEGIN_NAMESPACE

class Parser
{
public:
	Parser(Lexer *lexer);
	void DoStuff();

private:
	Lexer *lexer = nullptr;
};

BF_END_NAMESPACE
