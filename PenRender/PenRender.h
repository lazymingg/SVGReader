#ifndef _PenRender_H_
#define _PenRender_H_

#include "../Attributes/SVGAttributes.h"
#include <Defs/Defs.h>

//this class will based on the SVGAttributes class
class PenRender
{
private:
    SVGAttributes attributes;
public:
    //Get a solidBrush, a solidPen and a pen from linearGradient
    PenRender(SVGAttributes attributes);
    ~PenRender();

    Gdiplus::SolidBrush *getSolidBrush();
    Gdiplus::Pen *getSolidPen();
    Gdiplus::Pen *getPenLinear(std::string ID);
};

#endif