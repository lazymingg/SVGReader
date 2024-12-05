#ifndef _PATH_H_
#define _PATH_H_

#include "Figure.h"
#include "Point.h"
#include <gdiplus/gdipluspath.h>
#include <string>

using namespace Gdiplus;
using namespace rapidxml;

namespace MyFigure
{
    class Path : public Figure
    {
    private:
        Gdiplus::GraphicsPath path;

    public:
        friend bool isDigit(const char &c);
        friend bool isAlpha(const char &c);
        friend int extractNumber(const string &data, int &i);
        Path(xml_node<>* rootNode, Gdiplus::Graphics& graphics);
        ~Path() { path.Reset(); };
        void draw() override;
        void applyTransform() override;
    };
}

#endif