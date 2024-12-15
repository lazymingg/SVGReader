#include "../../ShapeHeader/Path/EllipticalArcCurveSegment.h"
#include "EllipticalArcCurveSegment.h"

float EllipticalArcCurveSegment::CalculateVectorAngle(float ux, float uy, float vx, float vy)
{
    float ta = atan2(uy, ux);
    float tb = atan2(vy, vx);

    if (tb >= ta) {
        return tb - ta;
    }

    return 2.0 * PI - (ta - tb);
}

MyPoint::Point EllipticalArcCurveSegment::setSegment(const char &curCommand, const std::string &data, int &index, MyPoint::Point start, MyPoint::Point &point1)
{
    MyPoint::Point radius = {extractNumber(data, index), extractNumber(data, index)};
    float rotation = extractNumber(data, index);
    bool largeArcFlag = bool(extractNumber(data, index));
    bool sweepFlag = bool(extractNumber(data, index));
    
    // End point
    point1 = toAbsolute(curCommand, data, index, start);

    if (point1.getX() == start.getX() && point1.getY() == start.getY())
        return start;

    if (radius.getX() == 0 || radius.getY() == 0)
        segment.AddLine
        (
            start.getX(), start.getY(),
            point1.getX(), point1.getY()
        );

    else
    {
        float rX = abs(radius.getX());
        float rY = abs(radius.getY());

        float sinPhi = sin(rotation * PI / 180);
        float cosPhi = cos(rotation * PI / 180);

        float dx = (start.getX() - point1.getX()) / 2.0f;
        float dy = (start.getY() - point1.getY()) / 2.0f;

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
            cosPhi * centerDash.getX() - sinPhi * centerDash.getY() + (start.getX() + point1.getX()) / 2,
            sinPhi * centerDash.getX() + cosPhi * centerDash.getY() + (start.getY() + point1.getY()) / 2
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

        for (int i = 0; i < segments; ++index)
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

            segment.AddBezier
            (
                start.getX(), start.getY(),
                start.getX() + d1.getX(), start.getY() + d1.getY(),
                end.getX() + de.getX(), end.getY() + de.getY(),
                end.getX(), end.getY()
            );

            theta1 = theta2;
            start = end;     
        }
    }

    return point1;
}