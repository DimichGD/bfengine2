#include "log.hpp"
#include "io/file.hpp"
#include <utility>
#include <unistd.h>

BF_BEGIN_NAMESPACE

Log::Destination Log::dest = Log::Destination::STDOUT;

Log::Log(const std::string_view &category, bool error)
{
	this->error = error;

	if (!category.empty())
	{
		ss << "[" << category << "]:";
	}
}

Log::~Log()
{
	ss << '\n';
	const std::string &message = ss.str();

	if (std::to_underlying(dest) & std::to_underlying(Destination::STDOUT))
	{
		//write(error ? 2 : 1, message.data(), message.size()); // 1 - stdout, 2 - stderr
		auto descriptor = error ? stderr : stdout;
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

void Log::Init(Destination destination)
{
	dest = destination;

	if (std::to_underlying(dest) & std::to_underlying(Destination::FILE))
	{
		// create file
	}
}

BF_END_NAMESPACE
