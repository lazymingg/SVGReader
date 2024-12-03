#include "../ShapeHeader/Circle.h"


MyFigure::Circle::Circle(xml_node<> *rootNode, Gdiplus::Graphics &graphics) : Ellipse(rootNode, graphics)
{

    if (rootNode->first_attribute("r") == nullptr)
    {
        std::cout << "Attribute 'r' not found in circle node." << std::endl;
        return;
    }
    // Thiết lập bán kính cho Circle
    r = stoi(rootNode->first_attribute("r")->value());
    cout << "Circle radius: " << r << endl;
    rx = r; // Đặt rx và ry bằng r
    ry = r;
}

void MyFigure::Circle::draw()
{
    applyTransform();
    // Ghi đè phương thức draw để sử dụng thông tin hình tròn
    cout << "Draw Circle: center = (" << center.getX() << ", " << center.getY() << "), ";
    cout << "r = " << rx << "\n\n";
    cout << "sth" << endl;

    // Gọi hàm vẽ ellipse từ lớp cha
    drawEllipse(graphics); // Gọi phương thức drawEllipse từ Ellipse
}
void MyFigure::Circle::applyTransform()
{
    MyMatrix::Matrix circleMatrix({{rx, 0, center.getX()}, {0, ry, center.getY()}, {0, 0, 1}});
    
    circleMatrix = this->attributes.getTransform().doTransform(circleMatrix);

    //Get new data
    rx = circleMatrix.getElement(0, 0);
    ry = circleMatrix.getElement(1, 1);
    center.setX(circleMatrix.getElement(0, 2));
    center.setY(circleMatrix.getElement(1, 2));
}