#include "../../ShapeHeader/Path/Path.h"

MyFigure::Path::Path(xml_node<> *rootNode, Gdiplus::Graphics &graphics) : Figure(rootNode, graphics)
{
    if (!rootNode) return;

    std::string data = rootNode->first_attribute("d")->value();
    if (data == "none") return;

    MyPoint::Point currentPoint, startPoint, point1, point2, point3;
    char curCommand, prevCommand = '\0';

    int len = data.length();
    for (int i = 0; i < len; ++i)
    {
        if (isAlpha(data[i]) || isDigit(data[i]) || data[i] == '-'|| data[i] == '+')
        {
            if (isalpha(data[i]))
                curCommand = data[i++];
            
            if (curCommand == prevCommand)
            {
                if (prevCommand == 'M')
                    curCommand = 'L';
                else if (prevCommand == 'm')
                    curCommand = 'l';
            }

            while (i < len && (data[i] == ' ' || data[i] == '\n'))
                ++i;

            cout << "Current command: " << curCommand << " - prev command: " << prevCommand << endl;

            switch (curCommand)
            {
                // Move-to commands
                case 'M':
                {
                    startPoint = currentPoint = {extractNumber(data, i), extractNumber(data, i)};
                    break;
                }
            
                case 'm':
                {
                    if (prevCommand == '\0')
                        startPoint = currentPoint = {extractNumber(data, i), extractNumber(data, i)};
                    else
                        startPoint = currentPoint = {currentPoint.getX() + extractNumber(data, i), currentPoint.getY() + extractNumber(data, i)};
                    break;
                }

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
                    Segment *segment = generator.generateSegment(prevCommand, curCommand, data, i, currentPoint, point1, point2, point3);
                    path.AddPath(&segment->getSegment(), true);
                    break;
                }
            }

            while (i < len && (data[i] == ',' || data[i] == ' ' || data[i] == '\n'))
                ++i;
            
            --i;

            prevCommand = curCommand;
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
        switch (pathTypes[i] & PathPointType::PathPointTypePathTypeMask)
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

    // cout << int(attributes.getFillColor().GetAlpha()) << ", " << int(attributes.getFillColor().GetRed()) << ", " << int(attributes.getFillColor().GetGreen()) << ", " << int(attributes.getFillColor().GetBlue()) << endl;
    // cout << int(attributes.getStrokeColor().GetAlpha()) << ", " << int(attributes.getStrokeColor().GetRed()) << ", " << int(attributes.getStrokeColor().GetGreen()) << ", " << int(attributes.getStrokeColor().GetBlue()) << endl;
    
    Color fillColor = static_cast<Fill*>(attributes.getAttributes("fill"))->getFill();
    int fillOpacity = static_cast<FillOpacity*>(attributes.getAttributes("fill-opacity"))->getFillOpacity() * fillColor.GetA();

    fillColor = Color(fillOpacity, fillColor.GetR(), fillColor.GetG(), fillColor.GetB());
    SolidBrush *fillBrush = new SolidBrush(fillColor);

    Color strokeColor = static_cast<Stroke*>(attributes.getAttributes("stroke"))->getStroke();
    int strokeOpacity = static_cast<StrokeOpacity*>(attributes.getAttributes("stroke-opacity"))->getStrokeOpacity() * strokeColor.GetA();
    strokeColor = Color(strokeOpacity, strokeColor.GetR(), strokeColor.GetG(), strokeColor.GetB());
    Pen *strokePen = new Pen(strokeColor, static_cast<StrokeWidth*>(attributes.getAttributes("stroke-width"))->getStrokeWidth());

    graphics.SetSmoothingMode(SmoothingModeAntiAlias);

    Gdiplus::Matrix a;
    static_cast<Transform*>(attributes.getAttributes("transform"))->transform(a);

    Gdiplus::Matrix originalMatrix;
    graphics.GetTransform(&originalMatrix);
    graphics.SetTransform(&a);

    graphics.FillPath(fillBrush, &path);

    graphics.DrawPath(strokePen, &path);
    graphics.SetTransform(&originalMatrix);

    delete[] points;
    delete[] pathTypes;
    delete fillBrush;
    delete strokePen;
}