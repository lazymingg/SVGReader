#include "../ShapeHeader/Text.h" // Adjust the path as needed

using namespace Gdiplus;
using namespace std;
using namespace rapidxml;

MyFigure::Text::Text(xml_node<> *rootNode, Gdiplus::Graphics &graphics) : Figure(rootNode, graphics)
{
    string getX = rootNode->first_attribute("x")->value();
    string getY = rootNode->first_attribute("y")->value();
    text = rootNode->value();
    this->point.setX(stof(getX));
    this->point.setY(stof(getY));
}

void MyFigure::Text::printInfomation()
{
    // cout << "Text" << endl;
    // point.print();

    // attributes.printAttributes();
}
void MyFigure::Text::draw()
{
    // Get fill color and adjust opacity
    Color fillColor = static_cast<Fill *>(attributes.getAttributes("fill"))->getFill();
    int fillOpacity = static_cast<int>(static_cast<FillOpacity *>(attributes.getAttributes("fill-opacity"))->getFillOpacity() * 255);
    fillColor = Color(fillOpacity, fillColor.GetR(), fillColor.GetG(), fillColor.GetB());
    SolidBrush brush(fillColor);

    // Get stroke color and adjust opacity
    Color strokeColor = static_cast<Stroke *>(attributes.getAttributes("stroke"))->getStroke();
    int strokeOpacity = static_cast<int>(static_cast<StrokeOpacity *>(attributes.getAttributes("stroke-opacity"))->getStrokeOpacity() * 255);
    if (fillColor.GetR() == 255 && fillColor.GetG() == 255 && fillColor.GetB() == 255)
    {
        strokeOpacity = 0;
    }
    strokeColor = Color(strokeOpacity, strokeColor.GetR(), strokeColor.GetG(), strokeColor.GetB());
    Pen pen(strokeColor, static_cast<StrokeWidth *>(attributes.getAttributes("stroke-width"))->getStrokeWidth());

    // Get font size, family, and style
    float fontSize = static_cast<FontSize *>(attributes.getAttributes("font-size"))->getFontSize();
    Gdiplus::FontFamily *fontFamily = static_cast<MyFontFamily *>(attributes.getAttributes("font-family"))->getFontFamily();
    Gdiplus::FontStyle fontStyle = static_cast<MyFontStyle *>(attributes.getAttributes("font-style"))->getFontStyle();

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
    std::wstring wideText(text.begin(), text.end());

    // Adjust the Y coordinate to move the text up
    PointF pointF(static_cast<float>(point.getX()), static_cast<float>(point.getY()));

    // Create a StringFormat object
    StringFormat format;

    // Handle text-anchor attribute
    std::string textAnchor = static_cast<TextAnchor *>(attributes.getAttributes("text-anchor"))->getTextAnchor();
    if (textAnchor == "middle")
    {
        format.SetAlignment(StringAlignmentCenter); // Center alignment
    }
    else if (textAnchor == "end")
    {
        format.SetAlignment(StringAlignmentFar); // Right alignment
    }
    else
    {
        format.SetAlignment(StringAlignmentNear); // Default: Left alignment
    }

    // Set the vertical alignment to bottom
    format.SetLineAlignment(StringAlignmentFar);

    // Draw the text with the specified format
    GraphicsPath textToPath;
    Matrix transformMatrix;
    static_cast<Transform *>(attributes.getAttributes("transform"))->transform(transformMatrix);

    Matrix originalMatrix;
    graphics.GetTransform(&originalMatrix);
    graphics.SetTransform(&transformMatrix);

    textToPath.AddString(wideText.c_str(), static_cast<INT>(wideText.length()),
                         fontFamily, fontStyle, fontSize, pointF, &format);

    graphics.FillPath(&brush, &textToPath);
    graphics.DrawPath(&pen, &textToPath);

    // Restore the original transform
    graphics.SetTransform(&originalMatrix);

    // Clean up if default font family was used
    if (defaultFontFamilyUsed)
    {
        delete fontFamily;
    }
}