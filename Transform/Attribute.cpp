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
		cout << "rgbColorRegex" << endl;
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