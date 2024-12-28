#ifndef _STOP_COLOR_H_
#define _STOP_COLOR_H_

#include "Stroke.h"
class StopColor : public Attribute
{
private:
    Gdiplus::Color color;   // color value
public:
    StopColor();
    StopColor(std::string value);
    Gdiplus::Color getStopColor();
    Attribute* clone() override;
    Attribute* clone(std::string value) override;
    void mergeData(Attribute* attribute) override;
    ~StopColor();
};

#endif