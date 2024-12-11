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


using namespace rapidxml;

class SVGAttributes
{
private:
    std::map<std::string, Attribute*> Attributes;

public:
    SVGAttributes(xml_node<> *shapeNode);
    SVGAttributes(const SVGAttributes &attributes);
    float getStrokeWidth();
    float getOpacity();
    float getFillOpacity();
    float getStrokeOpacity();
    Transform getTransform();
    Gdiplus::Color getFillColor();
    Gdiplus::Color getStrokeColor();
    float getFontSize();
    Gdiplus::FontFamily* getFontFamily();
    Gdiplus::FontStyle getFontStyle();
    std::string getTextAnchor();
    void printAttributes();
    void mergeAttributes(SVGAttributes &attributes);
    ~SVGAttributes();
};

#endif // SVG_ATTRIBUTES_H
