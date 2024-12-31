#include "formatUnit.h"

double formatUnit(string &s)
{ // Tìm vị trí của ký tự chữ cái đầu tiên
    size_t idx = 0;
    while (idx < s.length() && !isalpha(s[idx])) {
        idx++;
    }
    // Nếu không có đơn vị, trả về giá trị mặc định 1
    if (idx == s.length()) return 1;
    // Lấy phần đơn vị và xóa khỏi chuỗi ban đầu
    std::string unit = s.substr(idx);
    s = s.substr(0, idx); // Chỉ giữ phần số
    cout << "unit: " << unit << endl;
    if(unit == "in")
    {
        return 96;
    }
    else if(unit == "cm")
    {
        
        return 96.0 / 2.54;
    }
    else if(unit == "mm")
    {
        return 96.0 / 25.4;
    }
    else if(unit == "pt")
    {
        double num = 96.0 / 72;
        return num;
    }
    else if(unit == "pc")
    {
        return 16;
    }
    return 1;
}