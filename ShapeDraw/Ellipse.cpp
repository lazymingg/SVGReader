#include "../shapeheader/Ellipse.h"

MyFigure::Ellipse::Ellipse(xml_node<> *rootNode, Gdiplus::Graphics &graphics) : Figure(rootNode, graphics)
{
    if (!rootNode->first_attribute("cx"))
        center.setX(0);
    else
    {
        string tmpCx = rootNode->first_attribute("cx")->value();
        double unit = formatUnit(tmpCx);
        center.setX(stof(tmpCx) * unit);
    }

    if (!rootNode->first_attribute("cy"))
        center.setY(0);
    else
    {
        string tmpCy = rootNode->first_attribute("cy")->value();
        double unit = formatUnit(tmpCy);
        center.setY(stof(tmpCy) * unit);
    }

    if (rootNode->first_attribute("rx") && rootNode->first_attribute("ry"))
    {
        string tmpRx = rootNode->first_attribute("rx")->value();
        string tmpRy = rootNode->first_attribute("ry")->value();

        double unit1 = formatUnit(tmpRx);
        double unit2 = formatUnit(tmpRy);

        rx = stof(tmpRx) * unit1;
        ry = stof(tmpRy) * unit2;
        cout << "Ellipse rx: " << rx << ", ry: " << ry << endl;
    }
    else
    {
        std::cout << "Attributes 'rx' or 'ry' not found in ellipse node." << std::endl;
        rx = 0;
        ry = 0;
    }
}

void MyFigure::Ellipse::drawEllipse(Graphics &graphics)
{

    // Lấy giá trị `viewBox` scale từ `graphics`
    Gdiplus::Matrix currentMatrix;
    graphics.GetTransform(&currentMatrix);
    Color fillColor = static_cast<Fill*>(attributes.getAttributes("fill"))->getFill();
    int fillOpacity = static_cast<FillOpacity*>(attributes.getAttributes("fill-opacity"))->getFillOpacity() * fillColor.GetA();

    // if (fillColor.GetA() == 0 && fillColor.GetR() == 0 && fillColor.GetG() == 0 && fillColor.GetB() == 0)
    // {
    //     fillOpacity = 0;
    // }
    fillColor = Color(fillOpacity, fillColor.GetR(), fillColor.GetG(), fillColor.GetB());
    SolidBrush fillBrush(fillColor);

    Color strokeColor = static_cast<Stroke*>(attributes.getAttributes("stroke"))->getStroke();
    int strokeOpacity = static_cast<StrokeOpacity*>(attributes.getAttributes("stroke-opacity"))->getStrokeOpacity() * strokeColor.GetA();

    strokeColor = Color(strokeOpacity, strokeColor.GetR(), strokeColor.GetG(), strokeColor.GetB());
    Pen strokePen(strokeColor, static_cast<StrokeWidth*>(attributes.getAttributes("stroke-width"))->getStrokeWidth());
    
    std::cout << "rx = " << rx << ", ry = " << ry << std::endl;
    Gdiplus::Matrix a;
    static_cast<Transform*>(attributes.getAttributes("transform"))->transform(a);
    graphics.MultiplyTransform(&a);

    // Gdiplus::Matrix originalMatrix;
    // graphics.GetTransform(&originalMatrix);
    // graphics.SetTransform(&a);

    graphics.FillEllipse(&fillBrush, center.getX() - rx, center.getY() - ry, rx * 2, ry * 2);
    graphics.DrawEllipse(&strokePen, center.getX() - rx, center.getY() - ry, rx * 2, ry * 2);

    graphics.SetTransform(&currentMatrix);
}

void MyFigure::Ellipse::draw()
{
    std::cout << "Draw Ellipse: center = (" << center.getX() << ", " << center.getY() << "), ";
    std::cout << "rx = " << rx << ", ry = " << ry << "\n\n";
    drawEllipse(graphics);
}
