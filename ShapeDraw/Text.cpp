#include "../ShapeHeader/Text.h" // Adjust the path as needed

using namespace Gdiplus;
using namespace std;
using namespace rapidxml;

MyFigure::Text::Text(xml_node<> *rootNode, Gdiplus::Graphics &graphics) : Figure(rootNode, graphics)
{
    text = rootNode->value();
    vector<float> xValues = static_cast<vector<float>>(static_cast<X *>(attributes.getAttributes("x"))->getXValues(1));
    vector<float> yValues = static_cast<vector<float>>(static_cast<Y *>(attributes.getAttributes("y"))->getYValues(1));

    this->point.setX(xValues[0]);
    this->point.setY(yValues[0]);

    vector<float> dxValues = static_cast<vector<float>>(static_cast<Dx *>(attributes.getAttributes("dx"))->getDxValues(1));
    vector<float> dyValues = static_cast<vector<float>>(static_cast<Dy *>(attributes.getAttributes("dy"))->getDyValues(1));

    dx = dxValues[0];
    dy = dyValues[0];
}

void MyFigure::Text::printInfomation()
{
    // cout << "Text" << endl;
    // point.print();

    // attributes.printAttributes();
}

void MyFigure::Text::draw()
{
    // Lấy giá trị `viewBox` scale từ `graphics`
    Gdiplus::Matrix currentMatrix;
    graphics.GetTransform(&currentMatrix);
    // Get fill color and adjust opacity
    SolidBrush *brush = penRender.getSolidBrush(attributes);
    Pen *pen = penRender.getSolidPen(attributes);
    Pen *penLinear = penRender.getPenLinear(static_cast<Fill *>(attributes.getAttributes("fill"))->getId(), attributes);
    // Get font size, family, and style
    float fontSize = static_cast<FontSize *>(attributes.getAttributes("font-size"))->getFontSize();
    Gdiplus::FontFamily *fontFamily = static_cast<MyFontFamily *>(attributes.getAttributes("font-family"))->getFontFamily();
    Gdiplus::FontStyle fontStyle = static_cast<MyFontStyle *>(attributes.getAttributes("font-style"))->getFontStyle();
    // Get font weight
    // std::string fontWeightStr = static_cast<string>(static_cast<FontWeight *>(attributes.getAttributes("font-weight"))->getFontWeight());
    // if (fontWeightStr == "bold" || fontWeightStr == "bolder" || fontWeightStr == "700" || fontWeightStr == "800" || fontWeightStr == "900")
    // {
    //     fontStyle = static_cast<Gdiplus::FontStyle>(fontStyle | Gdiplus::FontStyleBold);
    // }

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

    // Adjust the position based on dx and dy
    pointF.X += dx;
    pointF.Y += dy;

    // Draw the text with the specified format
    GraphicsPath textToPath;
    Matrix transformMatrix;
    static_cast<Transform *>(attributes.getAttributes("transform"))->transform(transformMatrix);
    graphics.MultiplyTransform(&transformMatrix);

    // Matrix originalMatrix;
    // graphics.GetTransform(&originalMatrix);
    // graphics.SetTransform(&transformMatrix);

    textToPath.AddString(wideText.c_str(), static_cast<INT>(wideText.length()),
                         fontFamily, fontStyle, fontSize, pointF, &format);

    graphics.FillPath(brush, &textToPath);
    graphics.DrawPath(pen, &textToPath);
    // Use penLinear
    if (penLinear != nullptr)
        graphics.DrawPath(penLinear, &textToPath);

    // Restore the original transform
    graphics.SetTransform(&currentMatrix);

    // Clean up if default font family was used
    if (defaultFontFamilyUsed)
    {
        delete fontFamily;
    }
    delete brush;
    delete pen;
    if (penLinear != nullptr)
        delete penLinear;
}