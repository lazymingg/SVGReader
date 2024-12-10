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
};

class Fill : public Attribute
{
private:
    Gdiplus::Color color;

public:
    Fill();
    Fill(string value);
    Gdiplus::Color getFill();
    ~Fill();
};

class Stroke : public Attribute
{
private:
    Gdiplus::Color color;

public:
    Stroke();
    Stroke(string value);
    Gdiplus::Color getStroke();
    ~Stroke();
};

class StrokeWidth : public Attribute
{
private:
    float width;

public:
    StrokeWidth();
    StrokeWidth(float width);
    float getStrokeWidth();
    ~StrokeWidth();
};

class Ocopacity : public Attribute
{
private:
    float value;

public:
    Ocopacity();
    Ocopacity(float value);
    float getOcopacity();
    ~Ocopacity();
};

class Text : public Attribute
{
private:
    string text;

public:
    Text();
    Text(string text);
    string getText();
    ~Text();
};


class SVGAttributes : public Attribute
{
private:
    std::map<std::string, Attribute> Attributes;

public:
    // Constructor
    SVGAttributes(xml_node<> *shapeNode);

    float getStrokeWidth();
    float getOpacity();
    float getFillOpacity();
    float getStrokeOpacity();
    Transform getTransform();

    // Print attributes
    void printAttributes();
    Gdiplus::Color getFillColor();
    Gdiplus::Color getStrokeColor();
    std::string getText();
};

#endif // _SVGATTRIBUTES_H_
