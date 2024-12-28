#ifndef _DEFS_TAG_FACTORY_H_
#define _DEFS_TAG_FACTORY_H_

#include <iostream>
#include <map>
#include <string>
#include "LinearGradient/LinearGradient.h"
#include "defsTag.h"

using namespace std;


class DefsTagFactory
{
    private:
        std::map<std::string, DefsTag*> tagMap;
    public:
        DefsTagFactory();
        DefsTag* createTag(std::string tagName, rapidxml::xml_node<> *tagData);
        void registerTag(std::string tagName, DefsTag* tag);
        ~DefsTagFactory();
};

#endif