#ifndef STROKEOPACITY_H
#define STROKEOPACITY_H

#include "Attribute.h"
#include <string>

// StrokeOpacity class for handling stroke-opacity attributes
class StrokeOpacity : public Attribute
{
private:
    float value;

public:
    StrokeOpacity();
    StrokeOpacity(std::string getValue);
    float getStrokeOpacity();
    Attribute* clone() override;
    Attribute* clone(string value) override;
    void mergeData(Attribute* attribute) override;
    ~StrokeOpacity();
};

#endif // STROKEOPACITY_H
