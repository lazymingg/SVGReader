#include "../ShapeHeader/Text.h"
using namespace Gdiplus;
using namespace std;
using namespace rapidxml;

MyFigure::Text::Text(xml_node<> *rootNode, Gdiplus::Graphics &graphics) : Figure(rootNode, graphics)
{

    string getX = rootNode->first_attribute("x")->value();
    string getY = rootNode->first_attribute("y")->value();
    string getFont = rootNode->first_attribute("font-size")->value();
    this->point.setX(stoi(getX));
    this->point.setY(stoi(getY));
    this->font = stoi(getFont);
}

void MyFigure::Text::printInfomation()
{
    cout << "Text" << endl;
    point.print();
    cout << font << '\n';
    attributes.printAttributes();
}

void MyFigure::Text::draw()
{
    // Draw the text

    // Get fill color and adjust opacity
    Color fillColor = attributes.getFillColor();
    int opacity = attributes.getFillOpacity() * 255;
    fillColor = Color(opacity, fillColor.GetR(), fillColor.GetG(), fillColor.GetB());
    SolidBrush brush(fillColor);

    // Set font
    FontFamily fontFamily(L"Times New Roman");
    Font fontDraw(&fontFamily, this->font, FontStyleRegular, UnitPixel);

    // Convert text content to wide string
    string text = attributes.getText();
    std::wstring wideText(text.begin(), text.end());
    
    // Adjust the Y coordinate to move the text up
    PointF pointF(point.getX(), point.getY() * 14 / 15); // Adjust the value as needed
    graphics.DrawString(wideText.c_str(), -1, &fontDraw, pointF, &brush);
}