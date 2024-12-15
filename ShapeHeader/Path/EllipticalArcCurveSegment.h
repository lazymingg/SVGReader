#ifndef _ELLIPTICAL_ARC_CURVE_SEGMENT_H_
#define _ELLIPTICAL_ARC_CURVE_SEGMENT_H_

#include "Segment.h"

class EllipticalArcCurveSegment : public Segment
{
    float CalculateVectorAngle(float ux, float uy, float vx, float vy);
    MyPoint::Point setSegment(const char &curCommand, const std::string& data, int& index, MyPoint::Point start, MyPoint::Point &point1);
    virtual ~EllipticalArcCurveSegment() { segment.Reset(); }
};

#endif