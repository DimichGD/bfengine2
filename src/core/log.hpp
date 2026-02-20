#pragma once
#include "core/defines.hpp"
#include <string_view>
#include <vector>
#include <sstream>
#include <source_location>

BF_BEGIN_NAMESPACE

class Log
{
public:
	enum class Destination
	{
		STDOUT = 1,
		FILE   = 2,
		BOTH   = STDOUT | FILE,
	};

	Log(const std::string_view &category = {}, bool error = false);
	~Log();

	static void Init(Destination destination = Destination::STDOUT);

	template<typename T>
	Log &operator<<(const T &t)
	{
		if (ss.rdbuf()->in_avail())
			ss << ' ';

		ss << t;
		return *this;
	}

	template<typename T>
	Log &operator<<(const std::vector<T> &t)
	{
		*this << "[";

		for (auto &v: t)
			*this << v;

		*this << "]";

		return *this;
	}

	/*template<typename T>
	Log &operator<<(const std::span<T> &t)
	{
		*this << "[";

		for (auto &v: t)
			*this << v;

		*this << "]";

		return *this;
	}*/

private:
	static Destination dest;
	std::stringstream ss {};
	bool error = false;
	//std::string buffer {};
	//size_t cursor = 0;
};

class Error: public Log
{
public:
	constexpr Error(std::source_location loc = std::source_location::current()):
		Log(Trim(loc.function_name()), true) {}

private:
	static constexpr std::string_view Trim(const char *function_name)
	{
		std::string_view name(function_name);
		size_t start = name.find(' ') + 1;
		size_t end = name.find('(');
		return name.substr(start, end - start);
	}
};

BF_END_NAMESPACE
