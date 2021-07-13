#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <experimental/filesystem>
#include <vector>

#include "File.h" 

class FileSystemManager
{
public:
	FileSystemManager() = default;
	~FileSystemManager() = default;

	[[nodiscard]] File* LoadFile(const char* fileName, const bool& keepOpen) const;
	[[nodiscard]] char* LoadAndGetContents(const char* fileName, const bool& keepOpen) const;
	[[nodiscard]] bool WriteFileS(const char* fileName, const std::string &fileContents) const;
	[[nodiscard]] std::string GetExecutableDirectory() const;
	[[nodiscard]] std::vector<std::string> EnumerateDirectory(const char* directory) const;
};

#endif