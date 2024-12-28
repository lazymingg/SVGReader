#ifndef _DEFS_TAG_H_
#define _DEFS_TAG_H_

#include <iostream>
#include <string>
#include "../../extendLib/rapid_xml/rapidxml.hpp"
#include "../../Transform/SVGAttributes.h"

//interface for all tag in defs
class DefsTag
{
    protected:
        rapidxml::xml_node<> *shapeNode;
        SVGAttributes attributes;
    public:
        DefsTag(rapidxml::xml_node<> *constructorData) : shapeNode(constructorData) , attributes(constructorData) {}
        virtual DefsTag* clone() = 0;
        virtual DefsTag* clone(rapidxml::xml_node<> *constructorData) = 0;
        virtual ~DefsTag() {}
};


#endif 