#ifndef _SVG_DRAW_H_
#define _SVG_DRAW_H_

#include "ShapeHeader/Shape.h"
#include "SVGParser.h"
#include <iostream>
#include <Windows.h>
#include <gdiplus.h>
#include <objidl.h>
#include <vector>
#include "defs/Defs.h"
class FigureDraw
{
private:
    Graphics &graphics;
    vector<Figure *> figures;
    double svgWidth;            // Chiều rộng của SVG
    double svgHeight;           // Chiều cao của SVG
    string svgViewBox;     // Chuỗi viewBox của SVG
public:
    FigureDraw(Graphics &graphics);
    ~FigureDraw();
    void loadSVGFile(const string& filename);
    array<double, 4> parseViewBox(const std::string &viewBoxStr);
    void draw();
};
#endif