#ifndef GROUP_H
#define GROUP_H

#include <vector>
#include "Figure.h"
#include "Shape.h"

namespace MyFigure
{
    class Group : public Figure
    {
    private:
        vector<Figure *> children;

    public:
        // Constructor
        Group(xml_node<> *root_node, Gdiplus::Graphics &graphics);
        void addChild(Figure *child);

        void draw() override;
        ~Group();
    };
}
#endif