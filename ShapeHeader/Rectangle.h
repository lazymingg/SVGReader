#ifndef _RECTANGLE_H_
#define _RECTANGLE_H_

#include "Figure.h"
#include "Point.h"

using namespace Gdiplus;
using namespace std;
using namespace rapidxml;
namespace MyFigure
{
	class Rectangle : public Figure
	{
	private:
		MyPoint::Point point;
		float height;
		float width;
	public:
		//intialyze list 
		Rectangle(xml_node<>* rootNode, Gdiplus::Graphics& graphics);
		//to string
		void printInfomation();
		void draw() override;
	};
}

#endif
