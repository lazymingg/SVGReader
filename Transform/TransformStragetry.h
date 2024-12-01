#ifndef _TRANSFORM_STRAGETRY_H_
#define _TRANSFORM_STRAGETRY_H_

#include <iostream>
#include "../extendUtil/Matrix.h"

class TransformStragetry
{
    private:

    public:
        virtual void transform(MyMatrix::Matrix &Matrix) = 0;
};

class Translate : public TransformStragetry
{
    private:
        int dx, dy;
    public:
        Translate(double dx, double dy) : dx(dx), dy(dy) {}
        void transform(MyMatrix::Matrix &matrix) override
        {
            // tao ma tran bien doi
            // nhan ma tran bien doi voi ma tran cua hinh
            std::cout << "Translate: " << dx << " " << dy << std::endl;
        }
};

class Scale : public TransformStragetry
{
    private:
        int sx, sy;
    public:
        Scale(int sx, int sy) : sx(sx), sy(sy) {}
        void transform(MyMatrix::Matrix &matrix) override
        {
            // tao ma tran bien doi
            // nhan ma tran bien doi voi ma tran cua hinh
            std::cout << "Scale: " << sx << " " << sy << std::endl;
        }
};

class Rotate : public TransformStragetry
{
    private:
        int angle;
    public:
        Rotate(int angle) : angle(angle) {}
        void transform(MyMatrix::Matrix &matrix) override
        {
            // tao ma tran bien doi
            // nhan ma tran bien doi voi ma tran cua hinh
            std::cout << "Rotate: " << angle << std::endl;
        }
};



#endif