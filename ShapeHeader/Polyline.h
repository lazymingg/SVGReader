#ifndef _POLYLINE_H_
#define _POLYLINE_H_

#include "Figure.h"
#include <vector>
#include <sstream>
#include "Point.h"

using namespace Gdiplus;
using namespace std;
using namespace rapidxml;

namespace MyFigure
{
	class Polyline : public Figure
	{
	private:
		vector<MyPoint::Point> points;
	public:
		//intialyze list 
		Polyline(xml_node<>* rootNode, Gdiplus::Graphics& graphics);
		//to string
		void printInfomation();
		void draw() override;
	};
}

#endif