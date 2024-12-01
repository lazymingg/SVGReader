#ifndef _LINE_H_
#define _LINE_H_

#include "Figure.h"
#include <vector>
#include <sstream>
#include "Point.h"

using namespace Gdiplus;
using namespace std;
using namespace rapidxml;

namespace MyFigure
{
	class Line : public Figure
	{
	private:
		MyPoint::Point start;
		MyPoint::Point end;
	public:
		//intialyze list 
		Line(xml_node<>* rootNode, Gdiplus::Graphics& graphics);
		//to string
		void printInfomation();
		void draw() override;
		void applyTransform() override;
	};
}

#endif
