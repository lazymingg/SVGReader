#ifndef Y1_H
#define Y1_H

#include "Attribute.h"
#include <string>
#include <regex>

// Y1 class for handling y1 attributes
class Y1 : public Attribute
{
private:
    float value; // y1 value

public:
    Y1();
    Y1(std::string value);
    float getValue();
    Attribute* clone() override;
    Attribute* clone(std::string value) override;
    void mergeData(Attribute* attribute) override;
    string toString() override;
    ~Y1();
};

#endif