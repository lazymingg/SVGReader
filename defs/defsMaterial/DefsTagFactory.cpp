#include "DefsTagFactory.h"

DefsTagFactory::DefsTagFactory()
{
    registerTag("linearGradient", new LinearGradient(nullptr));
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

void DefsTagFactory::registerTag(std::string tagName, DefsTag *tag)
{
    tagMap[tagName] = tag;
}

DefsTagFactory::~DefsTagFactory()
{
    for (auto &tag : tagMap)
    {
        delete tag.second;
    }

    tagMap.clear();
}
