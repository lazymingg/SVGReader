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
    applyTransform();
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

    // Use library POINT to draw
    Point *pointArray = new Point[numPoints];
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
void MyFigure::Polyline::applyTransform()
{
    vector<vector<int>> matrixData;

    // x is the first line of the matrix
    vector<int> x;
    for (int i = 0; i < points.size(); i++)
    {
        x.push_back(points[i].getX());
    }
    matrixData.push_back(x);

    // y is the second line of the matrix
    vector<int> y;
    for (int i = 0; i < points.size(); i++)
    {
        y.push_back(points[i].getY());
    }
    matrixData.push_back(y);

    // the last line of the matrix 1

    vector<int> z;
    for (int i = 0; i < points.size(); i++)
    {
        z.push_back(1);
    }

    matrixData.push_back(z);

    MyMatrix::Matrix polylineMatrix(matrixData);

    // apply transform
    this->attributes.getTransform().transform(polylineMatrix);

    // get the points after transform
    int numCol = polylineMatrix.getCols();
    for (int i = 0; i < numCol; i++)
    {
        points[i].setX(polylineMatrix.getElement(0, i));
        points[i].setY(polylineMatrix.getElement(1, i));
    }
}