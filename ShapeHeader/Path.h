#ifndef _PATH_H_
#define _PATH_H_

#include "Figure.h"
#include "Point.h"
#include <gdiplus/gdipluspath.h>
#include <string>
#include <cmath>
#include <vector>

using namespace Gdiplus;
using namespace rapidxml;

#define PI 3.14159265358979323846

namespace MyFigure
{
    class Path : public Figure
    {
    private:
        Gdiplus::GraphicsPath path;

    public:
        float CalculateVectorAngle(float ux, float uy, float vx, float vy);
        Path(xml_node<>* rootNode, Gdiplus::Graphics& graphics);
        ~Path() { path.Reset(); };
        void draw() override;
    };
}

#endif