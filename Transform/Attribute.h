#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include <string>
#include <Windows.h>
#include <gdiplus.h>
#include <vector>
#include <memory>
#include <regex>
#include <iostream>

using namespace std;

//hexToColor function
Gdiplus::Color hexToColor(const std::string &hex);
Gdiplus::Color getColor(const std::string &value);

class Attribute
{
public:
    virtual Attribute* clone() = 0;
    virtual Attribute* clone(string value) = 0;
    virtual ~Attribute() = default;
    virtual void mergeData(Attribute* attribute) = 0;
};


#endif // ATTRIBUTE_H
