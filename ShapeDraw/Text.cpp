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
    // Lấy giá trị `viewBox` scale từ `graphics`
    Gdiplus::Matrix currentMatrix;
    graphics.GetTransform(&currentMatrix);
    // Get fill color and adjust opacity
    Color fillColor = static_cast<Fill *>(attributes.getAttributes("fill"))->getFill();
    int fillOpacity = static_cast<int>(static_cast<FillOpacity *>(attributes.getAttributes("fill-opacity"))->getFillOpacity() * fillColor.GetA());
    fillColor = Color(fillOpacity, fillColor.GetR(), fillColor.GetG(), fillColor.GetB());
    SolidBrush *brush = new SolidBrush(fillColor);

    // Get stroke color and adjust opacity
    Color strokeColor = static_cast<Stroke *>(attributes.getAttributes("stroke"))->getStroke();
    int strokeOpacity = static_cast<int>(static_cast<StrokeOpacity *>(attributes.getAttributes("stroke-opacity"))->getStrokeOpacity() * strokeColor.GetA());
    strokeColor = Color(strokeOpacity, strokeColor.GetR(), strokeColor.GetG(), strokeColor.GetB());

    Pen *pen = new Pen(strokeColor, static_cast<StrokeWidth *>(attributes.getAttributes("stroke-width"))->getStrokeWidth());

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

    // Get dx and dy values
    std::vector<float> dxValues = static_cast<Dx *>(attributes.getAttributes("dx"))->getDxValues(text.length());

    std::vector<float> dyValues = static_cast<Dy *>(attributes.getAttributes("dy"))->getDyValues(text.length());
   
    // Ensure dx and dy vectors are correctly sized
    if (dxValues.size() == 1)
    {
        dxValues.resize(text.length(), dxValues[0]);
    }
    if (dyValues.size() == 1)
    {
        dyValues.resize(text.length(), dyValues[0]);
    }

    // Initial position
    float x = static_cast<float>(point.getX());
    float y = static_cast<float>(point.getY());

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

    // Draw each glyph individually
    GraphicsPath textToPath;
    Matrix transformMatrix;
    static_cast<Transform *>(attributes.getAttributes("transform"))->transform(transformMatrix);
    graphics.MultiplyTransform(&transformMatrix);

    // Matrix originalMatrix;
    // graphics.GetTransform(&originalMatrix);
    // graphics.SetTransform(&transformMatrix);
    
    for (size_t i = 0; i < text.length(); ++i)
    {
        // Update x and y positions based on dx and dy values
        if (i > 0)
        {
            x += dxValues[i];
            y += dyValues[i];
        }

        std::cout << "dx[" << i << "]: " << dxValues[i] << ", dy[" << i << "]: " << dyValues[i] << std::endl;

        PointF pointF(x, y);
        std::wstring glyph(1, text[i]);

        textToPath.Reset();
        textToPath.AddString(glyph.c_str(), static_cast<INT>(glyph.length()),
                             fontFamily, fontStyle, fontSize, pointF, &format);
        graphics.FillPath(brush, &textToPath);
        graphics.DrawPath(pen, &textToPath);

    }

    // Restore the original transform
    graphics.SetTransform(&currentMatrix);

    // Clean up if default font family was used
    if (defaultFontFamilyUsed)
    {
        delete fontFamily;
    }
    delete brush;
    delete pen;
}