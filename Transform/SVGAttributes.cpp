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
			cout << "getFillColor" << endl;
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
    std::regex hexColorRegex(R"(^#([0-9A-Fa-f]{6}|[0-9A-Fa-f]{8})$)");
    std::regex rgbaColorRegex(R"(^rgba\((\d{1,3}),\s*(\d{1,3}),\s*(\d{1,3}),\s*([01]|0\.\d+)\)$)");
    std::regex rgbColorRegex(R"(^rgb\((\d{1,3}),\s*(\d{1,3}),\s*(\d{1,3})\)$)");
    std::regex namedColorRegex(R"(^[a-zA-Z]+$)");
    std::regex noneColorRegex(R"(^none$)");

    if (std::regex_match(value, hexColorRegex))
    {
        return hexToColor(value);
    }
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
    else if (std::regex_match(value, namedColorRegex))
    {
        static std::map<std::string, ARGB> namedColors = {
            {"red", 0xFFFF0000},
            {"green", 0xFF008000},
            {"blue", 0xFF0000FF},
            {"black", 0xFF000000},
            {"white", 0xFFFFFFFF},
            {"yellow", 0xFFFFFF00},
            {"aliceBlue", 0xFFF0F8FF},
            {"antiqueWhite", 0xFFFAEBD7},
            {"aqua", 0xFF00FFFF},
            {"aquamarine", 0xFF7FFFD4},
            {"azure", 0xFFF0FFFF},
            {"beige", 0xFFF5F5DC},
            {"bisque", 0xFFFFE4C4},
            {"blanchedAlmond", 0xFFFFEBCD},
            {"blueViolet", 0xFF8A2BE2},
            {"brown", 0xFFA52A2A},
            {"burlyWood", 0xFFDEB887},
            {"cadetBlue", 0xFF5F9EA0},
            {"chartreuse", 0xFF7FFF00},
            {"chocolate", 0xFFD2691E},
            {"coral", 0xFFFF7F50},
            {"cornflowerBlue", 0xFF6495ED},
            {"cornsilk", 0xFFFFF8DC},
            {"crimson", 0xFFDC143C},
            {"cyan", 0xFF00FFFF},
            {"darkBlue", 0xFF00008B},
            {"darkCyan", 0xFF008B8B},
            {"darkGoldenrod", 0xFFB8860B},
            {"darkGray", 0xFFA9A9A9},
            {"darkGreen", 0xFF006400},
            {"darkKhaki", 0xFFBDB76B},
            {"darkMagenta", 0xFF8B008B},
            {"darkOliveGreen", 0xFF556B2F},
            {"darkOrange", 0xFFFF8C00},
            {"darkOrchid", 0xFF9932CC},
            {"darkRed", 0xFF8B0000},
            {"darkSalmon", 0xFFE9967A},
            {"darkSeaGreen", 0xFF8FBC8F},
            {"darkSlateBlue", 0xFF483D8B},
            {"darkSlateGray", 0xFF2F4F4F},
            {"darkTurquoise", 0xFF00CED1},
            {"darkViolet", 0xFF9400D3},
            {"deepPink", 0xFFFF1493},
            {"deepSkyBlue", 0xFF00BFFF},
            {"dimGray", 0xFF696969},
            {"dodgerBlue", 0xFF1E90FF},
            {"firebrick", 0xFFB22222},
            {"floralWhite", 0xFFFFFAF0},
            {"forestGreen", 0xFF228B22},
            {"fuchsia", 0xFFFF00FF},     
            {"gainsboro", 0xFFDCDCDC},
            {"ghostWhite", 0xFFF8F8FF},
            {"gold", 0xFFFFD700},
            {"goldenrod", 0xFFDAA520},
            {"gray", 0xFF808080},
            {"greenYellow", 0xFFADFF2F},
            {"honeydew", 0xFFF0FFF0},
            {"hotPink", 0xFFFF69B4},
            {"indianRed", 0xFFCD5C5C},
            {"indigo", 0xFF4B0082},
            {"ivory", 0xFFFFFFF0},
            {"khaki", 0xFFF0E68C},
            {"lavender", 0xFFE6E6FA},
            {"lavenderBlush", 0xFFFFF0F5},
            {"lawnGreen", 0xFF7CFC00},
            {"lemonChiffon", 0xFFFFFACD},
            {"lightBlue", 0xFFADD8E6},
            {"lightCoral", 0xFFF08080},
            {"lightCyan", 0xFFE0FFFF},
            {"lightGoldenrodYellow", 0xFFFAFAD2},
            {"lightGray", 0xFFD3D3D3},
            {"lightGreen", 0xFF90EE90},
            {"lightPink", 0xFFFFB6C1},
            {"lightSalmon", 0xFFFFA07A},
            {"lightSeaGreen", 0xFF20B2AA},
            {"lightSkyBlue", 0xFF87CEFA},
            {"lightSlateGray", 0xFF778899},
            {"lightSteelBlue", 0xFFB0C4DE},
            {"lightYellow", 0xFFFFFFE0},
            {"lime", 0xFF00FF00},
            {"limeGreen", 0xFF32CD32},
            {"linen", 0xFFFAF0E6},
            {"magenta", 0xFFFF00FF},
            {"maroon", 0xFF800000},
            {"mediumAquamarine", 0xFF66CDAA},
            {"mediumBlue", 0xFF0000CD},
            {"mediumOrchid", 0xFFBA55D3},
            {"mediumPurple", 0xFF9370DB},
            {"mediumSeaGreen", 0xFF3CB371},
            {"mediumSlateBlue", 0xFF7B68EE},
            {"mediumSpringGreen", 0xFF00FA9A},
            {"mediumTurquoise", 0xFF48D1CC},
            {"mediumVioletRed", 0xFFC71585},
            {"midnightBlue", 0xFF191970},
            {"mintCream", 0xFFF5FFFA},
            {"mistyRose", 0xFFFFE4E1},
            {"moccasin", 0xFFFFE4B5},
            {"navajoWhite", 0xFFFFDEAD},
            {"navy", 0xFF000080},
            {"oldLace", 0xFFFDF5E6},
            {"olive", 0xFF808000},
            {"oliveDrab", 0xFF6B8E23},
            {"orange", 0xFFFFA500},
            {"orangeRed", 0xFFFF4500},
            {"orchid", 0xFFDA70D6},
            {"paleGoldenrod", 0xFFEEE8AA},
            {"paleGreen", 0xFF98FB98},
            {"paleTurquoise", 0xFFAFEEEE},
            {"paleVioletRed", 0xFFDB7093},
            {"papayaWhip", 0xFFFFEFD5},
            {"peachPuff", 0xFFFFDAB9},
            {"peru", 0xFFCD853F},
            {"pink", 0xFFFFC0CB},
            {"plum", 0xFFDDA0DD},
            {"powderBlue", 0xFFB0E0E6},
            {"purple", 0xFF800080},
            {"rosyBrown", 0xFFBC8F8F},
            {"royalBlue", 0xFF4169E1},
            {"saddleBrown", 0xFF8B4513},
            {"salmon", 0xFFFA8072},
            {"sandyBrown", 0xFFF4A460},
            {"seaGreen", 0xFF2E8B57},
            {"seaShell", 0xFFFFF5EE},
            {"sienna", 0xFFA0522D},
            {"silver", 0xFFC0C0C0},
            {"skyBlue", 0xFF87CEEB},
            {"slateBlue", 0xFF6A5ACD},
            {"slateGray", 0xFF708090},
            {"snow", 0xFFFFFAFA},
            {"springGreen", 0xFF00FF7F},
            {"steelBlue", 0xFF4682B4},
            {"tan", 0xFFD2B48C},
            {"teal", 0xFF008080},
            {"thistle", 0xFFD8BFD8},
            {"tomato", 0xFFFF6347},
            {"transparent", 0x00FFFFFF},
            {"turquoise", 0xFF40E0D0},
            {"violet", 0xFFEE82EE},
            {"wheat", 0xFFF5DEB3},
            {"whiteSmoke", 0xFFF5F5F5},
            {"yellowGreen", 0xFF9ACD32}
        };

        auto it = namedColors.find(value);
        if (it != namedColors.end())
        {
            return Gdiplus::Color(it->second);
        }
    }
    else if (std::regex_match(value, noneColorRegex))
    {
        return Gdiplus::Color(0, 0, 0, 0); // Fully transparent color
    }

    return Gdiplus::Color(0, 0, 0, 0); // Default to black if no match
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
	return color;
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
}

