#ifndef _PATH_H_
#define _PATH_H_

#include "LineSegment.h"
#include "CubicBezierSegment.h"
#include "QuadraticBezierSegment.h"
#include "EllipticalArcCurveSegment.h"

using namespace Gdiplus;
using namespace rapidxml;

namespace MyFigure
{
    class Path : public Figure
    {
    private:
        Gdiplus::GraphicsPath path;

    public:
        Path(xml_node<>* rootNode, Gdiplus::Graphics& graphics);
        ~Path() { path.Reset(); };
        void draw() override;
    };
}

#endif