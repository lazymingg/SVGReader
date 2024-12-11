#include "../ShapeHeader/Text.h" // Adjust the path as needed

using namespace Gdiplus;
using namespace std;
using namespace rapidxml;

MyFigure::Text::Text(xml_node<> *rootNode, Gdiplus::Graphics &graphics) : Figure(rootNode, graphics)
{
    string getX = rootNode->first_attribute("x")->value();
    string getY = rootNode->first_attribute("y")->value();
    string getFont = rootNode->first_attribute("font-size")->value();
    // string getDx = rootNode->first_attribute("dx")->value();
    // string getDy = rootNode->first_attribute("dy")->value();
    
    this->point.setX(stof(getX));
    this->point.setY(stof(getY));
    this->font = stof(getFont);
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
    int fillOpacity = static_cast<int>(attributes.getFillOpacity() * 255);
    fillColor = Color(fillOpacity, fillColor.GetR(), fillColor.GetG(), fillColor.GetB());
    SolidBrush brush(fillColor);

    // Get stroke color and adjust opacity
    Color strokeColor = attributes.getStrokeColor();
    int strokeOpacity = static_cast<int>(attributes.getStrokeOpacity() * 255);
    strokeColor = Color(strokeOpacity, strokeColor.GetR(), strokeColor.GetG(), strokeColor.GetB());
    Pen pen(strokeColor, attributes.getStrokeWidth());

    // Get font size, family, and style
    float fontSize = attributes.getFontSize();
    cout << fontSize << " ";
    Gdiplus::FontFamily* fontFamily = attributes.getFontFamily();
    Gdiplus::FontStyle fontStyle = attributes.getFontStyle();

    // Set default values if attributes are not found
    bool defaultFontFamilyUsed = false;
    if (fontFamily == nullptr)
    {
        fontFamily = new Gdiplus::FontFamily(L"Times New Roman");
        defaultFontFamilyUsed = true;
    }
    
    // Create the font
    Font fontDraw(fontFamily, fontSize, fontStyle, UnitPixel);

    // Convert text content to wide string
    std::string text = attributes.getText();
    std::cout << text << '\n';
    std::wstring wideText(text.begin(), text.end());

    // Adjust the Y coordinate to move the text up
    PointF pointF(point.getX(), point.getY()); // Adjust the value as needed

    // Create a StringFormat object and set the vertical alignment to bottom
    StringFormat format;
    format.SetLineAlignment(StringAlignmentFar); // Align text to the bottom

    // Draw the text with the specified format
    Gdiplus::GraphicsPath textToPath;
    Gdiplus::Matrix a;
    attributes.getTransform().transform(a);

    Gdiplus::Matrix originalMatrix;
    graphics.GetTransform(&originalMatrix);
    graphics.SetTransform(&a);

    textToPath.StartFigure();
    textToPath.AddString(wideText.c_str(), wideText.length(), fontFamily, fontStyle, fontSize, pointF, &format);

    graphics.FillPath(&brush, &textToPath);
    graphics.DrawPath(&pen, &textToPath);
    graphics.SetTransform(&originalMatrix);

    // Clean up if default font family was used
    if (defaultFontFamilyUsed)
    {
        delete fontFamily;
    }
}

void MyFigure::Text::applyTransform()
{
}