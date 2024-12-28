﻿#ifndef SVG_ATTRIBUTES_H
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
#include "X1.h"
#include "X2.h"
#include "Y1.h"
#include "Y2.h"
#include "Id.h"
#include "OffSet.h"
#include "StopColor.h"
using namespace rapidxml;

// singleton class for creating attributes
class AttributeFactory
{
private:
    static AttributeFactory* instance;
    std::map<std::string, Attribute*> Attributes;
    AttributeFactory();
public:
    static AttributeFactory* getInstance();
    void registerAttribute(const std::string &name, Attribute* attribute);
    Attribute* createAttribute(const std::string &name, const std::string &value);
    Attribute* createAttribute(const std::string &name);
    Attribute* getAttribute(const std::string &name);
    ~AttributeFactory();
};

class SVGAttributes
{
private:
    std::map<std::string, Attribute*> Attributes;
public:
    SVGAttributes(xml_node<> *shapeNode);
    SVGAttributes(const SVGAttributes &attributes);
    Attribute* getAttributes(std::string name);
    void mergeAttributes(SVGAttributes &attributes);
    ~SVGAttributes();
};


#endif // SVG_ATTRIBUTES_H
