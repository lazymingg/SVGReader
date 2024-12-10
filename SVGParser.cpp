#include "SVGParser.h"

SVGParser::SVGParser(const string &fileName)
{
    ifstream file(fileName, ios::binary); // Đọc dưới dạng nhị phân để đảm bảo đúng cách đọc dữ liệu
    if (!file)
    {
        cerr << "Cannot open file: " << fileName << endl;
        return;
    }

    // Xác định độ dài file
    file.seekg(0, ios::end);
    std::streamsize length = file.tellg();
    if (length == -1)
    {
        cerr << "Failed to get file length." << endl;
        return;
    }

    // Đặt lại cờ và đưa con trỏ về đầu file
    file.seekg(0, ios::beg);

    // Tạo buffer và đảm bảo null-terminated string
    buffer = new char[length + 1];

    // Đọc file vào buffer
    file.read(buffer, length);
    if (!file)
    {
        cerr << "Error while reading file." << endl;
        delete[] buffer;
        return;
    }

    buffer[length] = '\0'; // Đảm bảo kết thúc chuỗi bằng null terminator

    file.close();

    // Hiển thị thông tin đã đọc
    cout << "Read " << length << " characters\n";
    cout << buffer << endl;

    // Tạo đối tượng tài liệu XML
    this->doc.parse<0>(buffer);

    // Xóa buffer để giải phóng bộ nhớ
    // delete[] buffer;

    // Truy cập nút gốc (root)
    this->root_node = doc.first_node("svg");
    if (!root_node)
    {
        cerr << "No root node found." << endl;
        return;
    }
}
SVGParser::~SVGParser()
{
    if (buffer)
    {
        delete[] buffer;
    }
}

xml_node<> *SVGParser::getRootNodeName(string nodeName)
{
    xml_node<> *tempNode;
    tempNode = root_node->first_node(nodeName.c_str());
    if (tempNode)
    {
        return tempNode;
    }
    return nullptr;
}

xml_node<> *SVGParser::getRootNode()
{
    return root_node;
}

void printNode(xml_node<> *node, int depth = 0)
{
    // In ra tên node với độ thụt lề theo chiều sâu
    cout << std::string(depth * 2, ' ') << "Ten nut: " << node->name() << std::endl;

    // In ra tất cả thuộc tính của node
    for (xml_attribute<> *attr = node->first_attribute(); attr; attr = attr->next_attribute())
    {
        cout << std::string(depth * 2 + 2, ' ') << "Thuoc tinh: " << attr->name() << " = " << attr->value() << std::endl;
    }

    // Nếu node là một nhóm (g), duyệt đệ quy qua các node con
    if (std::string(node->name()) == "g")
    {
        for (xml_node<> *child = node->first_node(); child; child = child->next_sibling())
        {
            printNode(child, depth + 1); // Gọi đệ quy với chiều sâu tăng lên
        }
    }
}

void SVGParser::print()
{
    // Duyệt qua tất cả các node ở cấp cao nhất
    for (xml_node<> *node = root_node->first_node(); node; node = node->next_sibling())
    {
        printNode(node); // Gọi hàm đệ quy
    }
}