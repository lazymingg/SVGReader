#include "..\ShapeHeader\Path.h"

bool isDigit(const char &c)
{
    return c >= '0' && c <= '9';
}

bool isAlpha(const char &c)
{
    return c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z';
}

int extractNumber(const std::string &data, int &i)
{
    std::string numb = "";
    int len = data.length();

    while (i < len && (data[i] == ',' || data[i] == ' '))
        ++i;
    while (i < len && isDigit(data[i]))
        numb += data[i++];
    return !numb.empty() ? stoi(numb) : 0;
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

            if (command == 'M')
            {
                int x = extractNumber(data, i);
                int y = extractNumber(data, i);
                currentPoint = MyPoint::Point(x, y);
                startPoint = currentPoint;
            }
            else if (command == 'L')
            {
                int x = extractNumber(data, i);
                int y = extractNumber(data, i);
                path.AddLine(currentPoint.getX(), currentPoint.getY(), x, y);
                currentPoint = MyPoint::Point(x, y);
            }
            else if (command == 'H')
            {
                int x = extractNumber(data, i);
                path.AddLine(currentPoint.getX(), currentPoint.getY(), x, currentPoint.getY());
                currentPoint.setX(x);
            }
            else if (command == 'V')
            {
                int y = extractNumber(data, i);
                path.AddLine(currentPoint.getX(), currentPoint.getY(), currentPoint.getX(), y);
                currentPoint.setY(y);
            }
            else if (command == 'C')
            {
                int x1 = extractNumber(data, i);
                int y1 = extractNumber(data, i);
                int x2 = extractNumber(data, i);
                int y2 = extractNumber(data, i);
                int x3 = extractNumber(data, i);
                int y3 = extractNumber(data, i);

                path.AddBezier(currentPoint.getX(), currentPoint.getY(), x1, y1, x2, y2, x3, y3);
                currentPoint = MyPoint::Point(x3, y3);
            }
            else if (command == 'Z')
            {
                path.CloseFigure();
                currentPoint = startPoint;
            }
            else
            {
                cout << "Invalide Path's command\n";
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

    applyTransform();

    SolidBrush fillBrush(attributes.getFillColor());
    Pen strokePen(attributes.getStrokeColor(), attributes.getStrokeWidth());
    graphics.DrawPath(&strokePen, &path);

    delete[] points;
    delete[] pathTypes;
}

void MyFigure::Path::applyTransform()
{
    int pointCount = path.GetPointCount();
    if (pointCount == 0)
        return;

    Gdiplus::Point *points = new Gdiplus::Point[pointCount];
    path.GetPathPoints(points, pointCount);

    BYTE *pathTypes = new BYTE[pointCount];
    path.GetPathTypes(pathTypes, pointCount);

    vector<vector<int>> matrixData;
	
	// x is the first line of the matrix
	vector<int> x;
	for (int i = 0; i < pointCount; i++)
		x.push_back(points[i].X);
	matrixData.push_back(x);

	// y is the second line of the matrix
	vector<int> y;
	for (int i = 0; i < pointCount; i++)
		y.push_back(points[i].Y);
	matrixData.push_back(y);

	// the last line of the matrix 1

	vector<int> z;
	for (int i = 0; i < pointCount; i++)
	{
		z.push_back(1);
	}

	matrixData.push_back(z);
	
	MyMatrix::Matrix pathMatrix(matrixData);

	cout << "Path matrix before multiplying";
	pathMatrix.print();

	// apply transform
	this->attributes.getTransform().transform(pathMatrix);
	cout << "Path matrix after multiplying";
	pathMatrix.print();

    path.Reset();
    MyPoint::Point currentPoint, startPoint;
	for (int i = 0; i < pointCount; i++)
	{
        switch (pathTypes[i] & PathPointTypePathTypeMask)
        {
        case Gdiplus::PathPointTypeStart:
            currentPoint = MyPoint::Point(pathMatrix.getMatrix()[0][i], pathMatrix.getMatrix()[1][i]);
            startPoint = currentPoint;
            break;
        case Gdiplus::PathPointTypeLine:
            path.AddLine(currentPoint.getX(), currentPoint.getY(), pathMatrix.getMatrix()[0][i], pathMatrix.getMatrix()[1][i]);
            currentPoint = MyPoint::Point(pathMatrix.getMatrix()[0][i], pathMatrix.getMatrix()[1][i]);
            break;
        case Gdiplus::PathPointTypeBezier:
            path.AddBezier(currentPoint.getX(), currentPoint.getY(),
                            pathMatrix.getMatrix()[0][i], pathMatrix.getMatrix()[1][i],
                            pathMatrix.getMatrix()[0][i + 1], pathMatrix.getMatrix()[1][i + 1],
                            pathMatrix.getMatrix()[0][i + 2], pathMatrix.getMatrix()[1][i + 2]);
            currentPoint = MyPoint::Point(pathMatrix.getMatrix()[0][i + 2], pathMatrix.getMatrix()[1][i + 2]);
            i += 2;
            break;
        default:
            std::cout << "Unknown Type";
            break;
        }

        if (pathTypes[i] & Gdiplus::PathPointTypeCloseSubpath)
        {
            path.CloseFigure();
            currentPoint = startPoint;
        }
	}

    delete[] points;
    delete[] pathTypes;
}
