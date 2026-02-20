#include "file.hpp"
#include "core/log.hpp"
#include <chrono>
#include <fmt/format.h>
#include <filesystem>
#include <stdexcept>

BF_BEGIN_NAMESPACE

bool FileSystem::Create()
{
	std::array<std::string_view, 4> paths
	{
		"data/",
		"../data/",
		"../../data/",
		"../../../data/",
	};

	for (auto &p: paths)
	{
		if (std::filesystem::exists(p) && std::filesystem::is_directory(p))
		{
			data_path = p;
			break;
		}
	}

	if (data_path.empty())
	{
		Log() << "Data path not found";
		return false;
	}

	return true;
}

bool FileSystem::FileExists(const std::string &filename)
{
	return std::filesystem::exists(filename) && !std::filesystem::is_directory(filename);
}

const std::string &FileSystem::GetDataPath() const
{
	return data_path;
}


File::File(const std::string &name)
{
	this->name = name;
}

File::~File()
{
	if (file)
		fclose(file);
}

File::File(File &&other)
{
	Swap(std::move(other));
}

File &File::operator=(File &&other)
{
	Swap(std::move(other));
	return *this;
}

void File::Swap(File &&other)
{
	file = other.file;
	size = other.size;
	name = std::move(other.name);
	access = other.access;

	other.file = nullptr;
	other.size = 0;
	other.name = {};
	other.access = Access::READ;
}

bool File::Open(Access access)
{
	// TODO: check if file alreay opened and check access

	if (access == Access::READ && !std::filesystem::exists(name))
	{
		// TODO: do not write to log if not exists, write in caller side. or provide static exists function
		Log("File::Open") << "File" << name << "not found";
		return false;
	}

	const char *mode = nullptr;
	switch (access)
	{
		case Access::READ: mode = "rb"; break;
		case Access::WRITE: mode = "wb"; break;
		case Access::APPEND: mode = "ab"; break;
	}

	file = fopen(name.data(), mode);
	if (!file)
	{
		Log("File::Open") << "Failed to open" << name;
		return false;
	}

	if (access == Access::READ)
		size = std::filesystem::file_size(name);

	this->access = access;
	return true;
}

void File::Read(void *buffer, size_t count)
{
	if (!file)
		throw std::runtime_error(fmt::format("File {} is not opened", name));

	if (access != Access::READ)
		throw std::runtime_error(fmt::format("File {} is not opened for reading", name));

	if (buffer == nullptr)
		throw std::runtime_error(fmt::format("Failed to read {}, buffer is null", name));

	if (ftell(file) + count > size) // TODO: check if it's a off by one situation
		throw std::runtime_error(fmt::format("Read past end in {}", name));

	if (fread(buffer, count, 1, file) != 1)
		throw std::runtime_error(fmt::format("fread failed in {}", name));
}

void File::Write(const void *buffer, size_t count)
{
	if (!file)
		throw std::runtime_error(fmt::format("File {} is not opened", name));

	if (access != Access::WRITE && access != Access::APPEND)
		throw std::runtime_error(fmt::format("File {} is not opened for writing", name));

	if (buffer == nullptr)
		throw std::runtime_error(fmt::format("Failed to write {}, buffer is null", name));

	if (fwrite(buffer, count, 1, file) != 1)
		throw std::runtime_error(fmt::format("fwrite failed in {}", name));
}

void File::Skip(size_t count)
{
	if (!file)
		throw std::runtime_error(fmt::format("File {} is not opened", name));

	if (access != Access::READ)
		throw std::runtime_error(fmt::format("File {} is not opened for reading", name));

	if (ftell(file) + count > size) // TODO: check if it's a off by one situations
		throw std::runtime_error(fmt::format("Skip past end in {}", name));

	if (fseek(file, count, SEEK_CUR) < 0)
		throw std::runtime_error(fmt::format("fseek failed in {}", name));
}

void File::Seek(size_t offset)
{
	if (!file)
		throw std::runtime_error(fmt::format("File {} is not opened", name));

	if (access != Access::READ)
		throw std::runtime_error(fmt::format("File {} is not opened for reading", name));

	if (offset > size) // TODO: check if it's a off by one situation
		throw std::runtime_error(fmt::format("Seek past end in {}", name));

	if (fseek(file, offset, SEEK_SET) < 0)
		throw std::runtime_error(fmt::format("fseek failed in {}", name));
}

bool File::IsOpened() const
{
	return file != nullptr;
}

uint64_t File::LastWriteTime() const
{
	std::filesystem::file_time_type file_time = std::filesystem::last_write_time(name);
	auto system_time_point = std::chrono::clock_cast<std::chrono::system_clock>(file_time);
	return std::chrono::duration_cast<std::chrono::seconds>(system_time_point.time_since_epoch()).count();
}

std::vector<char> File::Read()
{
	if (size == 0)
		return {};

	std::vector<char> result(size);
	Read(result.data(), result.size());

	return result;
}

BF_END_NAMESPACE
