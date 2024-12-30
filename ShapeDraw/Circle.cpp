#include "../ShapeHeader/Circle.h"

MyFigure::Circle::Circle(xml_node<> *rootNode, Gdiplus::Graphics &graphics) : Ellipse(rootNode, graphics)
{

    if (rootNode->first_attribute("r") == nullptr)
    {
        std::cout << "Attribute 'r' not found in circle node." << std::endl;
        return;
    }
    // Thiết lập bán kính cho Circle
    rx = stod(rootNode->first_attribute("r")->value());
    cout << "Circle radius: " << rx << endl;
    ry = rx;
}

void MyFigure::Circle::draw()
{
    // Ghi đè phương thức draw để sử dụng thông tin hình tròn
    cout << "Draw Circle: center = (" << center.getX() << ", " << center.getY() << "), ";
    cout << "r = " << rx << "\n\n";
    cout << "sth" << endl;

    // Gọi hàm vẽ ellipse từ lớp cha
    drawEllipse(graphics); // Gọi phương thức drawEllipse từ Ellipse
}
