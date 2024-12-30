#include "FigureDraw.h"
#include <iostream>

//FigureDraw::FigureDraw(Graphics &graphics) : graphics(graphics) {}
FigureDraw::FigureDraw(Graphics &graphics):graphics(graphics), svgWidth(0), svgHeight(0), svgViewBox("") {}

std::array<double, 4> FigureDraw::parseViewBox(const std::string &viewBoxStr)
{
    std::array<double, 4> viewBox = {0, 0, 0, 0}; // Giá trị mặc định là 0
    std::stringstream ss(viewBoxStr);
    for (int i = 0; i < 4; ++i)
    {
        std::string value;
        if (std::getline(ss, value, ' '))
        {
            try
            {
                viewBox[i] = std::stod(value); // Chuyển đổi string thành double
            }
            catch (const std::invalid_argument &)
            {
                std::cerr << "Invalid value in viewBox string: " << value << std::endl;
                viewBox[i] = 0; // Gán giá trị mặc định nếu không hợp lệ
            }
            catch (const std::out_of_range &)
            {
                std::cerr << "Value out of range in viewBox string: " << value << std::endl;
                viewBox[i] = 0; // Gán giá trị mặc định nếu vượt quá giới hạn
            }
        }
    }
    return viewBox;
}
FigureDraw::~FigureDraw()
{
    for (Figure *figure : figures)
    {
        delete figure;
    }
    figures.clear();
}

void FigureDraw::loadSVGFile(const std::string &filename)
{
    // bool isHead = false;
    SVGParser parser(filename);
    parser.print();
    xml_node<> *rootNode = parser.getRootNode();

    //
    if (rootNode->first_attribute("width"))
    {
        svgWidth = std::stod(rootNode->first_attribute("width")->value());
    }
    else
    {
        svgWidth = 300; // Giá trị mặc định nếu không tìm thấy
    }

    if (rootNode->first_attribute("height"))
    {
        svgHeight = std::stod(rootNode->first_attribute("height")->value());
    }
    else
    {
        svgHeight = 150; // Giá trị mặc định nếu không tìm thấy
    }

    // Đọc thuộc tính viewBox
    if (rootNode->first_attribute("viewBox"))
    {
        svgViewBox = rootNode->first_attribute("viewBox")->value();
        if (!svgViewBox.empty())
        {
            auto viewBoxValues = parseViewBox(svgViewBox);
            std::cout << "ViewBox: xMin=" << viewBoxValues[0]
                      << ", yMin=" << viewBoxValues[1]
                      << ", width=" << viewBoxValues[2]
                      << ", height=" << viewBoxValues[3] << std::endl;

            // Chỉ cập nhật svgWidth và svgHeight từ viewBox nếu các giá trị này vẫn là 0
            if (svgWidth == 0) svgWidth = viewBoxValues[2]; cout << "SVG Width: " << svgWidth << endl;
            if (svgHeight == 0) svgHeight = viewBoxValues[3]; cout << "SVG Height: " << svgHeight << endl;
        }
    }

    std::cout << "SVG Dimensions: Width=" << svgWidth << ", Height=" << svgHeight << "\n";
//

    for (xml_node<> *node = rootNode->first_node(); node; node = node->next_sibling())
    {
        std::string element = node->name();

        if (element == "text")
        {
            figures.push_back(new MyFigure::Text(node, graphics));
        }
        else if (element == "rect")
        {
            figures.push_back(new MyFigure::Rectangle(node, graphics));
        }
        else if (element == "line")
        {
            figures.push_back(new MyFigure::Line(node, graphics));
        }
        else if (element == "polygon")
        {
            figures.push_back(new MyFigure::Polygon(node, graphics));
        }
        else if (element == "polyline")
        {
            figures.push_back(new MyFigure::Polyline(node, graphics));
        }
        else if (element == "ellipse")
        {
            figures.push_back(new MyFigure::Ellipse(node, graphics));
        }
        else if (element == "circle")
        {
            figures.push_back(new MyFigure::Circle(node, graphics));
        }
        else if (element == "path")
        {
            figures.push_back(new MyFigure::Path(node, graphics));
        }
        else if (element == "g")
        {
            figures.push_back(new MyFigure::Group(node, graphics));
        }
        else if (element == "defs")
        {
            Defs::getInstance()->setDefsNode(node);
        }
    }
}

void FigureDraw::draw()
{
    if (!svgViewBox.empty()) {
    // Tách các giá trị từ viewBox
        float viewBoxMinX = 0, viewBoxMinY = 0, viewBoxWidth = 0, viewBoxHeight = 0;
        std::sscanf(svgViewBox.c_str(), "%f %f %f %f", &viewBoxMinX, &viewBoxMinY, &viewBoxWidth, &viewBoxHeight);

        // Tính tỷ lệ scaleX và scaleY
        float scaleX = svgWidth / viewBoxWidth;
        float scaleY = svgHeight / viewBoxHeight;

        // Chọn tỷ lệ nhỏ hơn để đảm bảo giữ nguyên tỷ lệ aspect ratio
        float scale = std::min(scaleX, scaleY);

        // Tính toán offset để căn giữa viewBox bên trong viewport (nếu cần)
        float offsetX = (svgWidth - viewBoxWidth * scale) / 2;
        float offsetY = (svgHeight - viewBoxHeight * scale) / 2;

        // Thiết lập ma trận transform tổng quát
        graphics.TranslateTransform(offsetX, offsetY);                  // Dịch chuyển căn giữa
        graphics.ScaleTransform(scale, scale);                         // Thu nhỏ/phóng to theo tỷ lệ
        graphics.TranslateTransform(-viewBoxMinX, -viewBoxMinY);       // Đặt gốc viewBox về (0, 0)
    }

    // Vẽ các hình
    for (Figure *figure : figures)
    {
        std::cout << "draw figure" << endl;
        figure->draw();
    }
}
