#ifndef _FIGURE_H_
#define _FIGURE_H_

#include "../extendLib/rapid_xml/rapidxml.hpp"
#include "../SVGAttributes.h"
#include <windows.h>
#include <gdiplus.h>
#include <objidl.h>
#include <iostream>
#include "../Transform/Transform.h"

#pragma comment(lib, "Gdiplus.lib")

// using namespace std;
using namespace rapidxml;

class Figure
{
protected:
    xml_node<> *shapeNode;
    SVGAttributes attributes; // no default constructor must be initilized
    Gdiplus::Graphics &graphics;
public:
    Figure(xml_node<> *shapeNode, Gdiplus::Graphics &graphics);
    SVGAttributes& getAttributes();
    virtual void draw() = 0;
    virtual void applyTransform() = 0;
};

#endif