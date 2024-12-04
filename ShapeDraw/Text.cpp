#include "../ShapeHeader/Text.h" // Adjust the path as needed

using namespace Gdiplus;
using namespace std;
using namespace rapidxml;

MyFigure::Text::Text(xml_node<> *rootNode, Gdiplus::Graphics &graphics) : Figure(rootNode, graphics)
{
    string getX = rootNode->first_attribute("x")->value();
    string getY = rootNode->first_attribute("y")->value();
    string getFont = rootNode->first_attribute("font-size")->value();
    this->point.setX(stoi(getX));
    this->point.setY(stoi(getY));
    this->font = stoi(getFont);
}

void MyFigure::Text::printInfomation()
{
    cout << "Text" << endl;
    point.print();
    cout << font << '\n';
    attributes.printAttributes();
}

void MyFigure::Text::draw()
{
    // Get fill color and adjust opacity
    Color fillColor = attributes.getFillColor();
    int opacity = static_cast<int>(attributes.getFillOpacity() * 255);
    fillColor = Color(opacity, fillColor.GetR(), fillColor.GetG(), fillColor.GetB());
    SolidBrush brush(fillColor);

    // Set font
    FontFamily fontFamily(L"Times New Roman");
    Font fontDraw(&fontFamily, this->font, FontStyleRegular, UnitPixel);

    // Convert text content to wide string
    string text = attributes.getText();
    std::wstring wideText(text.begin(), text.end());

    // Adjust the Y coordinate to move the text up
    PointF pointF(point.getX(), point.getY()); // Adjust the value as needed

    // Create a StringFormat object and set the vertical alignment to bottom
    StringFormat format;
    format.SetLineAlignment(StringAlignmentFar); // Align text to the bottom

    Color strokeColor = attributes.getStrokeColor();
    // Adjust opacity
    opacity = static_cast<int>(attributes.getStrokeOpacity() * 255);
    strokeColor = Color(opacity, strokeColor.GetR(), strokeColor.GetG(), strokeColor.GetB());
    Pen pen(strokeColor, attributes.getStrokeWidth());

    // Draw the text with the specified format
    Gdiplus::GraphicsPath textToPath;
    textToPath.StartFigure();
    textToPath.AddString(wideText.c_str(), wideText.length(), &fontFamily, 0, font, pointF, &format);

    int pointCount = textToPath.GetPointCount();
    if (pointCount == 0)
        return;

    Gdiplus::Point* points = new Gdiplus::Point[pointCount];
    textToPath.GetPathPoints(points, pointCount);

    BYTE* pathTypes = new BYTE[pointCount];
    textToPath.GetPathTypes(pathTypes, pointCount);

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
    vector<int> z(pointCount, 1);
    matrixData.push_back(z);

    MyMatrix::Matrix pathMatrix(matrixData);

    cout << "Path matrix before multiplying";
    pathMatrix.print();

    // apply transform
    this->attributes.getTransform().transform(pathMatrix);
    cout << "Path matrix after multiplying";
    pathMatrix.print();

    textToPath.Reset();
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
            textToPath.AddLine(currentPoint.getX(), currentPoint.getY(), pathMatrix.getMatrix()[0][i], pathMatrix.getMatrix()[1][i]);
            currentPoint = MyPoint::Point(pathMatrix.getMatrix()[0][i], pathMatrix.getMatrix()[1][i]);
            break;
        case Gdiplus::PathPointTypeBezier:
            textToPath.AddBezier(currentPoint.getX(), currentPoint.getY(),
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
            textToPath.CloseFigure();
            currentPoint = startPoint;
        }
    }

    graphics.FillPath(&brush, &textToPath);
    graphics.DrawPath(&pen, &textToPath);

    delete[] points;
    delete[] pathTypes;
}

void MyFigure::Text::applyTransform()
{
    MyMatrix::Matrix textMatrix({{point.getX()}, {point.getY()}, {1}});

    this->attributes.getTransform().transform(textMatrix);

    // Get new data
    point.setX(textMatrix.getElement(0, 0));
    point.setY(textMatrix.getElement(0, 1));
}