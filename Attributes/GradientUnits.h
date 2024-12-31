#ifndef _GRADIENT_UNITS_H_
#define _GRADIENT_UNITS_H_

#include "Attribute.h"
#include <string>

class GradientUnits : public Attribute
{
private:
    std::string units;

public:
    GradientUnits();
    GradientUnits(std::string value);
    std::string getUnits();
    Attribute* clone() override;
    Attribute* clone(std::string value) override;
    void mergeData(Attribute* attribute) override;
    std::string toString() override;
    ~GradientUnits();
};

#endif