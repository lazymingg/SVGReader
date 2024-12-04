#ifndef _SVG_DRAW_H_
#define _SVG_DRAW_H_

#include "ShapeHeader/Shape.h"
#include "SVGParser.h"
#include <iostream>
#include <Windows.h>
#include <gdiplus.h>
#include <objidl.h>
#include <vector>

class FigureDraw
{
private:
    Graphics &graphics;
    vector<Figure *> figures;
public:
    FigureDraw(Graphics &graphics);
    ~FigureDraw();
    void loadSVGFile(const string& filename);
    void draw();
};
#endifz