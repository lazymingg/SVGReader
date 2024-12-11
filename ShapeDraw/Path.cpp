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

float MyFigure::Path::CalculateVectorAngle(float ux, float uy, float vx, float vy)
{
    float ta = atan2(uy, ux);
    float tb = atan2(vy, vx);

    if (tb >= ta) {
        return tb - ta;
    }

    return 2.0 * PI - (ta - tb);
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

            cout << "Current command: " << curCommand << endl;
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
                // Source: https://github.com/svg-net/SVG/blob/master/Source/Paths/SvgArcSegment.Drawing.cs
                case 'A':
                case 'a':
                {
                    MyPoint::Point radius = {extractNumber(data, i), extractNumber(data, i)};
                    float rotation = extractNumber(data, i);
                    bool largeArcFlag = bool(extractNumber(data, i));
                    bool sweepFlag = bool(extractNumber(data, i));
                    
                    // End point
                    if (curCommand == 'A')
                        point1 = {extractNumber(data, i), extractNumber(data, i)};
                    else if (curCommand == 'a')
                        point1 = {currentPoint.getX() + extractNumber(data, i), currentPoint.getY() + extractNumber(data, i)};

                    if (point1.getX() == currentPoint.getX() && point1.getY() == currentPoint.getY())
                        break;

                    if (radius.getX() == 0 || radius.getY() == 0)
                        path.AddLine
                        (
                            currentPoint.getX(), currentPoint.getY(),
                            point1.getX(), point1.getY()
                        );

                    else
                    {
                        float rX = abs(radius.getX());
                        float rY = abs(radius.getY());

                        float sinPhi = sin(rotation * PI / 180);
                        float cosPhi = cos(rotation * PI / 180);

                        float dx = (currentPoint.getX() - point1.getX()) / 2.0f;
                        float dy = (currentPoint.getY() - point1.getY()) / 2.0f;

                        MyPoint::Point dash1 = {cosPhi * dx + sinPhi * dy, -sinPhi * dx + cosPhi * dy};

                        float root;
                        float numerator = rX * rX * rY * rY - rX * rX * dash1.getY() * dash1.getY() - rY * rY * dash1.getX() * dash1.getX();

                        if (numerator < 0.0f)
                        {
                            float scale = sqrt(1.0 - numerator / (rX * rX * rY * rY));
                            rX *= scale;
                            rY *= scale;
                            root = 0;
                        }
                        else
                            root = ((largeArcFlag && sweepFlag) || (!largeArcFlag && !sweepFlag) ? -1 : 1) * sqrt(numerator / (rX * rX * dash1.getY() * dash1.getY() + rY * rY * dash1.getX() * dash1.getX()));

                        MyPoint::Point centerDash = {root * rX * dash1.getY() / rY, -root * rY * dash1.getX() / rX};
                        MyPoint::Point center = 
                        {
                            cosPhi * centerDash.getX() - sinPhi * centerDash.getY() + (currentPoint.getX() + point1.getX()) / 2,
                            sinPhi * centerDash.getX() + cosPhi * centerDash.getY() + (currentPoint.getY() + point1.getY()) / 2
                        };

                        float theta1 = CalculateVectorAngle(1.0, 0.0, (dash1.getX() - centerDash.getX()) / rX, (dash1.getY() - centerDash.getY()) / rY);
                        float dTheta = CalculateVectorAngle((dash1.getX() - centerDash.getX()) / rX, (dash1.getY() - centerDash.getY()) / rY, -(dash1.getX() + centerDash.getX()) / rX, -(dash1.getY() + centerDash.getY()) / rY);

                        if (!sweepFlag && dTheta > 0)
                            dTheta -= 2 * PI;
                        else if (sweepFlag && dTheta < 0)
                            dTheta += 2 * PI;

                        int segments = int(ceil(abs(dTheta / (PI / 2))));
                        float delta = dTheta / segments;
                        float t = 8.0 / 3.0 * sin(delta / 4.0) * sin(delta / 4.0) / sin(delta / 2.0);

                        for (int i = 0; i < segments; ++i)
                        {
                            float cosTheta1 = cos(theta1);
                            float sinTheta1 = sin(theta1);
                            float theta2 = theta1 + delta;
                            float cosTheta2 = cos(theta2);
                            float sinTheta2 = sin(theta2);
                            
                            MyPoint::Point end = 
                            {
                                cosPhi * rX * cosTheta2 - sinPhi * rY * sinTheta2 + center.getX(),
                                sinPhi * rX * cosTheta2 + cosPhi * rY * sinTheta2 + center.getY()
                            };

                            MyPoint::Point d1 =
                            {
                                t * (-cosPhi * rX * sinTheta1 - sinPhi * rY * cosTheta1),
                                t * (-sinPhi * rX * sinTheta1 + cosPhi * rY * cosTheta1)
                            };

                            MyPoint::Point de =
                            {
                                t * (cosPhi * rX * sinTheta2 + sinPhi * rY * cosTheta2),
                                t * (sinPhi * rX * sinTheta2 - cosPhi * rY * cosTheta2)
                            };

                            path.AddBezier
                            (
                                currentPoint.getX(), currentPoint.getY(),
                                currentPoint.getX() + d1.getX(), currentPoint.getY() + d1.getY(),
                                end.getX() + de.getX(), end.getY() + de.getY(),
                                end.getX(), end.getY()
                            );

                            theta1 = theta2;
                            currentPoint = end;     
                        }
                    }

                    currentPoint = point1;
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
    Color fillColor = attributes.getFillColor();
    int fillOpacity = attributes.getFillOpacity() * 255;
    if (fillColor.GetA() == 0 && fillColor.GetR() == 0 && fillColor.GetG() == 0 && fillColor.GetB() == 0)
    {
        fillOpacity = 0;
    }
    fillColor = Color(fillOpacity, fillColor.GetR(), fillColor.GetG(), fillColor.GetB());
    SolidBrush fillBrush(fillColor);

    Color strokeColor = attributes.getStrokeColor();
    int strokeOpacity = attributes.getStrokeOpacity() * 255;

    strokeColor = Color(strokeOpacity, strokeColor.GetR(), strokeColor.GetG(), strokeColor.GetB());
    Pen strokePen(strokeColor, attributes.getStrokeWidth());

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