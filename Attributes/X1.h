#ifndef X1_H
#define X1_H

#include "Attribute.h"
#include <string>
#include <regex>

// X1 class for handling x1 attributes
class X1 : public Attribute
{
private:
    float value; // x1 value

public:
    X1();
    X1(std::string value);
    float getValue();
    Attribute* clone() override;
    Attribute* clone(std::string value) override;
    void mergeData(Attribute* attribute) override;
    string toString() override;
    ~X1();
};

#endif