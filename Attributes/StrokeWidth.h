#ifndef STROKEWIDTH_H
#define STROKEWIDTH_H

#include "Attribute.h"

// StrokeWidth class for handling stroke width attributes
class StrokeWidth : public Attribute
{
private:
    float width;

public:
    StrokeWidth();
    StrokeWidth(std::string width);
    float getStrokeWidth();
    Attribute* clone() override;
    Attribute* clone(string value) override;
    void mergeData(Attribute* attribute) override;
    ~StrokeWidth();
};

#endif // STROKEWIDTH_H
