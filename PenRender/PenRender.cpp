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

Gdiplus::Pen *PenRender::getPenLinear(std::string ID, SVGAttributes &attributes)
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

    // Parse the coordinates with default value by yourself, no getting from attributes
    // Get x1, x2, y1, y2 like this:  std::vector<float> dxValues = static_cast<Dx *>(attributes.getAttributes("dx"))->getDxValues(text.length());
    float x1 = static_cast<float>(static_cast<X1 *>(attributes.getAttributes("x1"))->getValue());
    float x2 = static_cast<float>(static_cast<X2 *>(attributes.getAttributes("x2"))->getValue());
    float y1 = static_cast<float>(static_cast<Y1 *>(attributes.getAttributes("y1"))->getValue());
    float y2 = static_cast<float>(static_cast<Y2 *>(attributes.getAttributes("y2"))->getValue());

    Gdiplus::PointF startPoint(x1, y1); // Gdiplus::PointF startPoint
    Gdiplus::PointF endPoint(x2, y2);

    // Create a LinearGradientBrush
    Gdiplus::LinearGradientBrush *brush = new Gdiplus::LinearGradientBrush(startPoint, endPoint, Gdiplus::Color::Black, Gdiplus::Color::White);

    // Set the gradient stops directly
    for (size_t i = 0; i < stops.size(); ++i)
    {
        float offset = static_cast<OffSet *>(stops[i]->getAttributes().getAttributes("offset"))->getOffSet();
        Gdiplus::Color color = static_cast<StopColor *>(stops[i]->getAttributes().getAttributes("stop-color"))->getStopColor();
        brush->SetInterpolationColors(&color, &offset, 1);
    }

    // Create a Pen using the LinearGradientBrush
    Gdiplus::Pen *pen = new Gdiplus::Pen(brush, static_cast<StrokeWidth *>(attributes.getAttributes("stroke-width"))->getStrokeWidth());

    return pen;
}
