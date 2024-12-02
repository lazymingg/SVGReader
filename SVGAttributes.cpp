#include "SVGAttributes.h"

// Constructor
SVGAttributes::SVGAttributes(xml_node<> *shapeNode) : fill("none"),
													  stroke("none"),
													  strokeWidth(1.0f),
													  opacity(1.0f),
													  fillOpacity(1.0f),
													  strokeOpacity(0.0f),
													  strokeLinecap("butt"),
													  strokeLinejoin("miter"),
													  strokeDasharray(""),
													  text(""),
													  fillColor(Gdiplus::Color(0, 0, 0, 0)),
													  strokeColor(Gdiplus::Color(0, 0, 0, 0))
{
// default if not define stroke we will not draw stroke
// default if not define fill browser will fill with black color
// default fill opacity is 1
// default stroke opacity is 0
// default stroke width is 1
// default opacity is 1
// default stroke linecap is butt
// default stroke linejoin is miter
// default stroke dasharray is empty
// default transform is empty
// default text is empty

	xml_attribute<> *attribute = shapeNode->first_attribute();
	while (attribute != NULL)
	{
		std::string name = attribute->name();
		std::string value = attribute->value();

		if (name == "stroke-opacity")
		{
			setStrokeOpacity(stof(value));
		}
		else if (name == "stroke-width")
		{
			setStrokeWidth(stof(value));
		}
		else if (name == "opacity")
		{
			setOpacity(stof(value));
		}
		else if (name == "fill-opacity")
		{
			setFillOpacity(stof(value));
		}
		else if (name == "stroke-linecap")
		{
			setStrokeLinecap(value);
		}
		else if (name == "stroke-linejoin")
		{
			setStrokeLinejoin(value);
		}
		else if (name == "transform")
		{
			cout << "test" << endl;
			transform = Transform(value);
		}
		else if (name == "stroke-dasharray")
		{
			setStrokeDasharray(value);
		}
		attribute = attribute->next_attribute();
	}

	//loop through all the attributes again to determine is fill or stroke need to be drawn
	attribute = shapeNode->first_attribute();
	while (attribute != NULL)
	{
		std::cout << "flag" << std::endl;
		std::string name = attribute->name();
		std::string value = attribute->value();
		//if no stroke we will not draw stroke default stroke opacity is 0
		if (name == "stroke")
		{
			if (value != "none")
			{
				setStrokeColor(value);
				setStroke(value);
				if (getStrokeOpacity() == 0)
				{
					std::cout << "draw stroke with opacity 0" << std::endl;
					setStrokeOpacity(1.0f);
				}
			}
		}
		else if (name == "fill")
		{
			setFillColor(value);
			setFill(value);
			if (value == "none")
			{
				setFillOpacity(0.0f);
			}
		}
		attribute = attribute->next_attribute();
	}

	// Handle text content separately
	if (shapeNode->value() && strlen(shapeNode->value()) > 0)
	{
		setText(shapeNode->value());
	}
}

// Getters and setters
void SVGAttributes::setFill(const std::string &color) { fill = color; }
std::string SVGAttributes::getFill() const { return fill; }

void SVGAttributes::setStroke(const std::string &color) { stroke = color; }
std::string SVGAttributes::getStroke() const { return stroke; }

void SVGAttributes::setStrokeWidth(float width) { strokeWidth = width; }
float SVGAttributes::getStrokeWidth() const { return strokeWidth; }

void SVGAttributes::setOpacity(float value) { opacity = value; }
float SVGAttributes::getOpacity() const { return opacity; }

void SVGAttributes::setFillOpacity(float value) { fillOpacity = value; }
float SVGAttributes::getFillOpacity() const { return fillOpacity; }

void SVGAttributes::setStrokeOpacity(float value) { strokeOpacity = value; }
float SVGAttributes::getStrokeOpacity() const { return strokeOpacity; }

void SVGAttributes::setStrokeLinecap(const std::string &cap) { strokeLinecap = cap; }
std::string SVGAttributes::getStrokeLinecap() const { return strokeLinecap; }

void SVGAttributes::setStrokeLinejoin(const std::string &join) { strokeLinejoin = join; }
std::string SVGAttributes::getStrokeLinejoin() const { return strokeLinejoin; }

void SVGAttributes::setStrokeDasharray(const std::string &dash) { strokeDasharray = dash; }
std::string SVGAttributes::getStrokeDasharray() const { return strokeDasharray; }

Transform SVGAttributes::getTransform()
{
	return transform;
}

void SVGAttributes::setText(std::string tex) { text = tex; };
std::string SVGAttributes::getText() const { return text; };

// Print attributes
void SVGAttributes::printAttributes() const
{
	std::cout << "Fill: " << fill << "\n"
			  << "Stroke: " << stroke << "\n"
			  << "Stroke Width: " << strokeWidth << "\n"
			  << "Opacity: " << opacity << "\n"
			  << "Fill Opacity: " << fillOpacity << "\n"
			  << "Stroke Opacity: " << strokeOpacity << "\n"
			  << "Stroke Linecap: " << strokeLinecap << "\n"
			  << "Stroke Linejoin: " << strokeLinejoin << "\n"
			  << "Stroke Dasharray: " << strokeDasharray << "\n"
			  << "Text: " << text << "\n";
}

// string format = "rgb(255, 0, 0)";
void SVGAttributes::setFillColor(std::string str)
{
	if (str == "none")
	{
		fillColor = Gdiplus::Color(0, 0, 0, 0);
		return;
	}
	if (str[0] == '#')
	{
		int r = std::stoi(str.substr(1, 2), nullptr, 16);
		int g = std::stoi(str.substr(3, 2), nullptr, 16);
		int b = std::stoi(str.substr(5, 2), nullptr, 16);
		fillColor = Gdiplus::Color(255, r, g, b);
		return;
	}
	if (str.substr(0, 3) == "rgb")
	{
		int r, g, b;
		sscanf_s(str.c_str(), "rgb(%d, %d, %d)", &r, &g, &b);
		fillColor = Gdiplus::Color(255, r, g, b);
		return;
	}
	if (str.substr(0, 4) == "rgba")
	{
		int r, g, b, a;
		sscanf_s(str.c_str(), "rgba(%d, %d, %d, %d)", &r, &g, &b, &a);
		fillColor = Gdiplus::Color(a, r, g, b);
		return;
	}
}
Gdiplus::Color SVGAttributes::getFillColor() const
{
	return fillColor;
}

void SVGAttributes::setStrokeColor(std::string str)
{
	if (str == "none")
	{
		strokeColor = Gdiplus::Color(0, 0, 0, 0);
		return;
	}
	if (str[0] == '#')
	{
		int r = std::stoi(str.substr(1, 2), nullptr, 16);
		int g = std::stoi(str.substr(3, 2), nullptr, 16);
		int b = std::stoi(str.substr(5, 2), nullptr, 16);
		strokeColor = Gdiplus::Color(255, r, g, b);
		return;
	}
	if (str.substr(0, 3) == "rgb")
	{
		int r, g, b;
		sscanf_s(str.c_str(), "rgb(%d, %d, %d)", &r, &g, &b);
		strokeColor = Gdiplus::Color(255, r, g, b);
		return;
	}
	if (str.substr(0, 4) == "rgba")
	{
		int r, g, b, a;
		sscanf_s(str.c_str(), "rgba(%d, %d, %d, %d)", &r, &g, &b, &a);
		strokeColor = Gdiplus::Color(a, r, g, b);
		return;
	}
}

Gdiplus::Color SVGAttributes::getStrokeColor() const
{
	return strokeColor;
}
