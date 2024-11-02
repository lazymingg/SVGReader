#ifndef _SVG_PARSER_H_
#define _SVG_PARSER_H_

#include <string>
#include <iostream>
#include <fstream>
#include "extendLib\rapid_xml\rapidxml.hpp"
#include <cstring>

using namespace rapidxml;
using namespace std;

class SVGParser
{
private:
    xml_document<> doc;
    xml_node<>* root_node;
    char* buffer;
    
public:
    SVGParser(const string& filename);
    ~SVGParser();
	xml_node<>* getRootNodeName(string nodeName);
	xml_node<>* getRootNode();
    void print();
};


#endif