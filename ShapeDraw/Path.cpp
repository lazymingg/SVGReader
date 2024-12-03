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
        cout << data[i] << endl;
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

    pointCount = path.GetPointCount();
    Gdiplus::Point *points = new Gdiplus::Point[pointCount];
    path.GetPathPoints(points, pointCount);
}

void MyFigure::Path::draw()
{
    std::cout << "Path: ";

    if (pointCount == 0)
    {
        std::cout << "Empty\n\n";
        return;
    }

    std::cout << "Path Points:" << std::endl;

    for (int i = 0; i < pointCount; ++i)
    {
        // In thông tin điểm và loại đường
        std::cout << "Point " << i + 1 << ": ("
                  << points[i].X << ", "
                  << points[i].Y << ')' << std::endl;
    }

    SolidBrush fillBrush(attributes.getFillColor());
    Pen strokePen(attributes.getStrokeColor(), attributes.getStrokeWidth());
    graphics.DrawPath(&strokePen, &path);
}

void MyFigure::Path::applyTransform()
{
    vector<vector<int>> matrixData;
	
	// x is the first line of the matrix
	vector<int> x;
	for (int i = 0; i < pointCount; i++)
	{
		x.push_back(points[i].X);
	}
	matrixData.push_back(x);

	// y is the second line of the matrix
	vector<int> y;
	for (int i = 0; i < pointCount; i++)
	{
		y.push_back(points[i].Y);
	}
	matrixData.push_back(y);

	// the last line of the matrix 1

	vector<int> z;
	for (int i = 0; i < pointCount; i++)
	{
		z.push_back(1);
	}

	matrixData.push_back(z);
	

	MyMatrix::Matrix pathMatrix(matrixData);

	cout << "Polygon matrix before multi" << endl;
	pathMatrix.print();

	// apply transform
	this->attributes.getTransform().transform(pathMatrix);
	cout << "Polygon matrix after multi" << endl;
	pathMatrix.print();

	for (int i = 0; i < pointCount; i++)
	{
		points[i].X = (pathMatrix.getMatrix()[0][i]);
		points[i].Y = (pathMatrix.getMatrix()[1][i]);
	}

}
