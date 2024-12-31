#include <vector>
#include <memory>
#include <Gdiplus.h>

class LinearGradientManager
{
private:
    std::vector<Gdiplus::Color> colors_;
    std::vector<Gdiplus::REAL> offsets_;
    // point start and end
    Gdiplus::PointF startPoint;
    Gdiplus::PointF endPoint;
    Gdiplus::LinearGradientBrush *brush_;
    float strokeWidth; // stroke width
    bool isUserSpaceOnUse;
    string spreadMethod;

public:
    // Constructor: Tạo một LinearGradientBrush
    LinearGradientManager(Gdiplus::PointF startPoint, Gdiplus::PointF endPoint,
                          std::vector<Gdiplus::Color> colors, std::vector<Gdiplus::REAL> offsets,
                          float strokeWidth, string GradientUnits, string spreadMethod)
    {
        this->colors_ = colors;
        this->offsets_ = offsets;
        this->strokeWidth = strokeWidth;
        this->spreadMethod = spreadMethod;
        this->startPoint = startPoint;
        this->endPoint = endPoint;
        // Tạo LinearGradientBrush với các điểm bắt đầu và kết thúc
        this->brush_ = new Gdiplus::LinearGradientBrush(this->startPoint, this->endPoint, Gdiplus::Color::Black, Gdiplus::Color::White);
        // we need to set the the stop at 0 and 1
        // the 0 will be the start color and 1 will be the end color
        this->offsets_.insert(this->offsets_.begin(), 0.0f);
        this->offsets_.push_back(1.0f);
        this->colors_.insert(this->colors_.begin(), this->colors_[0]);
        this->colors_.push_back(this->colors_[this->colors_.size() - 1]);
        // Thiết lập các điểm dừng (gradient stops)
        this->brush_->SetInterpolationColors(colors_.data(), offsets_.data(), colors_.size());
        // Set the wrap mode based on the spreadMethod
        if (spreadMethod == "reflect")
        {
            this->brush_->SetWrapMode(Gdiplus::WrapModeTileFlipXY);
        }
        else if (spreadMethod == "repeat")
        {
            this->brush_->SetWrapMode(Gdiplus::WrapModeTile);
        }
        else // Default to "pad"
        {
            this->brush_->SetWrapMode(Gdiplus::WrapModeClamp);
        }
        this->isUserSpaceOnUse = true;
        if (GradientUnits == "objectBoundingBox")
        {
            this->isUserSpaceOnUse = false;
        }
    }

    // Destructor: Giải phóng bộ nhớ của LinearGradientBrush
    ~LinearGradientManager()
    {
        delete brush_; // Xóa brush khi không sử dụng nữa
    }

    // Lấy brush
    Gdiplus::LinearGradientBrush *getBrush()
    {
        delete brush_;
        this->brush_ = new Gdiplus::LinearGradientBrush(this->startPoint, this->endPoint, Gdiplus::Color::Black, Gdiplus::Color::White);
        this->brush_->SetInterpolationColors(colors_.data(), offsets_.data(), colors_.size());
        if (spreadMethod == "reflect")
        {
            this->brush_->SetWrapMode(Gdiplus::WrapModeTileFlipXY);
        }
        else if (spreadMethod == "repeat")
        {
            this->brush_->SetWrapMode(Gdiplus::WrapModeTile);
        }
        else // Default to "pad"
        {
            this->brush_->SetWrapMode(Gdiplus::WrapModeClamp);
        }
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

    bool getIsUserSpaceOnUse()
    {
        return isUserSpaceOnUse;
    }

    void transformCoordinates(const Gdiplus::RectF &bbox)
    {
        this->startPoint.X = bbox.X + bbox.Width * startPoint.X;
        this->startPoint.Y = bbox.Y + bbox.Height * startPoint.Y;
        this->endPoint.X = bbox.X + bbox.Width * endPoint.X;
        this->endPoint.Y = bbox.Y + bbox.Height * endPoint.Y;
    }
};
