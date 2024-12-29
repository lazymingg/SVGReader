#include "Attribute.h"
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
    else if (std::regex_match(value, noneColorRegex))
    {
        return Gdiplus::Color(0, 0, 0, 0);
    }
    else if (std::regex_match(value, namedColorRegex))
    {
        static std::map<std::string, Gdiplus::ARGB> namedColors = {
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
    

    return Gdiplus::Color(0, 0, 0, 0); 
}