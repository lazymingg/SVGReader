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
    if (len == 0) return 0;

    while (i < len && (data[i] == ',' || data[i] == ' '))
        ++i;

    if (i < len && data[i] == '-')
        numb += data[i++];
    while (i < len && (isDigit(data[i]) || data[i] == '.'))
        numb += data[i++];

    try {
        return !numb.empty() ? stof(numb) : 0;
    } catch (const std::invalid_argument &) {
        std::cerr << "Invalid number in path data: " << numb << std::endl;
        return 0;
    }
}

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
        if (isAlpha(data[i]) || isDigit(data[i]) || data[i] == '-')
        {
            if (isalpha(data[i]))
                curCommand = data[i++];

            while (i < len && data[i] == ' ')
                ++i;

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
                    startPoint = currentPoint = {currentPoint.getX() + extractNumber(data, i), currentPoint.getY() + extractNumber(data, i)};
                    break;
                }

                // Line-to commands
                case 'L':
                {
                    float x = extractNumber(data, i);
                    float y = extractNumber(data, i);
                    path.AddLine(currentPoint.getX(), currentPoint.getY(), x, y);
                    currentPoint = {x, y};
                    break;
                }

                case 'l':
                {
                    float dx = extractNumber(data, i);
                    float dy = extractNumber(data, i);
                    path.AddLine(currentPoint.getX(), currentPoint.getY(), currentPoint.getX() + dx, currentPoint.getY() + dy);
                    currentPoint = {currentPoint.getX() + dx, currentPoint.getY() + dy};
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
                    point1 = {extractNumber(data, i), extractNumber(data, i)};
                    point2 = {extractNumber(data, i), extractNumber(data, i)};
                    point3 = {extractNumber(data, i), extractNumber(data, i)};

                    path.AddBezier
                    (
                        currentPoint.getX(), currentPoint.getY(), 
                        point1.getX(), point1.getY(),
                        point2.getX(), point2.getY(),
                        point3.getX(), point3.getY()
                    );

                    currentPoint = point3;
                    break;
                }

                case 'c':
                {
                    // x = x0 + dx, y = y0 + dy
                    point1 = {currentPoint.getX() + extractNumber(data, i), currentPoint.getY() + extractNumber(data, i)};
                    point2 = {currentPoint.getX() + extractNumber(data, i), currentPoint.getY() + extractNumber(data, i)};
                    point3 = {currentPoint.getX() + extractNumber(data, i), currentPoint.getY() + extractNumber(data, i)};

                    path.AddBezier
                    (
                        currentPoint.getX(), currentPoint.getY(), 
                        point1.getX(), point1.getY(),
                        point2.getX(), point2.getY(),
                        point3.getX(), point3.getY()
                    );

                    currentPoint = point3;
                    break;
                }

                case 'S':
                {
                    if (prevCommand == 'C' || prevCommand == 'c' ||
                        prevCommand == 'S' || prevCommand == 's')
                        point1 = {2 * point3.getX() - point2.getX(), 2 * point3.getY() - point2.getY()};
                    else
                        point1 = currentPoint;
                    point2 = {extractNumber(data, i), extractNumber(data, i)};
                    point3 = {extractNumber(data, i), extractNumber(data, i)};    

                    path.AddBezier
                    (
                        currentPoint.getX(), currentPoint.getY(),
                        point1.getX(), point1.getY(),
                        point2.getX(), point2.getY(),
                        point3.getX(), point3.getY()
                    );

                    currentPoint = point3;
                    break;
                }

                case 's':
                {
                    if (prevCommand == 'C' || prevCommand == 'c' ||
                        prevCommand == 'S' || prevCommand == 's')
                        point1 = {2 * point3.getX() - point2.getX(), 2 * point3.getY() - point2.getY()};
                    else
                        point1 = currentPoint;

                    point2 = {extractNumber(data, i), extractNumber(data, i)};
                    point3 = {extractNumber(data, i), extractNumber(data, i)};

                    point2 = {currentPoint.getX() + point2.getX(), currentPoint.getY() + point2.getY()};
                    point3 = {currentPoint.getX() + point3.getX(), currentPoint.getY() + point3.getY()};

                    path.AddBezier
                    (
                        currentPoint.getX(), currentPoint.getY(),
                        point1.getX(), point1.getY(),
                        point2.getX(), point2.getY(),
                        point3.getX(), point3.getY()
                    );
                    currentPoint = point3;

                    break;
                }

                // Quadratic-Bézier-curve commands
                case 'Q':
                {
                    point1 = {extractNumber(data, i), extractNumber(data, i)};
                    point2 = {extractNumber(data, i), extractNumber(data, i)}; 

                    MyPoint::Point control1 =
                    {
                        currentPoint.getX() + 2.0f / 3 * (point1.getX() - currentPoint.getX()),
                        currentPoint.getY() + 2.0f / 3 * (point1.getY() - currentPoint.getY()),
                    };
                    
                    MyPoint::Point control2 =
                    {                        
                        point2.getX() + 2.0f / 3 * (point1.getX() - point2.getX()),
                        point2.getY() + 2.0f / 3 * (point1.getY() - point2.getY()),
                    };

                    path.AddBezier
                    (
                        currentPoint.getX(), currentPoint.getY(),
                        control1.getX(), control1.getY(),
                        control2.getX(), control2.getY(),    
                        point2.getX(), point2.getY()
                    );

                    currentPoint = point2;
                    break;
                }

                case 'q':
                {
                    point1 = {currentPoint.getX() + extractNumber(data, i), currentPoint.getY() + extractNumber(data, i)};
                    point2 = {currentPoint.getX() + extractNumber(data, i), currentPoint.getY() + extractNumber(data, i)}; 

                    MyPoint::Point control1 =
                    {
                        currentPoint.getX() + 2.0f / 3 * (point1.getX() - currentPoint.getX()),
                        currentPoint.getY() + 2.0f / 3 * (point1.getY() - currentPoint.getY()),
                    };
                    
                    MyPoint::Point control2 =
                    {                        
                        point2.getX() + 2.0f / 3 * (point1.getX() - point2.getX()),
                        point2.getY() + 2.0f / 3 * (point1.getY() - point2.getY()),
                    };

                    path.AddBezier
                    (
                        currentPoint.getX(), currentPoint.getY(),
                        control1.getX(), control1.getY(),
                        control2.getX(), control2.getY(),    
                        point2.getX(), point2.getY()
                    );

                    currentPoint = point2;
                    break;
                }

                case 'T':
                {
                    if (prevCommand == 'Q' || prevCommand == 'q' || 
                        prevCommand == 'T' || prevCommand == 't')
                        point1 =
                        {
                            2 * currentPoint.getX() - point1.getX(),
                            2 * currentPoint.getY() - point1.getY()
                        };
                    else
                        point1 = currentPoint;

                    point2 = {extractNumber(data, i), extractNumber(data, i)}; 

                    MyPoint::Point control1 =
                    {
                        currentPoint.getX() + 2.0f / 3 * (point1.getX() - currentPoint.getX()),
                        currentPoint.getY() + 2.0f / 3 * (point1.getY() - currentPoint.getY()),
                    };
                    
                    MyPoint::Point control2 =
                    {                        
                        point2.getX() + 2.0f / 3 * (point1.getX() - point2.getX()),
                        point2.getY() + 2.0f / 3 * (point1.getY() - point2.getY()),
                    };

                    path.AddBezier
                    (
                        currentPoint.getX(), currentPoint.getY(),
                        control1.getX(), control1.getY(),
                        control2.getX(), control2.getY(),    
                        point2.getX(), point2.getY()
                    );

                    currentPoint = point2;
                    break;
                }

                case 't':
                {
                    if (prevCommand == 'Q' || prevCommand == 'q' || 
                        prevCommand == 'T' || prevCommand == 't')
                        point1 =
                        {
                            2 * currentPoint.getX() - point1.getX(),
                            2 * currentPoint.getY() - point1.getY()
                        };
                    else
                        point1 = currentPoint;

                    point2 = {currentPoint.getX() + extractNumber(data, i), currentPoint.getY() + extractNumber(data, i)}; 

                    MyPoint::Point control1 =
                    {
                        currentPoint.getX() + 2.0f / 3 * (point1.getX() - currentPoint.getX()),
                        currentPoint.getY() + 2.0f / 3 * (point1.getY() - currentPoint.getY()),
                    };
                    
                    MyPoint::Point control2 =
                    {                        
                        point2.getX() + 2.0f / 3 * (point1.getX() - point2.getX()),
                        point2.getY() + 2.0f / 3 * (point1.getY() - point2.getY()),
                    };

                    path.AddBezier
                    (
                        currentPoint.getX(), currentPoint.getY(),
                        control1.getX(), control1.getY(),
                        control2.getX(), control2.getY(),    
                        point2.getX(), point2.getY()
                    );

                    currentPoint = point2;
                    break;
                }

                // Elliptical-arc-curve commands
                case 'A':
                {
                    break;
                }

                case 'a':
                {
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
                    cout << "Invalide Path's command\n";
                    break;
                }
            }

            --i;
            while (i < len && (data[i] == ',' || data[i] == ' '))
                ++i;
            
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

    cout << int(attributes.getFillColor().GetAlpha()) << ", " << int(attributes.getFillColor().GetRed()) << ", " << int(attributes.getFillColor().GetGreen()) << ", " << int(attributes.getFillColor().GetBlue()) << endl;
    cout << int(attributes.getStrokeColor().GetAlpha()) << ", " << int(attributes.getStrokeColor().GetRed()) << ", " << int(attributes.getStrokeColor().GetGreen()) << ", " << int(attributes.getStrokeColor().GetBlue()) << endl;
    SolidBrush fillBrush(attributes.getFillColor());
    Pen strokePen(attributes.getStrokeColor(), attributes.getStrokeWidth());
    graphics.SetSmoothingMode(SmoothingModeAntiAlias);

    // Gdiplus::Matrix a;
//     attributes.getTransform().transform(a);

    // Gdiplus::Matrix originalMatrix;
    // graphics.GetTransform(&originalMatrix);
    // graphics.SetTransform(&a);

    graphics.FillPath(&fillBrush, &path);

    graphics.DrawPath(&strokePen, &path);
    // graphics.SetTransform(&originalMatrix);

    delete[] points;
    delete[] pathTypes;
}

void MyFigure::Path::applyTransform()
{
}
