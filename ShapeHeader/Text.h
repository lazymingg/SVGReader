#ifndef _TEXT_H_
#define _TEXT_H_

#include "Figure.h"
#include "Point.h"
#include "Path.h"


using namespace Gdiplus;
using namespace std;
using namespace rapidxml;

namespace MyFigure
{
	class Text : public Figure
	{
	private:
		MyPoint::Point point;
		float dx;
		float dy;
	public:
		//intialyze list 
		Text(xml_node<>* rootNode, Gdiplus::Graphics& graphics);
		//to string
		void printInfomation();
		void draw() override;
		void applyTransform() override;
	};
}

#endif
