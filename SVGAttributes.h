#ifndef _SVGATTRIBUTES_H_
#define _SVGATTRIBUTES_H_

#include <string>
#include <map>
#include <iostream>
#include <Windows.h>
#include <gdiplus.h>
#include "extendLib/rapid_xml/rapidxml.hpp"
#include "Transform/Transform.h"

using namespace rapidxml;
class Attribute
{
protected:
    std::string value;

public:
    Attribute();
    Attribute(string value);
    ~Attribute();
};

class Fill : public Attribute
{
    public:
    Fill();
    Fill(string value);
    ~Fill();
};


class SVGAttributes : public Attribute
{
private:
    std::map<std::string, Attribute *> Attributes;

public:
    SVGAttributes(xml_node<> *shapeNode);
};

#endif // _SVGATTRIBUTES_H_
