#ifndef X2_H
#define X2_H

#include "Attribute.h"
#include <string>
#include <regex>

// X2 class for handling x2 attributes
class X2 : public Attribute
{
private:
    float value; // x2 value

public:
    X2();
    X2(string value);
    float getValue();
    Attribute* clone() override;
    Attribute* clone(string value) override;
    void mergeData(Attribute* attribute) override;
    ~X2();
};

#endif