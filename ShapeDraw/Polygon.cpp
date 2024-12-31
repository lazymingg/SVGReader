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
    Brush *brush = penRender.getSolidBrush(attributes);
    Pen *pen = penRender.getSolidPen(attributes);
    LinearGradientManager *temp = penRender.getPenLinear(static_cast<Fill *>(attributes.getAttributes("fill"))->getId(), attributes);
    Gdiplus::Pen *penLinear = nullptr;
    if (temp != nullptr)
    {
        penLinear = temp->getPen();
    }
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

    // Draw filled polygon
    graphics.SetSmoothingMode(SmoothingMode::SmoothingModeAntiAlias);
    graphics.FillPolygon(brush, pointArray.data(), pointArray.size());

    // Draw polygon outline
    cout << "Draw polygon";
    graphics.DrawPolygon(pen, pointArray.data(), pointArray.size());
    if (penLinear != nullptr)
    {
        if (!temp->getIsUserSpaceOnUse())
        {
            // Calculate the bounding box of the polygon
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
        graphics.FillPolygon(brushLinear, pointArray.data(), pointArray.size());
    }

    // Restore original matrix
    graphics.SetTransform(&currentMatrix);
    delete pen;
    delete brush;
    if (penLinear != nullptr)
        delete penLinear;
    if (penLinear != nullptr)
        delete penLinear;
}