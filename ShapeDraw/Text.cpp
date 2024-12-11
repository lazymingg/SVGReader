#include "../ShapeHeader/Text.h" // Adjust the path as needed

using namespace Gdiplus;
using namespace std;
using namespace rapidxml;

MyFigure::Text::Text(xml_node<> *rootNode, Gdiplus::Graphics &graphics) : Figure(rootNode, graphics)
{
    string getX = rootNode->first_attribute("x")->value();
    string getY = rootNode->first_attribute("y")->value();
    
    this->point.setX(stof(getX));
    this->point.setY(stof(getY));
}

void MyFigure::Text::printInfomation()
{
    cout << "Text" << endl;
    point.print();

    attributes.printAttributes();
}

void MyFigure::Text::draw()
{
    // Get fill color and adjust opacity
    Color fillColor = attributes.getFillColor();
    int fillOpacity = static_cast<int>(attributes.getFillOpacity() * 255);
    fillColor = Color(fillOpacity, fillColor.GetR(), fillColor.GetG(), fillColor.GetB());
    SolidBrush brush(fillColor);

    // Debug: Print fill color and opacity
    cout << "Fill Color: R=" << fillColor.GetR() << " G=" << fillColor.GetG() << " B=" << fillColor.GetB() << " A=" << fillColor.GetA() << endl;

    // Get stroke color and adjust opacity
    Color strokeColor = attributes.getStrokeColor();
    int strokeOpacity = static_cast<int>(attributes.getStrokeOpacity() * 255);
    strokeColor = Color(strokeOpacity, strokeColor.GetR(), strokeColor.GetG(), strokeColor.GetB());
    Pen pen(strokeColor, attributes.getStrokeWidth());

    // Debug: Print stroke color and opacity
    cout << "Stroke Color: R=" << strokeColor.GetR() << " G=" << strokeColor.GetG() << " B=" << strokeColor.GetB() << " A=" << strokeColor.GetA() << endl;

    // Get font size, family, and style
    float fontSize = attributes.getFontSize();
    cout << "Font Size: " << fontSize << endl;

    Gdiplus::FontFamily *fontFamily = attributes.getFontFamily();
    Gdiplus::FontStyle fontStyle = attributes.getFontStyle();

    // Set default values if attributes are not found
    bool defaultFontFamilyUsed = false;
    if (fontFamily == nullptr) {
        fontFamily = new Gdiplus::FontFamily(L"Times New Roman");
        if (fontFamily->IsAvailable()) {
            defaultFontFamilyUsed = true;
        } else {
            cerr << "Error: Default font family 'Times New Roman' is not available." << endl;
            delete fontFamily;
            return;
        }
    }

    // Create the font
    Font fontDraw(fontFamily, fontSize, fontStyle, UnitPixel);

    // Convert text content to wide string
    std::string text = attributes.getText();
    std::wstring wideText(text.begin(), text.end());

    // Debug: Print text to render
    cout << "Text to render: " << text << endl;

    // Adjust the Y coordinate to move the text up
    PointF pointF(static_cast<float>(point.getX()), static_cast<float>(point.getY()));

    // Create a StringFormat object and set the vertical alignment to bottom
    StringFormat format;
    format.SetLineAlignment(StringAlignmentFar); // Align text to the bottom

    // Draw the text with the specified format
    GraphicsPath textToPath;
    Matrix transformMatrix;
    attributes.getTransform().transform(transformMatrix);

    Matrix originalMatrix;
    graphics.GetTransform(&originalMatrix);
    graphics.SetTransform(&transformMatrix);

    Status status = textToPath.AddString(wideText.c_str(), static_cast<INT>(wideText.length()), 
                                         fontFamily, fontStyle, fontSize, pointF, &format);

    if (status != Ok) {
        cerr << "Error: Failed to add text to GraphicsPath." << endl;
    }

    graphics.FillPath(&brush, &textToPath);
    graphics.DrawPath(&pen, &textToPath);

    // Restore the original transform
    graphics.SetTransform(&originalMatrix);

    // Clean up if default font family was used
    if (defaultFontFamilyUsed) {
        delete fontFamily;
    }
}

void MyFigure::Text::applyTransform()
{
}