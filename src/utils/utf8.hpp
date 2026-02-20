#pragma once
#include "core/defines.hpp"
#include <string>

BF_BEGIN_NAMESPACE

class utf8_iterator
{
public:
	utf8_iterator(std::string::const_iterator it);

	bool operator!= (const utf8_iterator &other);
	utf8_iterator& operator++();
	unsigned int operator*();

private:
	std::string::const_iterator it;
};

class utf8_view
{
public:
	utf8_view(const std::string &str): ref(str) {}

	utf8_iterator begin();
	utf8_iterator end();

private:
	const std::string &ref;
};

BF_END_NAMESPACE
