#include "../ShapeHeader/Polyline.h"

using namespace Gdiplus;
using namespace std;
using namespace rapidxml;

MyFigure::Polyline::Polyline(xml_node<> *rootNode, Gdiplus::Graphics &graphics) : Figure(rootNode, graphics)
{

    // Đặt các điểm từ thuộc tính "points"
    string points = rootNode->first_attribute("points")->value();
    float x, y;
    int len = points.length(), i = 0;

    for (i; i < len; ++i)
    {
        x = extractNumber(points, i);
        y = extractNumber(points, i);
        this->points.push_back(MyPoint::Point(x, y));
    }
    
    // stringstream ss(points);
    // string point;
    // while (getline(ss, point, ' '))
    // {
    //     stringstream ssPoint(point);
    //     string x, y;
    //     getline(ssPoint, x, ',');
    //     getline(ssPoint, y, ',');
    //     this->points.push_back(MyPoint::Point(stof(x), stof(y)));
    // }
}

void MyFigure::Polyline::printInfomation()
{
//     cout << "Polyline:" << endl;
//     for (int i = 0; i < points.size(); i++)
//         points[i].print();
//     attributes.printAttributes();
}

void MyFigure::Polyline::draw()
{
    // Lấy giá trị `viewBox` scale từ `graphics`
    Gdiplus::Matrix currentMatrix;
    graphics.GetTransform(&currentMatrix);
    // draw polygon here
    // draw fill polygon first

    SolidBrush *brush = penRender.getSolidBrush(attributes);

    // create point array
    int numPoints = points.size();

    // Use library POINT to draw
    Point *pointArray = new Point[numPoints];
    for (int i = 0; i < numPoints; i++)
    {
        pointArray[i].X = points[i].getX();
        pointArray[i].Y = points[i].getY();
    }

    // fill polygon
    graphics.FillPolygon(brush, pointArray, numPoints);

    // free memory
    delete[] pointArray;
    // }

    Pen* pen = penRender.getSolidPen(attributes);
    LinearGradientManager *temp = penRender.getPenLinear(static_cast<Fill *>(attributes.getAttributes("fill"))->getId(), attributes);
    Gdiplus::Pen *penLinear = nullptr;
    if (temp != nullptr)
    {
        penLinear = temp->getPen();
    }
    // create point array
    numPoints = points.size();
    pointArray = new Point[numPoints];
    for (int i = 0; i < numPoints; i++)
    {
        pointArray[i].X = points[i].getX();
        pointArray[i].Y = points[i].getY();
    }

    // draw polyline
    graphics.SetSmoothingMode(SmoothingMode::SmoothingModeAntiAlias);
    Gdiplus::Matrix a;
    static_cast<Transform *>(attributes.getAttributes("transform"))->transform(a);
    graphics.MultiplyTransform(&a);

    // Gdiplus::Matrix originalMatrix;
    // graphics.GetTransform(&originalMatrix);
    // graphics.SetTransform(&a);

    graphics.DrawLines(pen, pointArray, numPoints);

    // Use penLinear
    if (penLinear != nullptr)
        graphics.DrawLines(penLinear, pointArray, numPoints);
    
    graphics.SetTransform(&currentMatrix);

    // free memory
    delete[] pointArray;
    // }
    delete pen;
    delete brush;
    if (penLinear != nullptr)
        delete penLinear;
    if (temp != nullptr)
        delete temp;
}