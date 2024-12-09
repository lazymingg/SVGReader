#include "../ShapeHeader/Path.h"

bool isDigit(const char &c)
{
    return c >= '0' && c <= '9';
}

bool isAlpha(const char &c)
{
    return c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z';
}

float extractNumber(const std::string &data, int &i)
{
    std::string numb = "";
    int len = data.length();

    while (i < len && (data[i] == ',' || data[i] == ' '))
        ++i;
    while (i < len && isDigit(data[i]))
        numb += data[i++];
    return !numb.empty() ? stof(numb) : 0;
}

MyFigure::Path::Path(xml_node<> *rootNode, Gdiplus::Graphics &graphics) : Figure(rootNode, graphics)
{
    if (!rootNode)
        return;

    std::string data = rootNode->first_attribute("d")->value();

    if (data == "none")
        return;

    MyPoint::Point currentPoint, startPoint;

    int len = data.length();
    for (int i = 0; i < len; ++i)
    {
        if (isAlpha(data[i]))
        {
            char command = data[i++];

            while (i < len && data[i] == ' ')
                ++i;

            switch (command)
            {
                // Move-to commands
                case 'M':
                {
                    float x = extractNumber(data, i);
                    float y = extractNumber(data, i);
                    currentPoint = MyPoint::Point(x, y);
                    startPoint = currentPoint;
                    break;
                }
            
                case 'm':
                {
                    float dx = extractNumber(data, i);
                    float dy = extractNumber(data, i);
                    currentPoint = MyPoint::Point(currentPoint.getX() + dx, currentPoint.getY() + dy);
                    startPoint = currentPoint;
                    break;
                }

                // Line-to commands
                case 'L':
                {
                    float x = extractNumber(data, i);
                    float y = extractNumber(data, i);
                    path.AddLine(currentPoint.getX(), currentPoint.getY(), x, y);
                    currentPoint = MyPoint::Point(x, y);
                    break;
                }

                case 'l':
                {
                    float dx = extractNumber(data, i);
                    float dy = extractNumber(data, i);
                    path.AddLine(currentPoint.getX(), currentPoint.getY(), currentPoint.getX() + dx, currentPoint.getY() + dy);
                    currentPoint = MyPoint::Point(currentPoint.getX() + dx, currentPoint.getY() + dy);
                    break;
                }

                case 'H':
                {
                    float x = extractNumber(data, i);
                    path.AddLine(currentPoint.getX(), currentPoint.getY(), x, currentPoint.getY());
                    currentPoint.setX(x);
                    break;
                }

                case 'h':
                {
                    float dx = extractNumber(data, i);
                    path.AddLine(currentPoint.getX(), currentPoint.getY(), currentPoint.getX() + dx, currentPoint.getY());
                    currentPoint.setX(currentPoint.getX() + dx);
                    break;
                }

                case 'V':
                {
                    float y = extractNumber(data, i);
                    path.AddLine(currentPoint.getX(), currentPoint.getY(), currentPoint.getX(), y);
                    currentPoint.setY(y);
                    break;
                }

                case 'v':
                {
                    float dy = extractNumber(data, i);
                    path.AddLine(currentPoint.getX(), currentPoint.getY(), currentPoint.getX(), currentPoint.getY() + dy);
                    currentPoint.setY(currentPoint.getY() + dy);
                    break;
                }

                // Cubic-Bézier-curve commands
                case 'C':
                {
                    float x1 = extractNumber(data, i);
                    float y1 = extractNumber(data, i);
                    float x2 = extractNumber(data, i);
                    float y2 = extractNumber(data, i);
                    float x3 = extractNumber(data, i);
                    float y3 = extractNumber(data, i);

                    path.AddBezier(currentPoint.getX(), currentPoint.getY(), x1, y1, x2, y2, x3, y3);
                    currentPoint = MyPoint::Point(x3, y3);
                    break;
                }

                case 'c':
                {
                    float dx1 = extractNumber(data, i);
                    float dy1 = extractNumber(data, i);
                    float dx2 = extractNumber(data, i);
                    float dy2 = extractNumber(data, i);
                    float dx3 = extractNumber(data, i);
                    float dy3 = extractNumber(data, i);

                    path.AddBezier(currentPoint.getX(), currentPoint.getY(), 
                                    currentPoint.getX() + dx1, currentPoint.getY() + dy1, 
                                    currentPoint.getX() + dx2, currentPoint.getY() + dy2, 
                                    currentPoint.getX() + dx3, currentPoint.getY() + dy3);
                    currentPoint = MyPoint::Point(currentPoint.getX() + dx3, currentPoint.getY() + dy3);
                    break;
                }

                case 'A':
                break;

                case 'a':
                break;

                case 'S':
                break;

                case 's':
                break;

                // Close-path commands
                case 'Z':
                case 'z':
                {
                    path.CloseFigure();
                    currentPoint = startPoint;
                    break;
                }

                default:
                {
                    cout << "Invalide Path's command\n";
                    break;
                }
            }

            --i;
            while (i < len && (data[i] == ',' || data[i] == ' '))
                ++i;
        }
    }
}

void MyFigure::Path::draw()
{
    int pointCount = path.GetPointCount();

    std::cout << "Path: ";

    if (pointCount == 0)
    {
        std::cout << "Empty\n\n";
        return;
    }

    Gdiplus::Point *points = new Gdiplus::Point[pointCount];
    path.GetPathPoints(points, pointCount);
    BYTE *pathTypes = new BYTE[pointCount];
    path.GetPathTypes(pathTypes, pointCount);

    std::cout << "Path Points and Path Types:" << std::endl;
    for (int i = 0; i < pointCount; ++i)
    {
        std::cout << "Point " << i + 1 << ": ("
                  << points[i].X << ", "
                  << points[i].Y << ") - Type: ";

        // Giải thích loại đường (Path Type)
        switch (pathTypes[i] & PathPointTypePathTypeMask)
        {
        case Gdiplus::PathPointTypeStart:
            std::cout << "Start Point";
            break;
        case Gdiplus::PathPointTypeLine:
            std::cout << "Line Segment";
            break;
        case Gdiplus::PathPointTypeBezier:
            std::cout << "Bezier Curve";
            break;
        default:
            std::cout << "Unknown Type";
            break;
        }

        if (pathTypes[i] & Gdiplus::PathPointTypeCloseSubpath)
        {
            std::cout << " (Closed Subpath)";
        }

        std::cout << std::endl;
    }

    SolidBrush fillBrush(attributes.getFillColor());
    Pen strokePen(attributes.getStrokeColor(), attributes.getStrokeWidth());
    graphics.SetSmoothingMode(SmoothingModeAntiAlias);

    Gdiplus::Matrix a;
    attributes.getTransform().transform(a);

    Gdiplus::Matrix originalMatrix;
    graphics.GetTransform(&originalMatrix);
    graphics.SetTransform(&a);

    graphics.FillPath(&fillBrush, &path);

    graphics.DrawPath(&strokePen, &path);
    graphics.SetTransform(&originalMatrix);

    delete[] points;
    delete[] pathTypes;
}

void MyFigure::Path::applyTransform()
{
}
