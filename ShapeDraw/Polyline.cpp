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
    cout << points << "end" << endl;
    for (i; i < len; ++i)
    {
        x = extractNumber(points, i);
        y = extractNumber(points, i);
        this->points.push_back(MyPoint::Point(x, y));
        cout << x << "," << y << " ";
        while (i < len && (points[i] == ' ' || points[i] == ',' || points[i] == '\n' || points[i] == '\t'))
            ++i;
        --i;
    }
<<<<<<< HEAD
    cout << endl;
=======
>>>>>>> AnhTRis
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

    Pen *pen = penRender.getSolidPen(attributes);
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
    {
        // Transform coordinates if gradientUnits is objectBoundingBox
        if (!temp->getIsUserSpaceOnUse())
        {
            // Calculate the bounding box of the polyline
            float minX = points[0].getX(), minY = points[0].getY();
            float maxX = points[0].getX(), maxY = points[0].getY();
            for (const auto &point : points)
            {
                if (point.getX() < minX)
                    minX = point.getX();
                if (point.getY() < minY)
                    minY = point.getY();
                if (point.getX() > maxX)
                    maxX = point.getX();
                if (point.getY() > maxY)
                    maxY = point.getY();
            }
            Gdiplus::RectF bbox(minX, minY, maxX - minX, maxY - minY);
            temp->transformCoordinates(bbox);
        }
        LinearGradientBrush *brushLinear = temp->getBrush();
        graphics.FillPolygon(brushLinear, pointArray, numPoints);
    }
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