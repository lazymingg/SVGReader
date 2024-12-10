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

void SVGAttributes::printAttributes()
{
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

// Hàm chuyển đổi màu HEX sang Gdiplus::Color
Gdiplus::Color hexToColor(const std::string &hex)
{
    int r, g, b, a = 255; // Mặc định alpha = 255 (hoàn toàn không trong suốt)

    // Kiểm tra chuỗi HEX có đúng định dạng không (có dấu # và đúng độ dài)
    if (hex[0] == '#' && (hex.length() == 7 || hex.length() == 9))
    {
        // Chuyển đổi từ HEX sang các giá trị RGB
        sscanf(hex.c_str() + 1, "%2x%2x%2x", &r, &g, &b);

        // Nếu có alpha, tách alpha từ 2 ký tự cuối
        if (hex.length() == 9)
        {
            sscanf(hex.c_str() + 7, "%2x", &a);
        }

        // Trả về màu từ ARGB
        return Gdiplus::Color(a, r, g, b);
    }
    else
    {
        // Nếu chuỗi không hợp lệ, trả về màu mặc định (đen)
        return Gdiplus::Color::Black;
    }
}

// Hàm lấy màu từ chuỗi
Gdiplus::Color getColor(const std::string &value)
{
    // Regex kiểm tra các định dạng màu
    std::regex hexColorRegex(R"(^#([0-9A-Fa-f]{6}|[0-9A-Fa-f]{8})$)");
    std::regex rgbaColorRegex(R"(^rgba\((\d{1,3}),\s*(\d{1,3}),\s*(\d{1,3}),\s*([01]|0\.\d+)\)$)");
    std::regex rgbColorRegex(R"(^rgb\((\d{1,3}),\s*(\d{1,3}),\s*(\d{1,3})\)$)");
    std::regex namedColorRegex(R"(^[a-zA-Z]+$)");
    std::regex noneColorRegex(R"(^none$)");

    // Nếu là màu HEX
    if (std::regex_match(value, hexColorRegex))
    {
        return hexToColor(value);
    }
    // Nếu là màu RGBA
    else if (std::regex_match(value, rgbaColorRegex))
    {
        int red, green, blue;
        float alpha;

        std::smatch match;
        if (std::regex_search(value, match, rgbaColorRegex))
        {
            red = std::stoi(match[1].str());
            green = std::stoi(match[2].str());
            blue = std::stoi(match[3].str());
            alpha = std::stof(match[4].str());

            int alphaInt = static_cast<int>(alpha * 255);

            return Gdiplus::Color(alphaInt, red, green, blue);
        }
    }
    // Nếu là màu RGB
    else if (std::regex_match(value, rgbColorRegex))
    {
        int red, green, blue;

        std::smatch match;
        if (std::regex_search(value, match, rgbColorRegex))
        {
            red = std::stoi(match[1].str());
            green = std::stoi(match[2].str());
            blue = std::stoi(match[3].str());

            return Gdiplus::Color(255, red, green, blue);
        }
    }
    // Nếu là tên màu
    // else if (std::regex_match(value, namedColorRegex))
    // {
    //     static std::map<std::string, Gdiplus::Color> namedColors = {
    //         {"red", Gdiplus::Color::Red},
    //         {"green", Gdiplus::Color::Green},
    //         {"blue", Gdiplus::Color::Blue},
    //         {"black", Gdiplus::Color::Black},
    //         {"white", Gdiplus::Color::White},
    //         {"yellow", Gdiplus::Color::Yellow},
    //         // Thêm các tên màu khác nếu cần
    //     };

    //     auto it = namedColors.find(value);
    //     if (it != namedColors.end())
    //     {
    //         return it->second;
    //     }
    // }
    // Nếu là "none"
    else if (std::regex_match(value, noneColorRegex))
    {
        return Gdiplus::Color(0, 0, 0, 0); // Màu trong suốt hoàn toàn
    }

    // Nếu không khớp với định dạng nào, trả về màu đen
    return Gdiplus::Color::Black;
}

Fill::Fill()
{
}

Fill::Fill(string value)
{
	color = getColor(value);
}

Gdiplus::Color Fill::getFill()
{
    return Gdiplus::Color();
}

Attribute *Fill::clone()
{
	return new Fill(*this);
}

Fill::~Fill()
{
}

Stroke::Stroke()
{
	color = Gdiplus::Color::Black;
}

Stroke::Stroke(string value)
{
	color = getColor(value);
}

Gdiplus::Color Stroke::getStroke()
{
    return Gdiplus::Color();
}

Attribute *Stroke::clone()
{
	return new Stroke(*this);
}

Stroke::~Stroke()
{
}

StrokeWidth::StrokeWidth()
{
	width = 1.0f;
}

StrokeWidth::StrokeWidth(string width)
{
	StrokeWidth::width = std::stof(width);
}

float StrokeWidth::getStrokeWidth()
{
    return 0.0f;
}

Attribute *StrokeWidth::clone()
{
	return new StrokeWidth(*this);
}

StrokeWidth::~StrokeWidth()
{
}

Ocopacity::Ocopacity()
{
}

Ocopacity::Ocopacity(string value)
{
	// Default opacity
	Ocopacity::value = 1.0f;

	// Regular expressions to match different formats of opacity
	std::regex numberRegex(R"(opacity\s*=\s*\"([0-9]*\.?[0-9]+)\")");
	std::regex percentageRegex(R"(opacity\s*=\s*\"([0-9]+)%\")");
	
	std::smatch match;

	// Check for opacity as a number
	if (std::regex_search(value, match, numberRegex))
	{
		value = std::stof(match[1].str());
	}

	// Check for opacity as a percentage
	if (std::regex_search(value, match, percentageRegex))
	{
		value = std::stof(match[1].str()) / 100.0f;
	}
}

float Ocopacity::getOcopacity()
{
    return 0.0f;
}

Attribute *Ocopacity::clone()
{
	return new Ocopacity(*this);
}

Ocopacity::~Ocopacity()
{
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

Transform::Transform()
{
    stragetry.push_back(new Translate("translate(0,0)"));
}

Transform::Transform(string str)
{   
    vector<string> tokens;
    int len = str.length();

    string get = "";

    for (int i = 0; i <= len; i++)
    {
        if ((str[i] == ' ' && str[i - 1] == ')') || i == len)
        {
            tokens.push_back(get);
            get = "";
        }
        else
            get += str[i];
    }
    
    for (int i = 0; i < tokens.size(); i++)
    cout << tokens[i] << '\n';

    for (auto &token : tokens)
    {
        if (token.find("translate") != string::npos)
        {
            stragetry.push_back(new Translate(token));
        }
        else if (token.find("scale") != string::npos)
        {
            stragetry.push_back(new Scale(token));
        }
        else if (token.find("rotate") != string::npos)
        {
            stragetry.push_back(new Rotate(token));
        }
    }
}

Transform::Transform(const Transform &transform)
{
    for (auto &a : transform.stragetry)
    {
        this->stragetry.push_back(a->clone());
    }
}

void Transform::transform(Gdiplus::Matrix &matrix)
{
    for (auto &stragetry : stragetry)
    {
        stragetry->transform(matrix);
    }
}
Transform &Transform::operator=(const Transform &transform)
{
    if (this == &transform)
    {
        return *this;
    }

    for (auto &stragetry : stragetry)
    {
        delete stragetry;
    }
    stragetry.clear();

    for (auto &stragetry : transform.stragetry)
    {
        this->stragetry.push_back(stragetry->clone());
    }

    return *this;
}

void Transform::addStragetry(Transform transform)
{
    for (auto &stragetry : transform.stragetry)
    {
        this->stragetry.push_back(stragetry->clone());
    }
}
Attribute* Transform::clone()
{
    return new Transform(*this);
}

Transform::~Transform()
{
    for (auto &stragetry : stragetry)
    {
        delete stragetry;
    }
    stragetry.clear();
}