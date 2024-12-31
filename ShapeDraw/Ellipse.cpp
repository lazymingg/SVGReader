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

    graphics.FillEllipse(fillBrush, center.getX() - rx, center.getY() - ry, rx * 2, ry * 2);
    graphics.DrawEllipse(strokePen, center.getX() - rx, center.getY() - ry, rx * 2, ry * 2);

    if (penLinear != nullptr)
    {
        temp->printColor();
        
        Gdiplus::RectF rect(center.getX() - rx, center.getY() - ry, rx * 2, ry * 2);
        // Transform coordinates if gradientUnits is objectBoundingBox
        if (!temp->getIsUserSpaceOnUse())
            temp->transformCoordinates(rect);

        Gdiplus::LinearGradientBrush *brush = temp->getBrush();
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
