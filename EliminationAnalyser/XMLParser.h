#ifndef XMLPARSER_H
#define XMLPARSER_H

#include <string>

#include "FileSystem.h"
#include "rapidxml-1.13/rapidxml.hpp"

class XMLParser
{
public:
    XMLParser(std::shared_ptr<FileSystemManager> _IFileSystemManager) : IFileSystemManager(_IFileSystemManager) { }
    ~XMLParser() = default;

    std::shared_ptr<rapidxml::xml_document<>> ParseXML(const std::string& path) const;

private:
    std::shared_ptr<FileSystemManager> IFileSystemManager = nullptr;
};
#endif