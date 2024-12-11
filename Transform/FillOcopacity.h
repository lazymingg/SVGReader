#ifndef FILLOPACITY_H
#define FILLOPACITY_H

#include "Attribute.h"
#include <string>

// FillOpacity class for handling fill-opacity attributes
class FillOpacity : public Attribute
{
private:
    float value;

public:
    FillOpacity();
    FillOpacity(const std::string &getValue);
    float getFillOpacity();
    Attribute* clone() override;
    ~FillOpacity();
};

#endif // FILLOPACITY_H
