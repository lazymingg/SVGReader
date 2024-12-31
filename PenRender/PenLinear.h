#include <vector>
#include <memory>
#include <Gdiplus.h>

class LinearGradientManager
{
private:
    std::vector<Gdiplus::Color> colors_;
    std::vector<Gdiplus::REAL> offsets_;
    //point start and end
    Gdiplus::PointF startPoint;
    Gdiplus::PointF endPoint;
    Gdiplus::LinearGradientBrush *brush_;
    float strokeWidth; // stroke width
public:
    // Constructor: Tạo một LinearGradientBrush
    LinearGradientManager(Gdiplus::PointF startPoint, Gdiplus::PointF endPoint, 
                          std::vector<Gdiplus::Color> colors, std::vector<Gdiplus::REAL> offsets, 
                          float strokeWidth)
    {
        this->colors_ = colors;
        this->offsets_ = offsets;
        this->strokeWidth = strokeWidth;

        this->startPoint = startPoint;
        this->endPoint = endPoint;
        // Tạo LinearGradientBrush với các điểm bắt đầu và kết thúc
        this->brush_ = new Gdiplus::LinearGradientBrush(this->startPoint, this->endPoint, Gdiplus::Color::Black, Gdiplus::Color::White);
        // Thiết lập các điểm dừng (gradient stops)
        this->brush_->SetInterpolationColors(colors_.data(), offsets_.data(), colors_.size());
    }

    // Destructor: Giải phóng bộ nhớ của LinearGradientBrush
    ~LinearGradientManager()
    {
        delete brush_; // Xóa brush khi không sử dụng nữa
    }

    // Lấy brush
    Gdiplus::LinearGradientBrush *getBrush()
    {
        return this->brush_;
    }

    // get pen 
    Gdiplus::Pen *getPen()
    {
        return new Gdiplus::Pen(brush_, strokeWidth);
    }

    // Lấy danh sách màu sắc trong gradient
    std::vector<Gdiplus::Color> getColors()
    {
        return colors_;
    }

    // Lấy danh sách offset của gradient
    std::vector<Gdiplus::REAL> getOffsets()
    {
        return offsets_;
    }

    // get startPoint
    Gdiplus::PointF getStartPoint()
    {
        return startPoint;
    }

    // get endPoint
    Gdiplus::PointF getEndPoint()
    {
        return endPoint;
    }

    void printColor()
    {
        for (size_t i = 0; i < colors_.size(); ++i)
        {
            cout << "==================Color: " << int(colors_[i].GetR()) << ", " << int(colors_[i].GetG()) << ", " << int(colors_[i].GetB()) << ", " << int(colors_[i].GetA()) << " - Offset: " << offsets_[i] << endl;
        }
    }
    // Lấy chiều rộng stroke
    float getStrokeWidth()
    {
        return strokeWidth;
    }
};
