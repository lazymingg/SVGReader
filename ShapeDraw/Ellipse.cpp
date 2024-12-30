#include "../shapeheader/Ellipse.h"

MyFigure::Ellipse::Ellipse(xml_node<> *rootNode, Gdiplus::Graphics &graphics) : Figure(rootNode, graphics)
{
    center.setX(stof(rootNode->first_attribute("cx")->value()));
    center.setY(stof(rootNode->first_attribute("cy")->value()));

    if (rootNode->first_attribute("rx") && rootNode->first_attribute("ry"))
    {
        rx = stof(rootNode->first_attribute("rx")->value());
        ry = stof(rootNode->first_attribute("ry")->value());
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
