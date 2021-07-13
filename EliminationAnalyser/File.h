#ifndef FILE_H
#define FILE_H

#include <fstream>
#include <sstream>
#include <iostream>

class File
{
public:
	explicit File(const char* _fileName, const bool &keepOpen = false);
	~File() = default;

	const char* GetContents() const { return fileContents.c_str(); }
	std::string GetName() const { return fileName; }
	bool GetIsClosedOnDisk() const;

	void Close() { if (!GetIsClosedOnDisk()) fileHandle.close(); }
	void Open(const bool& appendMode = false);
	void Reload(const bool& appendMode);
	void Write(const char* contents, const bool &append = false);
private:
	std::string fileName;
	std::string fileContents;

	std::fstream fileHandle;
};

#endif