#ifndef CIRCLE_H
#define CIRCLE_H

#include "Figure.h"
#include "Point.h"
#include "Ellipse.h"

using namespace Gdiplus;
using namespace std;
using namespace rapidxml;


namespace MyFigure 
{
    class Circle : public Ellipse 
    {
    private:
        float r;
    public:
        // Constructor của Circle nhận rootNode và graphics
        Circle(xml_node<>* rootNode, Gdiplus::Graphics& graphics);
        // Phương thức vẽ Circle
        //void drawCircle(Graphics& graphics);
        void draw() override;
        //void checksth();        
    };
}

#endif
