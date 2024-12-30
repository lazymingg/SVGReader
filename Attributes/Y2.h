#ifndef Y2_H
#define Y2_H

#include "Attribute.h"
#include <string>
#include <regex>

// Y2 class for handling y2 attributes
class Y2 : public Attribute
{
private:
    float value; // y2 value

public:
    Y2();
    Y2(std::string value);
    float getValue();
    Attribute* clone() override;
    Attribute* clone(std::string value) override;
    void mergeData(Attribute* attribute) override;
    string toString() override;
    ~Y2();
};

#endif