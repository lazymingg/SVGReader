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
    // cout << "polygon" << endl;
    // attributes.printAttributes();
    for (int i = 0; i < points.size(); i++)
    {
        points[i].print();
    }
}
void MyFigure::Polygon::draw()
{
    // Lấy giá trị `viewBox` scale từ `graphics`
    Gdiplus::Matrix currentMatrix;
    graphics.GetTransform(&currentMatrix);
    // Fill color
    Color fillColor = static_cast<Fill *>(attributes.getAttributes("fill"))->getFill();
    int fillOpacity = static_cast<FillOpacity *>(attributes.getAttributes("fill-opacity"))->getFillOpacity() * fillColor.GetA();

    fillColor = Color(fillOpacity, fillColor.GetR(), fillColor.GetG(), fillColor.GetB());
    SolidBrush *brush = new SolidBrush(fillColor);

    // Stroke color
    Color strokeColor = static_cast<Stroke *>(attributes.getAttributes("stroke"))->getStroke();
    int strokeOpacity = static_cast<StrokeOpacity *>(attributes.getAttributes("stroke-opacity"))->getStrokeOpacity() * strokeColor.GetA();

    strokeColor = Color(strokeOpacity, strokeColor.GetR(), strokeColor.GetG(), strokeColor.GetB());
    Pen *pen = new Pen(strokeColor, static_cast<StrokeWidth *>(attributes.getAttributes("stroke-width"))->getStrokeWidth());
    // Prepare points
    std::vector<Point> pointArray(points.size());
    for (size_t i = 0; i < points.size(); i++)
    {
        pointArray[i] = Point(points[i].getX(), points[i].getY());
    }

    // Apply transformation
    Gdiplus::Matrix transformMatrix;
    static_cast<Transform *>(attributes.getAttributes("transform"))->transform(transformMatrix);
    graphics.MultiplyTransform(&transformMatrix);

    // Gdiplus::Matrix originalMatrix;
    // graphics.GetTransform(&originalMatrix);
    // graphics.SetTransform(&transformMatrix);

    // Draw filled polygon
    graphics.SetSmoothingMode(SmoothingMode::SmoothingModeAntiAlias);
    graphics.FillPolygon(brush, pointArray.data(), pointArray.size());

    // Draw polygon outline
    cout << "Draw polygon";
    graphics.DrawPolygon(pen, pointArray.data(), pointArray.size());

    // Restore original matrix
    graphics.SetTransform(&currentMatrix);
    delete pen;
    delete brush;
}