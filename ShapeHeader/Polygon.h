#ifndef _POLYGON_H_
#define _POLYGON_H_

#include "Figure.h"
#include <vector>
#include <sstream>
#include "Point.h"


using namespace Gdiplus;
using namespace std;
using namespace rapidxml;

namespace MyFigure
{
	class Polygon : public Figure
	{
	private:
		vector <MyPoint::Point> points;
	public:
		//intialyze list 
		Polygon(xml_node<>* rootNode, Gdiplus::Graphics& graphics);
		//to string
		void printInfomation();
		void draw() override;
	};
}

#endif
