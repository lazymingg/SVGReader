#include "../shapeheader/Ellipse.h"

MyFigure::Ellipse::Ellipse(xml_node<> *rootNode, Gdiplus::Graphics &graphics) : Figure(rootNode, graphics)
{
    if (!rootNode->first_attribute("cx"))
        center.setX(0);
    else
        center.setX(stof(rootNode->first_attribute("cx")->value()));

    if (!rootNode->first_attribute("cy"))
        center.setY(0);
    else
        center.setY(stof(rootNode->first_attribute("cy")->value()));

    if (rootNode->first_attribute("rx") && rootNode->first_attribute("ry"))
    {
        rx = stof(rootNode->first_attribute("rx")->value());
        ry = stof(rootNode->first_attribute("ry")->value());
        cout << "Ellipse rx: " << rx << ", ry: " << ry << endl;
    }
    else
    {
        std::cout << "Attributes 'rx' or 'ry' not found in ellipse node." << std::endl;
        rx = 0;
        ry = 0;
    }
}

void MyFigure::Ellipse::drawEllipse(Graphics &graphics)
{

    // Lấy giá trị `viewBox` scale từ `graphics`
    Gdiplus::Matrix currentMatrix;
    graphics.GetTransform(&currentMatrix);

    Brush *fillBrush = penRender.getSolidBrush(attributes);
    Pen *strokePen = penRender.getSolidPen(attributes);
    LinearGradientManager *temp = penRender.getPenLinear(static_cast<Fill *>(attributes.getAttributes("fill"))->getId(), attributes);
    Gdiplus::Pen *penLinear = nullptr;
    if (temp != nullptr)
    {
        penLinear = temp->getPen();
    }
    
    std::cout << "rx = " << rx << ", ry = " << ry << std::endl;
    Gdiplus::Matrix a;
    static_cast<Transform *>(attributes.getAttributes("transform"))->transform(a);
    graphics.MultiplyTransform(&a);

    // Gdiplus::Matrix originalMatrix;
    // graphics.GetTransform(&originalMatrix);
    // graphics.SetTransform(&a);

    // graphics.FillEllipse(fillBrush, center.getX() - rx, center.getY() - ry, rx * 2, ry * 2);
    graphics.DrawEllipse(strokePen, center.getX() - rx, center.getY() - ry, rx * 2, ry * 2);

    if (penLinear != nullptr)
    {
        temp->printColor();
        
        //     // Tạo các điểm đầu và cuối cho LinearGradientBrush
        // Gdiplus::PointF startPoint(50.0f, 50.0f); // Điểm bắt đầu của gradient
        // Gdiplus::PointF endPoint(200.0f, 50.0f);  // Điểm kết thúc của gradient

        // // Màu sắc và các offset cho gradient
        // std::vector<Gdiplus::Color> colors = {Gdiplus::Color::Red, Gdiplus::Color::Yellow, Gdiplus::Color::Blue};
        // std::vector<Gdiplus::REAL> offsets = {0.0f, 0.5f, 1.0f};

        // // Tạo LinearGradientBrush
        // Gdiplus::LinearGradientBrush brush(startPoint, endPoint, Gdiplus::Color::Black, Gdiplus::Color::White);
        // brush.SetInterpolationColors(colors.data(), offsets.data(), colors.size());

        // // Vẽ một ellipse với LinearGradientBrush (fill ellipse)
        // Gdiplus::RectF rect(50.0f, 50.0f, 150.0f, 100.0f);
        // // graphics.FillEllipse(&brush, rect);

        Gdiplus::PointF startPoint = temp->getStartPoint();
        Gdiplus::PointF endPoint = temp->getEndPoint();

        // mau sac  
        std::vector<Gdiplus::Color> colors = temp->getColors();
        std::vector<Gdiplus::REAL> offsets = temp->getOffsets();

        // convert to Gdiplus::Color
        Gdiplus::Color* color = new Gdiplus::Color[colors.size()];
        for (size_t i = 0; i < colors.size(); ++i)
        {
            color[i] = colors[i];
        }
        Gdiplus::REAL* offset = new Gdiplus::REAL[offsets.size()];
        for (size_t i = 0; i < offsets.size(); ++i)
        {
            offset[i] = offsets[i];
        }
        // Create a LinearGradientBrush
        Gdiplus::LinearGradientBrush brush(startPoint, endPoint, Gdiplus::Color::Black, Gdiplus::Color::White);
        brush.SetInterpolationColors(color, offset, colors.size());

        //print all brush data
        cout << "=====Brush data\n";
        for (size_t i = 0; i < colors.size(); ++i)
        {
            cout << "Color: " << int(colors[i].GetR()) << ", " << int(colors[i].GetG()) << ", " << int(colors[i].GetB()) << ", " << int(colors[i].GetA()) << " - Offset: " << offsets[i] << endl;
        }
        // start point and end point
        cout << "Start point: " << startPoint.X << ", " << startPoint.Y << endl;
        cout << "End point: " << endPoint.X << ", " << endPoint.Y << endl;
        
        // Draw an ellipse with LinearGradientBrush (fill ellipse)
        Gdiplus::RectF rect(center.getX() - rx, center.getY() - ry, rx * 2, ry * 2);
        graphics.FillEllipse(&brush, rect);
    }

    graphics.SetTransform(&currentMatrix);

    delete fillBrush;
    delete strokePen;
    if (penLinear != nullptr)
        delete penLinear;
    if (temp != nullptr)
        delete temp;
}

void MyFigure::Ellipse::draw()
{
    std::cout << "Draw Ellipse: center = (" << center.getX() << ", " << center.getY() << "), ";
    std::cout << "rx = " << rx << ", ry = " << ry << "\n\n";
    drawEllipse(graphics);
}
