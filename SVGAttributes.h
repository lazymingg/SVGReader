#ifndef _SVGATTRIBUTES_H_
#define _SVGATTRIBUTES_H_

#include <string>
#include <iostream>
#include <Windows.h>
#include <gdiplus.h>
#include "extendLib/rapid_xml/rapidxml.hpp"

using namespace rapidxml;
class SVGAttributes
{
private:
    std::string fill;            // Màu lấp đầy
    std::string stroke;          // Màu viền
    float strokeWidth;           // Độ dày của viền
    float opacity;               // Độ trong suốt
    float fillOpacity;           // Độ trong suốt của phần lấp đầy
    float strokeOpacity;         // Độ trong suốt của viền
    std::string strokeLinecap;   // Kiểu kết thúc viền
    std::string strokeLinejoin;  // Kiểu nối viền
    std::string strokeDasharray; // Mẫu nét đứt
    std::string transform;       // Biến đổi hình dạng
    Gdiplus::Color fillColor;    // Màu lấp đầy dạng Color
    Gdiplus::Color strokeColor;  // Màu viền dạng Color
    std::string text;            // Chữ của định dạng text

public:
    // Constructor
    SVGAttributes(xml_node<> *shapeNode);

    // Getters and setters
    void setFill(const std::string &color);
    std::string getFill() const;

    void setStroke(const std::string &color);
    std::string getStroke() const;

    void setStrokeWidth(float width);
    float getStrokeWidth() const;

    void setOpacity(float value);
    float getOpacity() const;

    void setFillOpacity(float value);
    float getFillOpacity() const;

    void setStrokeOpacity(float value);
    float getStrokeOpacity() const;

    void setStrokeLinecap(const std::string &cap);
    std::string getStrokeLinecap() const;

    void setStrokeLinejoin(const std::string &join);
    std::string getStrokeLinejoin() const;

    void setStrokeDasharray(const std::string &dash);
    std::string getStrokeDasharray() const;

    void setTransform(const std::string &trans);
    std::string getTransform() const;

    // Print attributes
    void printAttributes() const;

    void setFillColor(std::string str);
    Gdiplus::Color getFillColor() const;

    void setStrokeColor(std::string str);
    Gdiplus::Color getStrokeColor() const;

    void setText(std::string tex);
    std::string getText() const;
};

#endif // _SVGATTRIBUTES_H_
