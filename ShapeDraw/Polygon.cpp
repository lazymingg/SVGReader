#include "../ShapeHeader/Polygon.h"

using namespace Gdiplus;
using namespace std;
using namespace rapidxml;

MyFigure::Polygon::Polygon(xml_node<> *rootNode, Gdiplus::Graphics &graphics) : Figure(rootNode, graphics)
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
    // }
}

void MyFigure::Polygon::printInfomation()
{
    cout << "polygon" << endl;
    attributes.printAttributes();
    for (int i = 0; i < points.size(); i++)
    {
        points[i].print();
    }
}
void MyFigure::Polygon::draw()
{
    // Fill color
    Color fillColor = attributes.getFillColor();
    int fillOpacity = attributes.getFillOpacity() * 255;
    if (fillColor.GetA() == 0 && fillColor.GetR() == 0 && fillColor.GetG() == 0 && fillColor.GetB() == 0)
    {
        fillOpacity = 0;
    }

    fillColor = Color(fillOpacity, fillColor.GetR(), fillColor.GetG(), fillColor.GetB());
    SolidBrush brush(fillColor);

    // Stroke color
    Color strokeColor = attributes.getStrokeColor();
    int strokeOpacity = attributes.getStrokeOpacity() * 255;

    strokeColor = Color(strokeOpacity, strokeColor.GetR(), strokeColor.GetG(), strokeColor.GetB());
    Pen pen(strokeColor, attributes.getStrokeWidth());

    // Prepare points
    std::vector<Point> pointArray(points.size());
    for (size_t i = 0; i < points.size(); i++)
    {
        pointArray[i] = Point(points[i].getX(), points[i].getY());
    }

    // Apply transformation
    Gdiplus::Matrix transformMatrix;
    attributes.getTransform().transform(transformMatrix);

    Gdiplus::Matrix originalMatrix;
    graphics.GetTransform(&originalMatrix);
    graphics.SetTransform(&transformMatrix);

    // Draw filled polygon
    graphics.SetSmoothingMode(SmoothingMode::SmoothingModeAntiAlias);
    graphics.FillPolygon(&brush, pointArray.data(), pointArray.size());

    // Draw polygon outline
    cout << "Draw polygon";
    graphics.DrawPolygon(&pen, pointArray.data(), pointArray.size());

    // Restore original matrix
    graphics.SetTransform(&originalMatrix);
}