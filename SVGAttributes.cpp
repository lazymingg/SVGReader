#include "SVGAttributes.h"

SVGAttributes::SVGAttributes(xml_node<> *shapeNode)
{
	for (xml_attribute<> *attr = shapeNode->first_attribute(); attr; attr = attr->next_attribute())
	{
		std::string name = attr->name();
		std::string value = attr->value();

		if (name == "stroke")
		{
			Attributes["stroke"] = new Stroke(value);
		}
		else if (name == "stroke-width")
		{
			Attributes["stroke-width"] = new StrokeWidth(value);
		}
		else if (name == "fill")
		{
			Attributes["fill"] = new Fill(value);
		}
		else if (name == "fill-opacity")
		{
			Attributes["fill-opacity"] = new FillOpacity(value);
		}
		else if (name == "stroke-opacity")
		{
			Attributes["stroke-opacity"] = new StrokeOpacity(value);
		}
		else if (name == "opacity")
		{
			Attributes["opacity"] = new Ocopacity(value);
		}
		else if (name == "text")
		{
			Attributes["text"] = new Text(value);
		}
		else if (name == "transform")
		{
			Attributes["transform"] = new Transform(value);
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

float SVGAttributes::getStrokeWidth()
{
	auto it = Attributes.find("stroke-width");
	if (it != Attributes.end())
	{
		StrokeWidth *strokeWidth = dynamic_cast<StrokeWidth *>(it->second);

		if (strokeWidth != nullptr)
		{
			return strokeWidth->getStrokeWidth();
		}
		else
		{
			std::cerr << "Error: stroke-width attribute is not of type StrokeWidth." << std::endl;
			return 0.0f;
		}
	}
	return 0.0f;
}

Gdiplus::Color SVGAttributes::getStrokeColor()
{
	auto it = Attributes.find("stroke");
	if (it != Attributes.end())
	{
		Stroke *stroke = dynamic_cast<Stroke *>(it->second);

		if (stroke != nullptr)
		{
			return stroke->getStroke();
		}
		else
		{
			std::cerr << "Error: stroke attribute is not of type Stroke." << std::endl;
			return Gdiplus::Color();
		}
	}
	// Default stroke color is black
	return Gdiplus::Color();
}

Gdiplus::Color SVGAttributes::getFillColor()
{
	auto it = Attributes.find("fill");
	if (it != Attributes.end())
	{
		Fill *fill = dynamic_cast<Fill *>(it->second);

		if (fill != nullptr)
		{
			return fill->getFill();
		}
		else
		{
			std::cerr << "Error: fill attribute is not of type Fill." << std::endl;
			return Gdiplus::Color();
		}
	}
	// Default fill color is black
	return Gdiplus::Color();
}

float SVGAttributes::getFillOpacity()
{
	auto it = Attributes.find("fill-opacity");
	if (it != Attributes.end())
	{
		FillOpacity *fillOpacity = dynamic_cast<FillOpacity *>(it->second);

		if (fillOpacity != nullptr)
		{
			return fillOpacity->getFillOpacity();
		}
		else
		{
			std::cerr << "Error: fill-opacity attribute is not of type FillOpacity." << std::endl;
			return 1.0f;
		}
	}
	// Default fill opacity is 1.0
	return 1.0f;
}

float SVGAttributes::getStrokeOpacity()
{
	auto it = Attributes.find("stroke-opacity");
	if (it != Attributes.end())
	{
		StrokeOpacity *strokeOpacity = dynamic_cast<StrokeOpacity *>(it->second);

		if (strokeOpacity != nullptr)
		{
			return strokeOpacity->getStrokeOpacity();
		}
		else
		{
			std::cerr << "Error: stroke-opacity attribute is not of type StrokeOpacity." << std::endl;
			return 1.0f;
		}
	}
	// Default stroke opacity is 1.0
	return 1.0f;
}

float SVGAttributes::getOpacity()
{
	auto it = Attributes.find("opacity");
	if (it != Attributes.end())
	{
		Ocopacity *opacity = dynamic_cast<Ocopacity *>(it->second);

		if (opacity != nullptr)
		{
			return opacity->getOcopacity();
		}
		else
		{
			std::cerr << "Error: opacity attribute is not of type Ocopacity." << std::endl;
			return 1.0f;
		}
	}
	// Default opacity is 1.0
	return 1.0f;
}

std::string SVGAttributes::getText()
{
	auto it = Attributes.find("text");
	if (it != Attributes.end())
	{
		Text *text = dynamic_cast<Text *>(it->second);

		if (text != nullptr)
		{
			return text->getText();
		}
		else
		{
			std::cerr << "Error: text attribute is not of type Text." << std::endl;
			return "";
		}
	}
	// Default text is empty
	return "";
}

Transform SVGAttributes::getTransform()
{
	auto it = Attributes.find("transform");
	if (it != Attributes.end())
	{
		Transform *transform = dynamic_cast<Transform *>(it->second);

		if (transform != nullptr)
		{
			return *transform;
		}
		else
		{
			std::cerr << "Error: transform attribute is not of type Transform." << std::endl;
			return Transform();
		}
	}
	// Default transform is identity matrix
	return Transform();
}

SVGAttributes::~SVGAttributes()
{
	for (auto &attr : Attributes)
	{
		delete attr.second;
	}
}

Attribute *Fill::clone()
{
	return new Fill(*this);
}

Attribute *Stroke::clone()
{
	return new Stroke(*this);
}

Attribute *StrokeWidth::clone()
{
	return new StrokeWidth(*this);
}

Attribute *Ocopacity::clone()
{
	return new Ocopacity(*this);
}

Text::Text()
{
	text = "";
}

Text::Text(string text)
{
	text = text;
}

string Text::getText()
{
    return text;
}

Attribute *Text::clone()
{
	return new Text(*this);
}

Text::~Text()
{
}

FillOpacity::FillOpacity()
{
	value = 1.0f;
}

FillOpacity::FillOpacity(string getValue)
{
	// Default fill opacity
	value = 1.0f;

	// Regular expressions to match different formats of fill-opacity
	std::regex numberRegex(R"(fill-opacity\s*=\s*\"([0-9]*\.?[0-9]+)\")");
	std::regex percentageRegex(R"(fill-opacity\s*=\s*\"([0-9]+)%\")");
	std::regex styleRegex(R"(style\s*=\s*\"[^\"]*fill-opacity\s*:\s*([0-9]*\.?[0-9]+)\s*;\")");

	std::smatch match;

	// Check for fill-opacity as a number
	if (std::regex_search(getValue, match, numberRegex))
	{
		value = std::stof(match[1].str());
	}

	// Check for fill-opacity as a percentage
	if (std::regex_search(getValue, match, percentageRegex))
	{
		value = std::stof(match[1].str()) / 100.0f;
	}

	// Check for fill-opacity as a CSS property
	if (std::regex_search(getValue, match, styleRegex))
	{
		value = std::stof(match[1].str());
	}
}

float FillOpacity::getFillOpacity()
{
	return value;
}

Attribute *FillOpacity::clone()
{
	return new FillOpacity(*this);
}

FillOpacity::~FillOpacity()
{
}

StrokeOpacity::StrokeOpacity()
{
	value = 1.0f;
}

StrokeOpacity::StrokeOpacity(string getValue)
{
	// Default stroke opacity
	value = 1.0f;

	// Regular expressions to match different formats of stroke-opacity
	std::regex numberRegex(R"(stroke-opacity\s*=\s*\"([0-9]*\.?[0-9]+)\")");
	std::regex percentageRegex(R"(stroke-opacity\s*=\s*\"([0-9]+)%\")");
	std::regex styleRegex(R"(style\s*=\s*\"[^\"]*stroke-opacity\s*:\s*([0-9]*\.?[0-9]+)\s*;\")");

	std::smatch match;

	// Check for stroke-opacity as a number
	if (std::regex_search(getValue, match, numberRegex))
	{
		value = std::stof(match[1].str());
	}

	// Check for stroke-opacity as a percentage
	if (std::regex_search(getValue, match, percentageRegex))
	{
		value = std::stof(match[1].str()) / 100.0f;
	}

	// Check for valueoke-opacity as a CSS property
	if (std::regex_search(getValue, match, styleRegex))
	{
		value = std::stof(match[1].str());
	}
}

float StrokeOpacity::getStrokeOpacity()
{
    return value;
}

Attribute *StrokeOpacity::clone()
{
	return new StrokeOpacity(*this);
}

StrokeOpacity::~StrokeOpacity()
{
}

Attribute *Transform::clone()
{
	return new Transform(*this);
}
