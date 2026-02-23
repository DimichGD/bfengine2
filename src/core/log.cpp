#include "log.hpp"
#include "io/file.hpp"
#include <utility>
#include <unistd.h>

BF_BEGIN_NAMESPACE

Log::Destination Log::dest = Log::Destination::STDOUT;
Log::Level Log::accept_level = Log::Level::INFO;

Log::Log(const std::string_view &category, Level level)
{
	current_level = level;
	if (uint32_t(current_level) < uint32_t(accept_level))
		return;

	std::string level_string;
	switch (level)
	{
		case Level::INFO:  level_string = "[I]"; break;
		case Level::WARN:  level_string = "[W]"; break;
		case Level::ERROR: level_string = "[E]"; break;
		case Level::LOG:                         break;
	}

	if (!category.empty())
		ss << level_string << "[" << category << "]:";
}

Log::~Log()
{
	if (uint32_t(current_level) < uint32_t(accept_level))
		return;

	ss << '\n';
	const std::string &message = ss.str();

	if (std::to_underlying(dest) & std::to_underlying(Destination::STDOUT))
	{
		//write(error ? 2 : 1, message.data(), message.size()); // 1 - stdout, 2 - stderr
		auto descriptor = current_level == Level::ERROR ? stderr : stdout;
		fwrite(message.data(), message.size(), 1, descriptor);
		fflush(descriptor);
	}

	if (std::to_underlying(dest) & std::to_underlying(Destination::FILE))
	{
		File file("log.txt");
		file.Open(File::Access::APPEND);
		file.Write(message.data(), message.size());
	}
}

void Log::Init(Destination destination, Level level)
{
	dest = destination;
	accept_level = level;

	if (std::to_underlying(dest) & std::to_underlying(Destination::FILE))
	{
		// create file
	}
}

BF_END_NAMESPACE
