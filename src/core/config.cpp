#include "core/config.hpp"
#include "core/log.hpp"
#include "io/file.hpp"
#include "utils/hash.hpp"

BF_BEGIN_NAMESPACE

StreamReader::StreamReader(std::vector<char> &buffer)
{
	begin = buffer.begin();
	end = buffer.end();
	current = begin;
}

void StreamReader::SkipLine()
{
	SkipWhitespaces();

	while (current != end && *current != '\n')
		++current;
}

void StreamReader::SkipToken()
{
	SkipWhitespaces();

	while (current != end && !IsWhitespace(*current))
		++current;
}

std::string_view StreamReader::NextToken()
{
	SkipWhitespaces();

	auto it = current;
	while (current != end && !IsWhitespace(*current))
		++current;

	return { it, current };
}

int StreamReader::NextInt()
{
	int value = 0;
	std::string_view token = NextToken();

	std::from_chars_result result = std::from_chars(token.begin(), token.end(), value);
	if (result.ec != std::errc())
	{
		Log() << "Failed to convert" << token << "to int";
		return 0;
	}

	return value;
}

std::string_view StreamReader::NextString()
{
	std::string_view token = NextToken();
	// Read from quote to quote
	return { token.begin() + 1, token.end() - 1 };
}

void StreamReader::SkipWhitespaces()
{
	while (current != end && IsWhitespace(*current))
		++current;
}

bool StreamReader::IsWhitespace(char symbol)
{
	return symbol == ' ' || symbol == '\n' || symbol == '\t' || symbol == '\r' || symbol == 0;
}


/*class ConfigReader: public StreamReader
{
public:
	bool ReadInt(std::string_view name, int &value)
	{
		if (NextToken() != name)
			return false;

		return true;
	}
};*/


bool Config::Load()
{
	File file("system.cfg");
	if (!file.Open())
	{
		Log("Config::Load") << "Failed to load config, using default";
		return false;
	}

	auto content = file.Read();
	StreamReader reader(content);

	for (std::string_view name = reader.NextToken(); !name.empty(); name = reader.NextToken())
	{
		if (name == "width")
			window.width = reader.NextInt();

		else if (name == "height")
			window.height = reader.NextInt();

		else
			Log("Config::Load") << "Unknown name" << name;
	}

	return true;
}

bool Config::Save()
{
	File file("system.cfg");
	if (!file.Open(File::Access::WRITE))
	{
		Log("Config::Save") << "Failed to save config";
		return false;
	}

	std::string str =
R"(width 800
height 600)";

	file.Write(str.data(), str.size());

	return true;
}



BF_END_NAMESPACE
