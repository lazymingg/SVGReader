#ifndef STROKE_H
#define STROKE_H

#include "Attribute.h"
#include <string>
#include <Gdiplus.h>

// Stroke class for handling stroke color attributes
class Stroke : public Attribute
{
private:
    Gdiplus::Color color;

public:
    Stroke();
    Stroke(std::string value);
    Gdiplus::Color getStroke();
    Attribute* clone() override;
    Attribute* clone(string value) override;
    void mergeData(Attribute* attribute) override;
    ~Stroke();
};

#endif // STROKE_H
