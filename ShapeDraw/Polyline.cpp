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
    // draw polygon here
    // draw fill polygon first

    Color fillColor = static_cast<Fill *>(attributes.getAttributes("fill"))->getFill();
    // adjust opacity
    int opacity = static_cast<FillOpacity *>(attributes.getAttributes("fill-opacity"))->getFillOpacity() * fillColor.GetA();

    fillColor = Color(opacity, fillColor.GetR(), fillColor.GetG(), fillColor.GetB());
    SolidBrush *brush = new SolidBrush(fillColor);

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

    // draw stroke
    Color strokeColor = static_cast<Stroke *>(attributes.getAttributes("stroke"))->getStroke();
    // adjust opacity
    opacity = static_cast<StrokeOpacity *>(attributes.getAttributes("stroke-opacity"))->getStrokeOpacity() * strokeColor.GetA();

    strokeColor = Color(opacity, strokeColor.GetR(), strokeColor.GetG(), strokeColor.GetB());
    Pen *pen = new Pen(strokeColor, static_cast<StrokeWidth *>(attributes.getAttributes("stroke-width"))->getStrokeWidth());
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

    Gdiplus::Matrix originalMatrix;
    graphics.GetTransform(&originalMatrix);
    graphics.SetTransform(&a);

    graphics.DrawLines(pen, pointArray, numPoints);
    graphics.SetTransform(&originalMatrix);

    // free memory
    delete[] pointArray;
    // }
    delete pen;
    delete brush;
}