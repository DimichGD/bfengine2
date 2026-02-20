#pragma once
#include "core/defines.hpp"
#include <string_view>
#include <cstdint>

BF_BEGIN_NAMESPACE

constexpr uint64_t FNV1A(const char *data, size_t len)
{
	// https://en.wikipedia.org/wiki/Fowler–Noll–Vo_hash_function
	// https://gist.github.com/ruby0x1/81308642d0325fd386237cfa3b44785c
	uint64_t hash = 0xcbf29ce484222325;
	uint64_t prime = 0x100000001b3;

	for(size_t i = 0; i < len; i++)
	{
		hash = hash ^ uint8_t(data[i]);
		hash *= prime;
	}

	return hash;
}

constexpr uint64_t FNV1A(std::string_view string)
{
	return FNV1A(string.data(), string.size());
}

/*uint64_t FNV1A(char *data, size_t len)
{
	uint64_t hash = 0xcbf29ce484222325;
	uint64_t prime = 0x100000001b3;

	for(size_t i = 0; i < len; i++)
	{
		hash = hash ^ uint8_t(data[i]);
		hash *= prime;
	}

	return hash;
}*/

BF_END_NAMESPACE
