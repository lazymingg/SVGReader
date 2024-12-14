#include "SVGAttributes.h"

SVGAttributes::SVGAttributes(xml_node<> *shapeNode)
{
    for (xml_attribute<> *attr = shapeNode->first_attribute(); attr; attr = attr->next_attribute())
    {
        std::string name = attr->name();
        std::string value = attr->value();
		Attribute *attribute = this->factory.createAttribute(name, value);
		if (attribute == nullptr)
		{
			cout << "invalid attribute: " << name << endl;
		}
		// add attribute to map
		Attributes[name] = attribute;
    }
}

SVGAttributes::SVGAttributes(const SVGAttributes &attributes)
{
	for (auto &attr : attributes.Attributes)
	{
		Attributes[attr.first] = attr.second->clone();
	}
}


Attribute *SVGAttributes::getAttributes(std::string name)
{
	auto it = Attributes.find(name);
	if (it != Attributes.end())
	{
		return it->second;
	}
	// return an object with default value
	return this->factory.createAttribute(name);
}

void SVGAttributes::mergeAttributes(SVGAttributes &attributes)
{
	for (auto &attr : attributes.Attributes)
	{
		if (Attributes.find(attr.first) == Attributes.end())
		{
			Attributes[attr.first] = attr.second->clone();
		}
		else
		{
			Attributes[attr.first]->mergeData(attr.second);
		}
	}
}

SVGAttributes::~SVGAttributes()
{
	for (auto &attr : Attributes)
	{
		delete attr.second;
	}
}

AttributeFactory::AttributeFactory()
{
	registerAttribute("stroke", new Stroke());
	registerAttribute("stroke-width", new StrokeWidth());
	registerAttribute("fill", new Fill());
	registerAttribute("fill-opacity", new FillOpacity());
	registerAttribute("stroke-opacity", new StrokeOpacity());
	registerAttribute("opacity", new Ocopacity());
	registerAttribute("transform", new Transform());
	registerAttribute("font-size", new FontSize());
	registerAttribute("font-family", new MyFontFamily());
	registerAttribute("font-style", new MyFontStyle());
	registerAttribute("text-anchor", new TextAnchor());
	registerAttribute("dx", new Dx());
	registerAttribute("dy", new Dy());
}

void AttributeFactory::registerAttribute(const std::string &name, Attribute *attribute)
{
	Attributes[name] = attribute;
}

Attribute *AttributeFactory::createAttribute(const std::string &name, const std::string &value)
{
	auto it = Attributes.find(name);
	if (it != Attributes.end())
	{
		return it->second->clone(value);
	}
	return nullptr;
}

Attribute* AttributeFactory::createAttribute(const std::string &name)
{
	auto it = Attributes.find(name);
	if (it != Attributes.end())
	{
		return it->second->clone();
	}
	return nullptr;
}


Attribute *AttributeFactory::getAttribute(const std::string &name)
{
	auto it = Attributes.find(name);
	if (it != Attributes.end())
	{
		return it->second;
	}
	return nullptr;
}

AttributeFactory::~AttributeFactory()
{
	for (auto &attr : Attributes)
	{
		delete attr.second;
	}
}
