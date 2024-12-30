#ifndef X_H
#define X_H

#include "Attribute.h"
#include <string>
#include <vector>
#include <regex>

// X class for handling x attributes
class X : public Attribute
{
private:
    std::vector<float> xValues; // x values

public:
    X();
    X(string value);
    std::vector<float> getXValues(size_t length) const;
    Attribute* clone() override;
    Attribute* clone(string value) override;
    void mergeData(Attribute* attribute) override;
    string toString() override;
    ~X();
};

#endif