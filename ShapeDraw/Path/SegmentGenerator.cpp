#include "../../ShapeHeader/Path/SegmentGenerator.h"

Segment* SegmentGenerator::generateSegment(const char &prevCommand, const char &curCommand, const std::string &data, int &index, MyPoint::Point &start, MyPoint::Point &point1, MyPoint::Point &point2, MyPoint::Point &point3)
{
    switch (curCommand)
    {
        // Line-to commands
        case 'L':
        case 'l':
        {
            LineSegment *segment = new LineSegment();
            start = segment->setSegment(curCommand, data, index, start);
            return segment;
        }

        case 'H':
        case 'h':
        {
            HorizontalLineSegment *segment = new HorizontalLineSegment();
            start = segment->setSegment(curCommand, data, index, start);
            return segment;
        }

        case 'V':
        case 'v':
        {
            VerticalLineSegment *segment = new VerticalLineSegment();
            start = segment->setSegment(curCommand, data, index, start);
            return segment;
        }

        // Cubic-Bézier-curve commands
        case 'C':
        case 'c':
        {
            CubicBezierSegment *segment = new CubicBezierSegment();
            start = segment->setSegment(curCommand, data, index, start, point1, point2, point3);
            return segment;
        }

        case 'S':
        case 's':
        {
            SmoothCubicBezierSegment *segment = new SmoothCubicBezierSegment();
            start = segment->setSegment(curCommand, prevCommand, data, index, start, point1, point2, point3);
            return segment;
        }

        // Quadratic-Bézier-curve commands
        case 'Q':
        case 'q':
        {
            QuadraticBezierSegment *segment = new QuadraticBezierSegment();
            start = segment->setSegment(curCommand, data, index, start, point1, point2);
            return segment;
        }

        case 'T':
        case 't':
        {
            SmoothQuadraticBezierSegment *segment = new SmoothQuadraticBezierSegment();
            start = segment->setSegment(curCommand, prevCommand, data, index, start, point1, point2);
            return segment;
        }

        // Elliptical-arc-curve commands
        // Source: https://github.com/svg-net/SVG/blob/master/Source/Paths/SvgArcSegment.Drawing.cs
        case 'A':
        case 'a':
        {
            EllipticalArcCurveSegment *segment = new EllipticalArcCurveSegment();
            start = segment->setSegment(curCommand, data, index, start, point1);
            return segment;
        }

        default:
        {
            cout << "Invalid command\n";
            break;
        }
    }

    return nullptr;
}