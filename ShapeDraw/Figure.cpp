#include "../ShapeHeader/Figure.h"

bool isDigit(const char &c)
{
    return c >= '0' && c <= '9';
}

bool isCapitalizedAlpha(const char &c)
{
    return c >= 'A' && c <= 'Z';
}

bool isNotCapitalizedAlpha(const char &c)
{
    return c >= 'a' && c <= 'z';
}

bool isAlpha(const char &c)
{
    return isCapitalizedAlpha(c) || isNotCapitalizedAlpha(c);
}

float extractNumber(const std::string &data, int &i)
{
    std::string numb = "";
    int len = data.length();
    if (len == 0) return 0;

    while (i < len && (data[i] == ',' || data[i] == ' ' || data[i] == '\n'))
        ++i;

    if (i < len && data[i] == '-')
        numb += data[i++];
    while (i < len && (isDigit(data[i]) || data[i] == '.'))
        numb += data[i++];

    try {
        return !numb.empty() ? stof(numb) : 0;
    } catch (const std::invalid_argument &) {
        std::cerr << "Invalid number in path data: " << numb << std::endl;
        return 0;
    }
}

Figure::Figure(xml_node<>* shapeNode, Gdiplus::Graphics &graphics) : attributes(shapeNode), shapeNode(shapeNode), graphics(graphics) {}

SVGAttributes &Figure::getAttributes()
{
    return attributes;
}
