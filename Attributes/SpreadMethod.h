#ifndef _SPREAD_METHOD_H_
#define _SPREAD_METHOD_H_

#include "Attribute.h"
#include <string>

class SpreadMethod : public Attribute
{
private:
    std::string method;

public:
    SpreadMethod();
    SpreadMethod(std::string value);
    std::string getMethod();
    Attribute* clone() override;
    Attribute* clone(std::string value) override;
    void mergeData(Attribute* attribute) override;
    std::string toString() override;
    ~SpreadMethod();
};

#endif