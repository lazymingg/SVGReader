#include "../shapeheader/Ellipse.h"

MyFigure::Ellipse::Ellipse(xml_node<> *rootNode, Gdiplus::Graphics &graphics) : Figure(rootNode, graphics)
{
    if (!rootNode->first_attribute("cx"))
        center.setX(0);
    else
        center.setX(stof(rootNode->first_attribute("cx")->value()));

    if (!rootNode->first_attribute("cy"))
        center.setY(0);
    else
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
    LinearGradientManager *temp = penRender.getPenLinear(static_cast<Fill *>(attributes.getAttributes("fill"))->getId(), attributes);
    Gdiplus::Pen *penLinear = nullptr;
    if (temp != nullptr)
    {
        penLinear = temp->getPen();
    }
    
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
    {
        temp->printColor();
        Gdiplus::LinearGradientBrush *brush = temp->getBrush();
        Gdiplus::RectF rect(center.getX() - rx, center.getY() - ry, rx * 2, ry * 2);
        graphics.FillEllipse(brush, rect);
    }

    graphics.SetTransform(&currentMatrix);

    delete fillBrush;
    delete strokePen;
    if (penLinear != nullptr)
        delete penLinear;
    if (temp != nullptr)
        delete temp;
}

void MyFigure::Ellipse::draw()
{
    std::cout << "Draw Ellipse: center = (" << center.getX() << ", " << center.getY() << "), ";
    std::cout << "rx = " << rx << ", ry = " << ry << "\n\n";
    drawEllipse(graphics);
}
