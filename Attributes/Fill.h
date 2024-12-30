#ifndef FILL_H
#define FILL_H

#include "Attribute.h"
#include <string>
#include <regex>
#include <Gdiplus.h>

// Fill class for handling fill color attributes
class Fill : public Attribute
{
private:
    Gdiplus::Color color;
    
public:
    Fill();
    Fill(std::string value);
    Gdiplus::Color getFill();
    Attribute* clone() override;
    Attribute* clone(string value) override;
    void mergeData(Attribute* attribute) override;
    string toString() override;
    ~Fill();
};

#endif
