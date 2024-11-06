#include "../ShapeHeader/Polyline.h"
using namespace Gdiplus;
using namespace std;
using namespace rapidxml;

MyFigure::Polyline::Polyline(xml_node<> *rootNode, Gdiplus::Graphics &graphics) : Figure(rootNode, graphics)
{
    // Đặt các điểm từ thuộc tính "points"
    string points = rootNode->first_attribute("points")->value();
    stringstream ss(points);
    string point;
    while (getline(ss, point, ' '))
    {
        stringstream ssPoint(point);
        string x, y;
        getline(ssPoint, x, ',');
        getline(ssPoint, y, ',');
        this->points.push_back(MyPoint::Point(stoi(x), stoi(y)));
    }
}

void MyFigure::Polyline::printInfomation()
{
    cout << "Polyline:" << endl;
    for (int i = 0; i < points.size(); i++)
        points[i].print();
    attributes.printAttributes();
}

void MyFigure::Polyline::draw()
{
    // draw polygon here
    // draw fill polygon first
    // if (attributes.getFill() != "none" || attributes.getFillOpacity() != 0)
    // {
        Color fillColor = attributes.getFillColor();
        // adjust opacity
        int opacity = attributes.getFillOpacity() * 255;
        fillColor = Color(opacity, fillColor.GetR(), fillColor.GetG(), fillColor.GetB());
        SolidBrush brush(fillColor);

        // create point array
        int numPoints = points.size();

        //Use library POINT to draw
        Point* pointArray = new Point[numPoints];
        for (int i = 0; i < numPoints; i++)
        {
            pointArray[i].X = points[i].getX();
            pointArray[i].Y = points[i].getY();
        }

        // fill polygon
        graphics.FillPolygon(&brush, pointArray, numPoints);

        // free memory
        delete[] pointArray;
    // }

    // draw stroke
    // if (attributes.getStroke() != "none")
    // {
        Color strokeColor = attributes.getStrokeColor();
        // adjust opacity
        opacity = attributes.getStrokeOpacity() * 255;
        strokeColor = Color(opacity, strokeColor.GetR(), strokeColor.GetG(), strokeColor.GetB());
        Pen pen(strokeColor, attributes.getStrokeWidth());

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
        graphics.DrawLines(&pen, pointArray, numPoints);

        // free memory
        delete[] pointArray;
    // }
}