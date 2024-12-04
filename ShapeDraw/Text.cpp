#include "../ShapeHeader/Text.h" // Adjust the path as needed

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
    // Get fill color and adjust opacity
    Color fillColor = attributes.getFillColor();
    int opacity = static_cast<int>(attributes.getFillOpacity() * 255);
    fillColor = Color(opacity, fillColor.GetR(), fillColor.GetG(), fillColor.GetB());
    SolidBrush brush(fillColor);

    // Set font
    FontFamily fontFamily(L"Times New Roman");
    Font fontDraw(&fontFamily, this->font, FontStyleRegular, UnitPixel);

    // Convert text content to wide string
    string text = attributes.getText();
    std::wstring wideText(text.begin(), text.end());

    // Adjust the Y coordinate to move the text up
    PointF pointF(point.getX(), point.getY()); // Adjust the value as needed

    // Create a StringFormat object and set the vertical alignment to bottom
    StringFormat format;
    format.SetLineAlignment(StringAlignmentFar); // Align text to the bottom

    Color strokeColor = attributes.getStrokeColor();
    // Adjust opacity
    opacity = static_cast<int>(attributes.getStrokeOpacity() * 255);
    strokeColor = Color(opacity, strokeColor.GetR(), strokeColor.GetG(), strokeColor.GetB());
    Pen pen(strokeColor, attributes.getStrokeWidth());

    // Draw the text with the specified format
    Gdiplus::GraphicsPath textToPath;
    textToPath.StartFigure();
    textToPath.AddString(wideText.c_str(), wideText.length(), &fontFamily, 0, font, pointF, &format);

    graphics.FillPath(&brush, &textToPath);
    graphics.DrawPath(&pen, &textToPath);
}

void MyFigure::Text::applyTransform()
{
    MyMatrix::Matrix textMatrix({{(double) point.getX()}, {(double) point.getY()}, {1}});

    this->attributes.getTransform().transform(textMatrix);

    // Get new data
    point.setX(textMatrix.getElement(0, 0));
    point.setY(textMatrix.getElement(0, 1));
}