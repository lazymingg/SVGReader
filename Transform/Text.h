#ifndef TEXT_H
#define TEXT_H

#include "Attribute.h"
#include <string>

// Text class for handling text attributes
class Text : public Attribute
{
private:
    std::string text;

public:
    Text();
    Text(std::string text);
    std::string getText();
    Attribute* clone() override;
    ~Text();
};

#endif // TEXT_H
