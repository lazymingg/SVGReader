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

    Brush *fillBrush = penRender.getSolidBrush(attributes);
    Pen *strokePen = penRender.getSolidPen(attributes);
    Pen *penLinear = penRender.getPenLinear(static_cast<Fill *>(attributes.getAttributes("fill"))->getId(), attributes);

    std::cout << "rx = " << rx << ", ry = " << ry << std::endl;
    Gdiplus::Matrix a;
    static_cast<Transform *>(attributes.getAttributes("transform"))->transform(a);
    graphics.MultiplyTransform(&a);

    // Gdiplus::Matrix originalMatrix;
    // graphics.GetTransform(&originalMatrix);
    // graphics.SetTransform(&a);

    graphics.FillEllipse(fillBrush, center.getX() - rx, center.getY() - ry, rx * 2, ry * 2);
    graphics.DrawEllipse(strokePen, center.getX() - rx, center.getY() - ry, rx * 2, ry * 2);

    if (penLinear != nullptr)
        graphics.DrawEllipse(penLinear, center.getX() - rx, center.getY() - ry, rx * 2, ry * 2);

    graphics.SetTransform(&currentMatrix);

    delete fillBrush;
    delete strokePen;
    if (penLinear != nullptr)
        delete penLinear;
}

void MyFigure::Ellipse::draw()
{
    std::cout << "Draw Ellipse: center = (" << center.getX() << ", " << center.getY() << "), ";
    std::cout << "rx = " << rx << ", ry = " << ry << "\n\n";
    drawEllipse(graphics);
}
