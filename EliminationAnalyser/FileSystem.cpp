#include "FileSystem.h"

/**
* \brief Loads the given file and returns its File instance.
* \param fileName The file name to load. Is relative to current working directory.
* \param keepOpen States if we need to keep the file open (e.g. for log files that are constantly written to). This locks the file until closed.
* \return An instance of File, representing the file.
*/
File* FileSystemManager::LoadFile(const char* fileName, const bool &keepOpen) const {
	char newPath[MAX_PATH] = "";
	PathCombineA(newPath, GetExecutableDirectory().c_str(), fileName);

	return std::make_shared<File>(newPath, keepOpen).get();
}

/**
 * \brief Loads the given file and returns its contents.
 * \param fileName The file name to load. Is relative to current working directory.
 * \param keepOpen States if we need to keep the file open (e.g. for log files that are constantly written to). This locks the file until closed.
 * \return A character array containing the file's contents.
 */
char* FileSystemManager::LoadAndGetContents(const char* fileName, const bool& keepOpen) const {
	File* file = LoadFile(fileName, keepOpen);

	return file != nullptr ? const_cast<char*>(file->GetContents()) : nullptr;
}

/**
 * \brief Writes the given character array (string) to file.
 * \param fileName The file name to write to. Will overwrite the file if it already exists. Is relative to current working directory.
 * \param fileContents The character array to write.
 * \return Whether the operation has succeeded or failed.
 */
bool FileSystemManager::WriteFileS(const char* fileName, const std::string &fileContents) const
{
	File* file = LoadFile(fileName, true);
	
	if (file != nullptr)
	{
		std::ofstream fstream;
		fstream.open(file->GetName());

		fstream << fileContents;
		fstream.close();
		
		// TODO: FIXME
		//file->Write(fileContents, false);
		return true;
	}
	
	return false;
}

/**
 * \brief Retrieves the file names within a directory.
 * \param directory The directory name to check. Is relative to current working directory.
 * \return A vector of string containing all file names within the given directory.
 */
std::vector<std::string> FileSystemManager::EnumerateDirectory(const char* directory) const
{
	std::vector<std::string> results;
	char newPath[MAX_PATH] = "";

	PathCombineA(newPath, GetExecutableDirectory().c_str(), directory);

	if (std::experimental::filesystem::exists(newPath))
	{
		for (const auto& entry : std::experimental::filesystem::directory_iterator(newPath))
			results.push_back(entry.path().string());
	}

	return results;
}

//https://gist.github.com/karolisjan/f9b8ac3ae2d41ec0ce70f2feac6bdfaf
/**
 * \brief Find the current working directory.
 * \return A string containing the full current working directory.
 */
std::string FileSystemManager::GetExecutableDirectory() const
{
	char buffer[MAX_PATH];
	GetModuleFileNameA(nullptr, buffer, MAX_PATH);

	return std::string(buffer).substr(0, std::string(buffer).find_last_of("\\/"));
}