Stroke::Stroke(string value)
{
	color = getColor(value);
	cout << "red" << color.GetR() << endl;
	cout << "green" << color.GetG() << endl;
	cout << "blue" << color.GetB() << endl;
}

Gdiplus::Color Stroke::getStroke()
{
	return color;
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
	return width;
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
	return value;
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

FillOpacity::FillOpacity(const std::string &getValue)
{
	// Default fill opacity
	value = 1.0f;

	// Regex patterns
	std::regex percentageRegex(R"(^([0-9]+)%$)");	   // Match percentage (e.g., "50%")
	std::regex decimalRegex(R"(^([0-9]*\.?[0-9]+)$)"); // Match decimal (e.g., "0.5", "1.0")
	std::smatch match;

	// Check for percentage
	if (std::regex_match(getValue, match, percentageRegex))
	{
		value = std::stof(match[1].str()) / 100.0f; // Extract and convert percentage
	}
	// Check for decimal
	else if (std::regex_match(getValue, match, decimalRegex))
	{
		value = std::stof(match[1].str()); // Convert to float directly
	}
	else
	{
		value = 1.0f; // Default fill-opacity
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

	// Regex patterns
	std::regex percentageRegex(R"(^([0-9]+)%$)");	   // Match percentage (e.g., "50%")
	std::regex decimalRegex(R"(^([0-9]*\.?[0-9]+)$)"); // Match decimal (e.g., "0.5", "1.0")
	std::smatch match;

	// Check for percentage
	if (std::regex_match(getValue, match, percentageRegex))
	{
		value = std::stof(match[1].str()) / 100.0f; // Extract and convert percentage
	}
	// Check for decimal
	else if (std::regex_match(getValue, match, decimalRegex))
	{
		value = std::stof(match[1].str()); // Convert to float directly
	}
	else
	{
		value = 1.0f; // Default stroke-opacity
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
Attribute *Transform::clone()
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