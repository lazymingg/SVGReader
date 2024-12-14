#ifndef Y_H
#define Y_H

#include "Attribute.h"
#include <string>
#include <vector>
#include <regex>

// Y class for handling y attributes
class Y : public Attribute
{
private:
    std::vector<float> yValues; // y values

public:
    Y();
    Y(const std::string value);
    std::vector<float> getYValues(size_t length) const;
    Attribute* clone() override;
    Attribute* clone(string value) override;
    void mergeData(Attribute* attribute) override;
    ~Y();
};

#endif