#include "../shapeheader/Ellipse.h"


MyFigure::Ellipse::Ellipse(xml_node<>* rootNode, Gdiplus::Graphics& graphics) : Figure(rootNode, graphics)
{

    center.setX(stoi(rootNode->first_attribute("cx")->value()));
    center.setY(stoi(rootNode->first_attribute("cy")->value()));

    if (rootNode->first_attribute("rx") && rootNode->first_attribute("ry")) 
    {
        rx = stoi(rootNode->first_attribute("rx")->value());
        ry = stoi(rootNode->first_attribute("ry")->value());
        cout << "Ellipse rx: " << rx << ", ry: " << ry << endl;
    }
    else 
    {
        std::cerr << "Attributes 'rx' or 'ry' not found in ellipse node." << std::endl;
        rx = 0;
        ry = 0;
    }
}

void MyFigure::Ellipse::drawEllipse(Graphics& graphics) 
{
    SolidBrush fillBrush(attributes.getFillColor());
    Pen strokePen(attributes.getStrokeColor(), attributes.getStrokeWidth());
    std::cout << "rx = " << rx << ", ry = " << ry << std::endl;
    graphics.FillEllipse(&fillBrush, center.getX() - rx, center.getY() - ry, rx * 2, ry * 2);
    graphics.DrawEllipse(&strokePen, center.getX() - rx, center.getY() - ry, rx * 2, ry * 2);
}

void MyFigure::Ellipse::draw() 
{
    applyTransform();
    std::cout << "Draw Ellipse: center = (" << center.getX() << ", " << center.getY() << "), ";
    std::cout << "rx = " << rx << ", ry = " << ry << "\n\n";
    drawEllipse(graphics);
}
void MyFigure::Ellipse::applyTransform()
{
    MyMatrix::Matrix ellipseMatrix({{rx, 0, center.getX()}, {0, ry, center.getY()}, {0, 0, 1}});
    
    this->attributes.getTransform().transform(ellipseMatrix);

    //Get new data
    rx = ellipseMatrix.getElement(0, 0);
    ry = ellipseMatrix.getElement(1, 1);
    center.setX(ellipseMatrix.getElement(0, 2));
    center.setY(ellipseMatrix.getElement(1, 2));
}