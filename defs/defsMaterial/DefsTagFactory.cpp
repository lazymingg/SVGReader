#include "DefsTagFactory.h"

DefsTagFactory::DefsTagFactory()
{
    registerTag("linearGradient", new LinearGradient());
}

DefsTag *DefsTagFactory::createTag(std::string tagName, rapidxml::xml_node<> *tagData)
{
    if (tagMap.find(tagName) == tagMap.end())
    {
        std::cout << "Tag not found: " << tagName << std::endl;
        return nullptr;
    }
    return tagMap[tagName]->clone(tagData);
}

