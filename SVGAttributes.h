﻿#ifndef _SVGATTRIBUTES_H_
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
};

class SVGAttributes
{
private:
    std::map<std::string, Attribute *> Attributes;

public:
    // Constructor
    SVGAttributes(xml_node<> *shapeNode);

    // Getters and setters
    void setFill(const std::string &color);
    std::string getFill() const;

    void setStroke(const std::string &color);
    std::string getStroke() const;

    void setStrokeWidth(float width);
    float getStrokeWidth() const;

    void setOpacity(float value);
    float getOpacity() const;

    void setFillOpacity(float value);
    float getFillOpacity() const;

    void setStrokeOpacity(float value);
    float getStrokeOpacity() const;

    void setStrokeLinecap(const std::string &cap);
    std::string getStrokeLinecap() const;

    void setStrokeLinejoin(const std::string &join);
    std::string getStrokeLinejoin() const;

    void setStrokeDasharray(const std::string &dash);
    std::string getStrokeDasharray() const;

    Transform getTransform();

    // Print attributes
    void printAttributes() const;

    void setFillColor(std::string str);
    Gdiplus::Color getFillColor() const;

    void setStrokeColor(std::string str);
    Gdiplus::Color getStrokeColor() const;

    void setText(std::string tex);
    std::string getText() const;

    void mergeAttributes(SVGAttributes &attr);
};

#endif // _SVGATTRIBUTES_H_
