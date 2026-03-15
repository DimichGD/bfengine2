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
	enum class Level
	{
		INFO,
		WARN,
		ERROR, // ERROR conflicts with windows.h
		LOG,
	};

	enum class Destination
	{
		STDOUT = 1,
		FILE   = 2,
		BOTH   = STDOUT | FILE,
	};

	Log(const std::string_view &category = {}, Level level = Level::LOG);
	~Log();

	static void Init(Destination destination = Destination::STDOUT, Level level = Level::INFO);

	template<typename T>
	Log &operator<<(const T &t)
	{
		if (uint32_t(current_level) < uint32_t(accept_level))
			return *this;

		if (ss.rdbuf()->in_avail())
			ss << ' ';

		ss << t;
		return *this;
	}

	template<typename T>
	Log &operator<<(const std::vector<T> &t)
	{
		if (uint32_t(current_level) < uint32_t(accept_level))
			return *this;

		*this << "[";

		for (auto &v: t)
			*this << v;

		*this << "]";

		return *this;
	}

	template<typename T>
	Log &operator<<(const std::span<T> &t)
	{
		if (uint32_t(current_level) < uint32_t(accept_level))
			return *this;

		*this << "[";

		for (auto &v: t)
			*this << v;

		*this << "]";

		return *this;
	}

protected:
	static constexpr std::string_view Trim(const char *function_name)
	{
		std::string_view name(function_name);
		name = name.substr(0, name.find('('));
		return name.substr(name.find_last_of(' ') + 1);
	}

private:
	static Destination dest;
	static Level accept_level;
	std::stringstream ss {};
	Level current_level = Level::INFO;
};

class Info: public Log
{
public:
	constexpr Info(std::source_location loc = std::source_location::current()):
		Log(Log::Trim(loc.function_name()), Level::INFO) {}
};

class Warn: public Log
{
public:
	constexpr Warn(std::source_location loc = std::source_location::current()):
		Log(Log::Trim(loc.function_name()), Level::WARN) {}
};

class Error: public Log
{
public:
	constexpr Error(std::source_location loc = std::source_location::current()):
		Log(Log::Trim(loc.function_name()), Level::ERROR) {}
};

BF_END_NAMESPACE
