#include "File.h"

/**
 * \brief Initialises this file class, as well as opening the file.
 * \param _fileName The file name to open. Relative to current working directory.
 * \param keepOpen Whether or not we want to keep the file open (e.g. for log files).
 */
File::File(const char* _fileName, const bool &keepOpen) : fileName(_fileName) {
	Open();

	if (!keepOpen)
		fileHandle.close();
}

/**
 * \brief Finds if the file is closed on disk, or locked.
 * \return Whether or not the file is closed.
 */
bool File::GetIsClosedOnDisk() const
{
	return !fileHandle.is_open();
}

/**
 * \brief Opens the file, and writes its contents to the fileContents variable.
 * \param appendMode Whether we need to open the file in append mode, for writing to it later.
 */
void File::Open(const bool& appendMode) {
	if (!GetIsClosedOnDisk()) {
		std::cout << "Charon : WARN: Filesystem attempted to open a file that is already open.";
		return;
	}

	try
	{
		if (appendMode)
			fileHandle.open(fileName, std::ios::app | std::ios::out | std::ios::in);
		else
			fileHandle.open(fileName, std::ios::out | std::ios::in);

		std::string line, text;
		while (std::getline(fileHandle, line))
			text += line;

		fileContents = text;
	}
	catch (std::fstream::failure &exception)
	{
		std::cout << "Error: failed to open file (code " << exception.code() << "): " << exception.what() << "\n";
	}
	
}

/**
 * \brief Closes and re-opens the file lock.
 * \param appendMode Whether we need to open the file in append mode.
 */
void File::Reload(const bool &appendMode = false) {
	Close();
	Open(appendMode);
}

/**
 * \brief Write the given contents to the file.
 * \param contents The contents to be written to the file.
 * \param append Whether or not the given contents need to be appended to the file instead of overwriting it.
 */
void File::Write(const char* contents, const bool& append) {
	if (append)
		Reload(true);

	if (GetIsClosedOnDisk())
		Open(false);

	fileHandle << contents;
	//fileHandle.write(contents, sizeof(char) * sizeof(contents));
	fileHandle.flush();

	if (!append)
		fileHandle.close();
}
