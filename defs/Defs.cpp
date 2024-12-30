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
<<<<<<< HEAD
            cout << " tag value " << nodeValue << endl;
            defsMap[nodeName] = tag;
=======
            // cout << " tag value " << nodeValue << endl;
            defsMap[nodeName].push_back(tag);
>>>>>>> 4534dd95f8ba05792504bc87df0fbb7afea6e574
        }
        else
        {
            std::cout << "invalid Defs: " << nodeName << std::endl;
        }
        childNode = childNode->next_sibling();
    }
}

vector<DefsTag*> Defs::getDefsTag(std::string tagName)
{
    if (defsMap.find(tagName) == defsMap.end())
    {
        std::cout << "Tag not found: " << tagName << std::endl;
        return {};
    }
    return defsMap[tagName];
}

std::map<std::string,vector<DefsTag*>> Defs::getDefsMap()
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
        for (auto &tagItem : tag.second)
        {
            delete tagItem;
        }
    }
    defsMap.clear();
    delete instance;
    instance = nullptr;
}

Defs::Defs()
{
    defsNode = nullptr;
}


