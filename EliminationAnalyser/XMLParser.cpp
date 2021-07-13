#include "XMLParser.h"

#include "rapidxml-1.13/rapidxml.hpp"

std::shared_ptr<rapidxml::xml_document<>> XMLParser::ParseXML(const std::string& path) const
{
    std::shared_ptr<rapidxml::xml_document<>> doc = std::make_shared<rapidxml::xml_document<>>();

    const auto file_buffer = IFileSystemManager->LoadAndGetContents(path.c_str(), false);

    if (file_buffer != nullptr)
    {
	    doc->parse<rapidxml::parse_no_entity_translation>(file_buffer);
        return doc;
    }

    return nullptr;
}
