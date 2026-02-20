#pragma once
#include "core/defines.hpp"
#include <cstdint>
#include <string_view>
#include <vector>

BF_BEGIN_NAMESPACE


class StreamReader
{
public:
	StreamReader(std::vector<char> &buffer);
	BF_NON_COPYABLE(StreamReader)
	BF_NON_MOVABLE(StreamReader)

	void SkipLine();
	void SkipToken();

	std::string_view NextToken();
	//bool NextTokenExpected(std::string_view expected_token);
	//void Expect(std::string_view expected_token);

	int NextInt();
	//float NextFloat();
	std::string_view NextString();

protected:
	void SkipWhitespaces();
	bool IsWhitespace(char symbol);

private:
	std::vector<char>::iterator begin;
	std::vector<char>::iterator end;
	std::vector<char>::iterator current;
};



struct Config
{
	struct Render
	{
		enum class API
		{
			VK, GL,
		};

		API api = API::GL;
		bool debug = true;
	};

	struct Window
	{
		uint32_t width = 800;
		uint32_t height = 600;
		uint32_t monitor = 0;
		uint32_t swap_interval = 1;
	};

	Window window;
	Render render;

	//uint32_t width = 800;
	//uint32_t height = 600;

	bool Load();
	bool Save();
};

BF_END_NAMESPACE
