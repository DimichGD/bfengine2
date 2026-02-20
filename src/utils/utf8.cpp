#include "utf8.hpp"

BF_BEGIN_NAMESPACE

utf8_iterator::utf8_iterator(std::string::const_iterator it)
{
	this->it = it;
}

bool utf8_iterator::operator!=(const utf8_iterator &other)
{
	return this->it != other.it;
}

utf8_iterator &utf8_iterator::operator++()
{
	return *this;
}

unsigned int utf8_iterator::operator*()
{
	unsigned int codepoint = 0;

	if ((*it & 0x80) == 0)
	{
		codepoint = *it++ & 0x7F;
	}
	else if ((*it & 0xE0) == 0xC0)
	{
		codepoint = *it++ & 0x1F;
		codepoint = ((codepoint << 6) | (*it++ & 0x3F));
	}
	else if ((*it & 0xF0) == 0xE0)
	{
		codepoint = *it++ & 0x0F;
		codepoint = ((codepoint << 6) | (*it++ & 0x3F));
		codepoint = ((codepoint << 6) | (*it++ & 0x3F));
	}
	else if ((*it & 0xF8) == 0xF0)
	{
		codepoint = *it++ & 0x07;
		codepoint = ((codepoint << 6) | (*it++ & 0x3F));
		codepoint = ((codepoint << 6) | (*it++ & 0x3F));
		codepoint = ((codepoint << 6) | (*it++ & 0x3F));
	}

	return codepoint;
}

utf8_iterator utf8_view::begin()
{
	return utf8_iterator(ref.begin());
}

utf8_iterator utf8_view::end()
{
	return utf8_iterator(ref.end());
}

BF_END_NAMESPACE
