#ifndef DY_H
#define DY_H

#include "Attribute.h"
#include <string>
#include <vector>
#include <regex>

// Dy class for handling dy attributes
class Dy : public Attribute
{
private:
    std::vector<float> dyValues; // Vector of dy values

public:
    Dy();
    Dy(std::string &value);
    std::vector<float> getDyValues(size_t glyphCount) const;
    Attribute* clone() override;
    Attribute* clone(std::string value) override;
    void mergeData(Attribute* attribute) override;
    ~Dy();
};

#endif