#include "PenRender.h"

PenRender::PenRender()
{
}

PenRender::~PenRender()
{
}

Gdiplus::SolidBrush *PenRender::getSolidBrush(SVGAttributes &attributes)
{
    Gdiplus::Color fillColor = static_cast<Fill *>(attributes.getAttributes("fill"))->getFill();
    int fillOpacity = static_cast<FillOpacity *>(attributes.getAttributes("fill-opacity"))->getFillOpacity() * fillColor.GetA();
    fillColor = Gdiplus::Color(fillOpacity, fillColor.GetR(), fillColor.GetG(), fillColor.GetB());
    return new Gdiplus::SolidBrush(fillColor);
}

Gdiplus::Pen *PenRender::getSolidPen(SVGAttributes &attributes)
{
    Gdiplus::Color strokeColor = static_cast<Stroke *>(attributes.getAttributes("stroke"))->getStroke();
    int strokeOpacity = static_cast<StrokeOpacity *>(attributes.getAttributes("stroke-opacity"))->getStrokeOpacity() * strokeColor.GetA();
    strokeColor = Gdiplus::Color(strokeOpacity, strokeColor.GetR(), strokeColor.GetG(), strokeColor.GetB());
    return new Gdiplus::Pen(strokeColor, static_cast<StrokeWidth *>(attributes.getAttributes("stroke-width"))->getStrokeWidth());
}

LinearGradientManager *PenRender::getPenLinear(std::string ID, SVGAttributes &attributes)
{
    if (ID == "")
    {
        return nullptr;
    }
    // Get the linearGradient by the ID
    DefsTag *linearGradientTag = Defs::getInstance()->findLinearGradient(ID);
    if (!linearGradientTag)
    {
        return nullptr;
    }

    LinearGradient *linearGradient = static_cast<LinearGradient *>(linearGradientTag);
    std::vector<Stop *> stops = linearGradient->getStops();
    if (stops.size() == 0)
    {
        return nullptr;
    }
    cout << linearGradient->toString() << endl;
    // get the attrbute of the linearGradient
    SVGAttributes attributesLinear = linearGradient->getAttributes();
    float x1 = static_cast<float>(static_cast<X1 *>(attributesLinear.getAttributes("x1"))->getValue());
    float y1 = static_cast<float>(static_cast<Y1 *>(attributesLinear.getAttributes("y1"))->getValue());
    float x2 = static_cast<float>(static_cast<X2 *>(attributesLinear.getAttributes("x2"))->getValue());
    float y2 = static_cast<float>(static_cast<Y2 *>(attributesLinear.getAttributes("y2"))->getValue());

    Gdiplus::PointF startPoint(x1, y1); // Gdiplus::PointF startPoint
    Gdiplus::PointF endPoint(x2, y2);

    // Create the LinearGradientBrush
    Gdiplus::LinearGradientBrush *brush = new Gdiplus::LinearGradientBrush(startPoint, endPoint, Gdiplus::Color::Black, Gdiplus::Color::White);

    // Prepare color and offset arrays
    std::vector<Gdiplus::Color> colors;
    std::vector<Gdiplus::REAL> offsets;

    for (size_t i = 0; i < stops.size(); ++i)
    {
        // Get the offset
        float offset = static_cast<OffSet *>(stops[i]->getAttributes().getAttributes("offset"))->getOffSet();
        offsets.push_back(static_cast<Gdiplus::REAL>(offset));

        // Get the stop-color
        Gdiplus::Color color = static_cast<StopColor *>(stops[i]->getAttributes().getAttributes("stop-color"))->getStopColor();
        colors.push_back(color);
    }
    // print all data from stop
    for (size_t i = 0; i < colors.size(); ++i)
    {
        cout << "Color: " << int(colors[i].GetR()) << ", " << int(colors[i].GetG()) << ", " << int(colors[i].GetB()) << ", " << int(colors[i].GetA()) << " - Offset: " << offsets[i] << endl;
    }

    // Get the stroke width
    float strokeWidth = static_cast<StrokeWidth *>(attributes.getAttributes("stroke-width"))->getStrokeWidth();
    std::string gradientUnits = static_cast<GradientUnits *>(attributesLinear.getAttributes("gradientUnits"))->getUnits();
    std::string spreadMethod = static_cast<SpreadMethod *>(attributesLinear.getAttributes("spreadMethod"))->getMethod();

    // Create the LinearGradientManager
    return new LinearGradientManager(startPoint, endPoint, colors, offsets, strokeWidth, gradientUnits, spreadMethod);
}
