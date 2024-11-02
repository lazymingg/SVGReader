#ifndef _SVG_DRAW_H_
#define _SVG_DRAW_H_

#include "ShapeHeader/Shape.h"
#include "SVGParser.h"
#include "SVGAttributes.h"
#include <iostream>
#include <Windows.h>
#include <gdiplus.h>
#include <objidl.h>
#include <vector>

class SVGDraw
{
private:
    Graphics &graphics;
    vector<Figure *> figures;
public:
    SVGDraw(Graphics &graphics);
    ~SVGDraw();
    void loadSVGFile(const string& filename);
    void draw();
};
#endif