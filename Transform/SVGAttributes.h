#ifndef SVG_ATTRIBUTES_H
#define SVG_ATTRIBUTES_H

#include <string>
#include <map>
#include <iostream>
#include <Windows.h>
#include <gdiplus.h>
#include <memory>
#include <regex>
#include "../extendLib/rapid_xml/rapidxml.hpp"
#include "Attribute.h"
#include "Transform.h"
#include "Stroke.h"
#include "StrokeWidth.h"
#include "Fill.h"
#include "FillOcopacity.h"
#include "StrokeOcopacity.h"
#include "FontSize.h"
#include "MyFontFamily.h"
#include "MyFontStyle.h"
#include "Ocopacity.h"
#include "TextAnchor.h"
#include "Dx.h"
#include "Dy.h"

using namespace rapidxml;


class AttributeFactory
{
private:
    std::map<std::string, Attribute*> Attributes;
public:
    AttributeFactory();
    void registerAttribute(const std::string &name, Attribute* attribute);
    Attribute* createAttribute(const std::string &name, const std::string &value);
    Attribute* createAttribute(const std::string &name);
    Attribute* getAttribute(const std::string &name);
    ~AttributeFactory();
};

class SVGAttributes
{
private:
    std::map<std::string, Attribute*> Attributes;\
    AttributeFactory factory;

public:
    SVGAttributes(xml_node<> *shapeNode);
    SVGAttributes(const SVGAttributes &attributes);
    Attribute* getAttributes(std::string name);
    void mergeAttributes(SVGAttributes &attributes);
    ~SVGAttributes();
};


#endif // SVG_ATTRIBUTES_H
