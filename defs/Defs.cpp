#include "Defs.h"



Defs * Defs::getInstance()
{
    if (instance == nullptr)
    {
        instance = new Defs();
    }
    return instance;
}

void Defs::setDefsNode(rapidxml::xml_node<>* defsNode)
{
    this->defsNode = defsNode;
    // Read all child nodes of defs node
    rapidxml::xml_node<>* childNode = defsNode->first_node();
    while (childNode != nullptr)
    {
        std::string nodeName = childNode->name();
        std::string nodeValue = childNode->value();
        //using defsFactory to create tag
        DefsTagFactory defsFactory;
        DefsTag* tag = defsFactory.createTag(nodeName, childNode);
        if (tag != nullptr)
        {
            cout << " find 1 tag in def " << nodeName << endl;
            // cout << " tag value " << nodeValue << endl;
            defsMap[nodeName] = tag;
        }
        else
        {
            std::cout << "invalid Defs: " << nodeName << std::endl;
        }
        childNode = childNode->next_sibling();

    }
}

DefsTag* Defs::getDefsTag(std::string tagName)
{
    if (defsMap.find(tagName) == defsMap.end())
    {
        std::cout << "Tag not found: " << tagName << std::endl;
        return nullptr;
    }
    return defsMap[tagName];
}

std::map<std::string,DefsTag*> Defs::getDefsMap()
{
    return defsMap;
}

void Defs::printDefs()
{
    for (auto &tag : defsMap)
    {
        std::cout << tag.first << std::endl;
    }
}

Defs::~Defs()
{
    for (auto &tag : defsMap)
    {
        delete tag.second;
    }

    defsMap.clear();
    delete instance;
}

Defs::Defs()
{
    defsNode = nullptr;
}


