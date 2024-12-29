#ifndef OCPROPERTY_H
#define OCPROPERTY_H

#include "Attribute.h"
#include <string>

// Ocopacity class for handling opacity attributes
class Ocopacity : public Attribute
{
private:
    float value;

public:
    Ocopacity();
    Ocopacity(std::string value);
    float getOcopacity();
    Attribute* clone() override;
    Attribute* clone(string value) override;
    void mergeData(Attribute* attribute) override;
    ~Ocopacity();
};

#endif // OCPROPERTY_H
