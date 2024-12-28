#ifndef _OFF_SET_H_
#define _OFF_SET_H_

#include "Attribute.h"
#include <string>

class OffSet : public Attribute
{
private:
    float offSet;
public:
    OffSet();
    OffSet(std::string value);
    float getX();
    float getY();
    Attribute* clone() override;
    Attribute* clone(std::string value) override;
    void mergeData(Attribute* attribute) override;
    ~OffSet();
};
#endif