#pragma once
#include "core/defines.hpp"
#include <cstdint>
#include <string>
#include <cstdio>
#include <vector>

BF_BEGIN_NAMESPACE

class FileSystem
{
public:
	FileSystem() = default;
	BF_NON_MOVABLE(FileSystem)
	BF_NON_COPYABLE(FileSystem)

	bool Create();
	bool FileExists(const std::string &filename);
	const std::string &GetDataPath() const;

private:
	std::string data_path;
};

class File
{
public:
	enum class Access
	{
		READ, WRITE, APPEND,
	};

	/*enum class Result
	{
		SUCCESS, NOT_FOUND, FAILED_TO_OPEN,
	};*/

	File(const std::string &name);
	~File();

	BF_NON_COPYABLE(File)
	File(File &&other);
	File &operator=(File &&other);

	bool Open(Access access = File::Access::READ);
	void Read(void *buffer, size_t count);
	void Write(const void *buffer, size_t count);
	void Skip(size_t count);
	void Seek(size_t offset);
	bool IsOpened() const;
	uint64_t LastWriteTime() const;

	template<typename T>
	void Read(T *t)
	{
		Read(t, sizeof(T));
	}

	std::vector<char> Read();

	size_t Pos() const { return ftell(file); }
	size_t Size() const { return size; }
	std::string_view Name() const { return name; }

private:
	void Swap(File &&other);

private:
	std::string name {};
	size_t size = 0;
	std::FILE *file = nullptr;
	Access access = File::Access::READ;
};

BF_END_NAMESPACE
