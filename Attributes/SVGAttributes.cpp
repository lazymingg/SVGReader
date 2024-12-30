#include "SVGAttributes.h"

SVGAttributes::SVGAttributes()
{

}

SVGAttributes::SVGAttributes(xml_node<> *shapeNode)
{
	if (shapeNode == nullptr)
	{
		return;
	}
    for (xml_attribute<> *attr = shapeNode->first_attribute(); attr; attr = attr->next_attribute())
    {
		// get instance of attribute factory
		AttributeFactory *factory = AttributeFactory::getInstance();
        std::string name = attr->name();
        std::string value = attr->value();
		Attribute *attribute = factory->createAttribute(name, value);
		if (attribute == nullptr)
		{
			cout << "invalid attribute: " << name << endl;
		}
		else
		{
			// add attribute to map
			Attributes[name] = attribute;
		}
	}
}


SVGAttributes::SVGAttributes(const SVGAttributes &attributes)
{
	for (auto &attr : attributes.Attributes)
	{
		Attributes[attr.first] = attr.second->clone();
	}
}

SVGAttributes &SVGAttributes::operator=(const SVGAttributes &attributes)
{
	if (this == &attributes)
	{
		return *this;
	}
	for (auto &attr : Attributes)
	{
		delete attr.second;
	}
	Attributes.clear();
	for (auto &attr : attributes.Attributes)
	{
		Attributes[attr.first] = attr.second->clone();
	}
	return *this;
}

Attribute *SVGAttributes::getAttributes(std::string name)
{
	// get instance of attribute factory
	AttributeFactory *factory = AttributeFactory::getInstance();
	auto it = Attributes.find(name);
	if (it != Attributes.end())
	{
		return it->second;
	}
	// return an object with default value
	return factory->createAttribute(name);
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
	registerAttribute("x", new X());
	registerAttribute("y", new Y());
	registerAttribute("x1", new X1());
	registerAttribute("x2", new X2());
	registerAttribute("y1", new Y1());
	registerAttribute("y2", new Y2());
	registerAttribute("id", new Id());
	registerAttribute("offset", new OffSet());
	registerAttribute("stop-color", new StopColor());
	registerAttribute("font-weight", new FontWeight());
}

AttributeFactory *AttributeFactory::getInstance()
{
	if (instance == nullptr)
	{
		instance = new AttributeFactory();
	}
	return instance;
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
