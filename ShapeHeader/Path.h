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
    class PathSegment
    {
    protected:
        Gdiplus::GraphicsPath segment;

    public:
        virtual void setSegment(const string &data, int& i) = 0;
        Gdiplus::GraphicsPath& getSegment() { return this->segment; }
    };

    class PathSegmentM
    {

    };

    class Path : public Figure
    {
    private:
        Gdiplus::GraphicsPath path;

    public:
        friend bool isDigit(const char &c);
        friend bool isAlpha(const char &c);
        friend float extractNumber(const string &data, int &i);
        Path(xml_node<>* rootNode, Gdiplus::Graphics& graphics);
        ~Path() { path.Reset(); };
        void draw() override;
        void applyTransform() override;
    };
}

#endif