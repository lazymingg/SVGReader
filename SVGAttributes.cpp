#include "SVGAttributes.h"

SVGAttributes::SVGAttributes(xml_node<> *shapeNode)
{
	for (xml_attribute<> *attr = shapeNode->first_attribute(); attr; attr = attr->next_attribute())
	{
		std::string name = attr->name();
		std::string value = attr->value();
		//fill strokewith stroke fill-opacity stroke-opacity stroke-width stroke color opacity transform
		if (name == "fill")
		{
			Attributes["fill"] = new Fill(value);
		}
		else if (name == "stroke")
		{
			Attributes["stroke"] = new Stroke(value);
		}
		else if (name == "stroke-width")
		{
			Attributes["stroke-width"] = new StrokeWidth(value);
		}
		else if (name == "fill-opacity")
		{
			Attributes["fill-opacity"] = new FillOpacity(value);
		}
		else if (name == "stroke-opacity")
		{
			Attributes["stroke-opacity"] = new StrokeOpacity(value);
		}
		else if (name == "stroke-width")
		{
			Attributes["stroke-width"] = new StrokeWidth(value);
		}
		else if (name == "stroke")
		{
			Attributes["stroke"] = new Stroke(value);
		}
		else if (name == "opacity")
		{
			Attributes["opacity"] = new Opacity(value);
		}
		else if (name == "transform")
		{
			Attributes["transform"] = new Transform(value);	
		}
	}
}
