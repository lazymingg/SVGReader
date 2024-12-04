#ifndef _TRANSFORM_STRAGETRY_H_
#define _TRANSFORM_STRAGETRY_H_

#include <iostream>
#include "../extendUtil/Matrix.h"
#include <cmath>
#define M_PI 3.14159265358979323846
class TransformStragetry
{
protected:
public:
    virtual void transform(MyMatrix::Matrix &Matrix) = 0;
    //clone method
    virtual TransformStragetry *clone() = 0;
    virtual void print() = 0;
};


class Translate : public TransformStragetry
{
private:
    double dx, dy;

public:
    Translate(string str)
    {
        size_t openBracket = str.find("(");
        size_t closeBracket = str.find(")");
        size_t comma = str.find(",");
        dx = stod(str.substr(openBracket + 1, comma - openBracket - 1));
        dy = stod(str.substr(comma + 1, closeBracket - comma - 1));
    }

    void transform(MyMatrix::Matrix &matrix) override
    {
        // tao ma tran bien doi
        vector<vector<double>> matrixData;

        vector<double> x;
        x.push_back(1);
        x.push_back(0);
        x.push_back(dx);
        matrixData.push_back(x);

        vector<double> y;
        y.push_back(0);
        y.push_back(1);
        y.push_back(dy);
        matrixData.push_back(y);

        vector<double> z;
        z.push_back(0);
        z.push_back(0);
        z.push_back(1);
        matrixData.push_back(z);

        MyMatrix::Matrix translateMatrix(matrixData);
        translateMatrix.print();
        matrix.print();
        matrix = translateMatrix * matrix;
        matrix.print();


        // nhan ma tran bien doi voi ma tran cua hinh
        std::cout << "Translate: " << dx << " " << dy << std::endl;
    }

    TransformStragetry *clone() override
    {
        return new Translate(*this);
    }

    void print() override
    {
        std::cout << "Translate: " << dx << " " << dy << std::endl;
    }
};

class Scale : public TransformStragetry
{
private:
    double sx, sy;

public:
    Scale(string str)
    {
        size_t openBracket = str.find("(");
        size_t closeBracket = str.find(")");
        size_t comma = str.find(",");
       if (comma == string::npos)
            sx = sy = stoi(str.substr(openBracket + 1, closeBracket - openBracket - 1));
        else
        {
            sx = stod(str.substr(openBracket + 1, comma - openBracket - 1));
            sy = stod(str.substr(comma + 1, closeBracket - comma - 1));
        }

    }
    void transform(MyMatrix::Matrix &matrix) override
    {
        // tao ma tran bien doi
        vector<vector<double>> matrixData;

        vector<double> x;
        x.push_back(sx);
        x.push_back(0);
        x.push_back(0);
        matrixData.push_back(x);

        vector<double> y;
        y.push_back(0);
        y.push_back(sy);
        y.push_back(0);
        matrixData.push_back(y);

        vector<double> z;
        z.push_back(0);
        z.push_back(0);
        z.push_back(1);
        matrixData.push_back(z);

        MyMatrix::Matrix scaleMatrix(matrixData);
        matrix = scaleMatrix * matrix;
        // nhan ma tran bien doi voi ma tran cua hinh
        std::cout << "Scale: " << sx << " " << sy << std::endl;
    }

    TransformStragetry *clone() override
    {
        return new Scale(*this);
    }

    void print() override
    {
        std::cout << "Scale: " << sx << " " << sy << std::endl;
    }
};

class Rotate : public TransformStragetry
{
private:
    double angle;

public:
    Rotate(string str)
    {
        size_t openBracket = str.find("(");
        size_t closeBracket = str.find(")");
        angle = stod(str.substr(openBracket + 1, closeBracket - openBracket - 1));
    }
    void transform(MyMatrix::Matrix &matrix) override
    {
        // tao ma tran bien doi
        vector<vector<double>> matrixData;

        double radAngle = angle * M_PI / 180;
        vector<double> x;
        x.push_back(cos(radAngle));
        x.push_back(-sin(radAngle));
        x.push_back(0);
        matrixData.push_back(x);

        vector<double> y;
        y.push_back(sin(radAngle));
        y.push_back(cos(radAngle));
        y.push_back(0);
        matrixData.push_back(y);

        vector<double> z;
        z.push_back(0);
        z.push_back(0);
        z.push_back(1);
        matrixData.push_back(z);

        MyMatrix::Matrix rotateMatrix(matrixData);
        matrix = rotateMatrix * matrix;
        for (int i = 0; i < matrix.getRows(); i++)
        {
            for (int j = 0; j < matrix.getCols(); j++)
            {
                int temp = matrix.getElement(i, j);
                temp /= 100;
                matrix.setElement(i, j, temp);
            }
        }
        // nhan ma tran bien doi voi ma tran cua hinh
        std::cout << "Rotate: " << angle << std::endl;
    }

    TransformStragetry *clone() override
    {
        return new Rotate(*this);
    }

    void print() override
    {
        std::cout << "Rotate: " << angle << std::endl;
    }
};

#endif