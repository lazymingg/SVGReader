#ifndef DX_H
#define DX_H

#include "Attribute.h"
#include <string>
#include <vector>
#include <regex>

// Dx class for handling dx attributes
class Dx : public Attribute
{
private:
    std::vector<float> dxValues; // Vector of dx values

public:
    Dx();
    Dx(string &value);
    std::vector<float> getDxValues(size_t glyphCount) const;
    Attribute* clone() override;
    Attribute* clone(string value) override;
    void mergeData(Attribute* attribute) override;
    string toString() override;
    ~Dx();
};

#endif
