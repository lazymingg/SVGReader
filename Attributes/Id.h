#ifndef _ID_H_
#define _ID_H_
#include "Attribute.h"

class Id : public Attribute
{
private:
    std::string id;
public:
    Id();
    Id(std::string value);
    std::string getId();
    Attribute* clone(std::string value) override;
    Attribute* clone() override;
    void mergeData(Attribute* attribute) override;
    string toString() override;
    ~Id();
};

#endif