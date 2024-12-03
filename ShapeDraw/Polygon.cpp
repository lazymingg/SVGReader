#include "../ShapeHeader/Polygon.h"

using namespace Gdiplus;
using namespace std;
using namespace rapidxml;

MyFigure::Polygon::Polygon(xml_node<>* rootNode, Gdiplus::Graphics& graphics) : Figure(rootNode, graphics)
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
// draw polygon here
// draw fill polygon first
	applyTransform();

	Color fillColor = attributes.getFillColor();
	//ajust opacity
	int opacity = attributes.getFillOpacity() * 255;
	fillColor = Color(opacity, fillColor.GetR(), fillColor.GetG(), fillColor.GetB());
	SolidBrush brush(fillColor);
	//print color

	Point* pointArray = new Point[points.size()];
	for (int i = 0; i < points.size(); i++)
	{
		pointArray[i].X = points[i].getX();
		pointArray[i].Y = points[i].getY();
	}
	graphics.FillPolygon(&brush, pointArray, (int)points.size());
	delete[] pointArray;

//draw stroke
	Color strokeColor = attributes.getStrokeColor();
	//ajust opacity
	opacity = attributes.getStrokeOpacity() * 255;
	strokeColor = Color(opacity, strokeColor.GetR(), strokeColor.GetG(), strokeColor.GetB());
	Pen pen(strokeColor, attributes.getStrokeWidth());
	//print color
	graphics.SetSmoothingMode(SmoothingMode::SmoothingModeAntiAlias);
	graphics.DrawPolygon(&pen, (Point*)&points[0], points.size());
}

void MyFigure::Polygon::applyTransform()
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
	

	MyMatrix::Matrix polygonMatrix(matrixData);

	cout << "Polygon matrix before multi" << endl;
	polygonMatrix.print();

	// apply transform
	polygonMatrix = this->attributes.getTransform().doTransform(polygonMatrix);
	cout << "Polygon matrix after multi" << endl;
	polygonMatrix.print();

	for (int i = 0; i < points.size(); i++)
	{
		points[i].setX(polygonMatrix.getMatrix()[0][i]);
		points[i].setY(polygonMatrix.getMatrix()[1][i]);
	}
}