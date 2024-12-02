#ifndef _ELLIPSE_H
#define _ELLIPSE_H

#include "Figure.h"
#include "Point.h"

using namespace Gdiplus;
using namespace rapidxml;

namespace MyFigure
{
	class Ellipse : public Figure
	{
	protected:
		MyPoint::Point center;
		INT rx;
		INT ry;
	public:
		// Parameterized constructor: form rootNode
		Ellipse(xml_node<>* rootNode, Gdiplus::Graphics& graphics);
		void drawEllipse(Graphics& graphics);
		void draw() override;
		void applyTransform() override;
	};
}

#endif