#ifndef _SVGATTRIBUTES_H_
#define _SVGATTRIBUTES_H_

#include <string>
#include <map>
#include <iostream>
#include <Windows.h>
#include <gdiplus.h>
#include "extendLib/rapid_xml/rapidxml.hpp"
#include "Transform/Transform.h"
#include <memory>
#include <regex>
using namespace rapidxml;
class Attribute
{
public:
    virtual Attribute* clone() = 0;
    
};

class Fill : public Attribute
{
private:
    Gdiplus::Color color;
public:
    Fill();
    Fill(string value);
    Gdiplus::Color getFill();
    Attribute* clone() override;
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
    Attribute* clone() override;
    ~Stroke();
};

class StrokeWidth : public Attribute
{
private:
    float width;

public:
    StrokeWidth();
    StrokeWidth(string width);
    float getStrokeWidth();
    Attribute* clone() override;
    ~StrokeWidth();
};

class Ocopacity : public Attribute
{
private:
    float value;

public:
    Ocopacity();
    Ocopacity(string value);
    float getOcopacity();
    Attribute* clone() override;
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
    Attribute* clone() override;
    ~Text();
};

class FillOpacity : public Attribute
{
private:
    float value;
public:
    FillOpacity();
    FillOpacity(string value);
    float getFillOpacity();
    Attribute* clone() override;
    ~FillOpacity();
};

class StrokeOpacity : public Attribute
{
private:
    float value;
public:
    StrokeOpacity();
    StrokeOpacity(string value);
    float getStrokeOpacity();
    Attribute* clone() override;
    ~StrokeOpacity();
};



class SVGAttributes : public Attribute
{
private:
    std::map<std::string, Attribute*> Attributes;

public:
    SVGAttributes(xml_node<> *shapeNode);
    SVGAttributes(const SVGAttributes &attributes);+
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


    ~SVGAttributes();
};

#endif // _SVGATTRIBUTES_H_
