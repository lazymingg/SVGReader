#ifndef _DEFS_H_
#define _DEFS_H_
#include "../extendLib/rapid_xml/rapidxml.hpp"
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <regex>
#include "defsMaterial/DefsTagFactory.h"
// Defs reader
class Defs 
{
private:
    static Defs* instance;
    Defs();
    Defs(const Defs&) = delete;
    Defs& operator=(const Defs&) = delete;
    std::map<std::string, DefsTag*> defsMap;
    rapidxml::xml_node<> *defsNode;
public:
    static Defs* getInstance();
    void setDefsNode(rapidxml::xml_node<> *defsNode);
    DefsTag* getDefsTag(std::string tagName);
    std::map<std::string, DefsTag*> getDefsMap();
    void printDefs();
    ~Defs();
};


#endif