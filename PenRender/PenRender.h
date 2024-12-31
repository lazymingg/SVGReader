#ifndef _PenRender_H_
#define _PenRender_H_

#include "../Attributes/SVGAttributes.h"
#include "../defs/Defs.h"
#include "PenLinear.h"  

//this class will based on the SVGAttributes class
class PenRender
{
public:
    //Get a solidBrush, a solidPen and a pen from linearGradient
    PenRender();
    ~PenRender();
    Gdiplus::SolidBrush *getSolidBrush(SVGAttributes &attributes);
    Gdiplus::Pen *getSolidPen(SVGAttributes &attributes);
    LinearGradientManager *getPenLinear(std::string ID, SVGAttributes &attributes);
};

#endif