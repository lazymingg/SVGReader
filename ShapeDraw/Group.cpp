#include "../ShapeHeader/Group.h"

MyFigure::Group::Group(xml_node<> *root_node, Gdiplus::Graphics &graphics) : Figure(root_node, graphics)
{
    this->shapeNode = root_node;
    for (xml_node<> *node = root_node->first_node(); node; node = node->next_sibling())
    {
        std::string shape = node->name();

        if (shape == "text")
        {
            children.push_back(new MyFigure::Text(node, graphics));
        }
        else if (shape == "rect")
        {
            children.push_back(new MyFigure::Rectangle(node, graphics));
        }
        else if (shape == "line")
        {
            children.push_back(new MyFigure::Line(node, graphics));
        }
        else if (shape == "polygon")
        {
            children.push_back(new MyFigure::Polygon(node, graphics));
        }
        else if (shape == "polyline")
        {
            children.push_back(new MyFigure::Polyline(node, graphics));
        }
        else if (shape == "ellipse")
        {
            children.push_back(new MyFigure::Ellipse(node, graphics));
        }
        else if (shape == "circle")
        {
            children.push_back(new MyFigure::Circle(node, graphics));
        }
        else if (shape == "path")
        {
            children.push_back(new MyFigure::Path(node, graphics));
        }
        else if (shape == "g")
        {
            children.push_back(new Group(node, graphics));
        }
    }
}

void MyFigure::Group::addChild(Figure *child)
{
    children.push_back(child);
}

void MyFigure::Group::draw()
{
    for (auto &child : children)
    {
        child->getAttributes().mergeAttributes(attributes);
    }
<<<<<<< HEAD

=======
>>>>>>> 8d8cdce29b603f30ffd7b7702dac7ef09e54a80a
    for (auto &child : children)
    {
        child->draw();
    }
}

void MyFigure::Group::applyTransform()
{
}

MyFigure::Group::~Group()
{
    for (auto &child : children)
    {
        delete child;
    }
    children.clear();
}
