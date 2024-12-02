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
};


class Translate : public TransformStragetry
{
private:
    int dx, dy;

public:
    Translate(string str)
    {
        size_t openBracket = str.find("(");
        size_t closeBracket = str.find(")");
        size_t comma = str.find(",");
        dx = stoi(str.substr(openBracket + 1, comma - openBracket - 1));
        dy = stoi(str.substr(comma + 1, closeBracket - comma - 1));
    }

    void transform(MyMatrix::Matrix &matrix) override
    {
        // tao ma tran bien doi
        vector<vector<int>> matrixData;

        vector<int> x;
        x.push_back(1);
        x.push_back(0);
        x.push_back(dx);
        matrixData.push_back(x);

        vector<int> y;
        y.push_back(0);
        y.push_back(1);
        y.push_back(dy);
        matrixData.push_back(y);

        vector<int> z;
        z.push_back(0);
        z.push_back(0);
        z.push_back(1);
        matrixData.push_back(z);

        MyMatrix::Matrix translateMatrix(matrixData);
        matrix = translateMatrix * matrix;

        // nhan ma tran bien doi voi ma tran cua hinh
        std::cout << "Translate: " << dx << " " << dy << std::endl;
    }
};

class Scale : public TransformStragetry
{
private:
    int sx, sy;

public:
    Scale(string str)
    {
        size_t openBracket = str.find("(");
        size_t closeBracket = str.find(")");
        size_t comma = str.find(",");
        sx = stoi(str.substr(openBracket + 1, comma - openBracket - 1));
        sy = stoi(str.substr(comma + 1, closeBracket - comma - 1));
    }
    void transform(MyMatrix::Matrix &matrix) override
    {
        // tao ma tran bien doi
        vector<vector<int>> matrixData;

        vector<int> x;
        x.push_back(sx);
        x.push_back(0);
        x.push_back(0);
        matrixData.push_back(x);

        vector<int> y;
        y.push_back(0);
        y.push_back(sy);
        y.push_back(0);
        matrixData.push_back(y);

        vector<int> z;
        z.push_back(0);
        z.push_back(0);
        z.push_back(1);
        matrixData.push_back(z);

        MyMatrix::Matrix scaleMatrix(matrixData);
        matrix = scaleMatrix * matrix;
        // nhan ma tran bien doi voi ma tran cua hinh
        std::cout << "Scale: " << sx << " " << sy << std::endl;
    }
};

class Rotate : public TransformStragetry
{
private:
    int angle;

public:
    Rotate(string str)
    {
        size_t openBracket = str.find("(");
        size_t closeBracket = str.find(")");
        angle = stoi(str.substr(openBracket + 1, closeBracket - openBracket - 1));
    }
    void transform(MyMatrix::Matrix &matrix) override
    {
        // tao ma tran bien doi
        vector<vector<int>> matrixData;

        double radAngle = angle * M_PI / 180;
        vector<int> x;
        x.push_back(cos(radAngle) * 100);
        x.push_back(-sin(radAngle) * 100);
        x.push_back(0);
        matrixData.push_back(x);

        vector<int> y;
        y.push_back(sin(radAngle) * 100);
        y.push_back(cos(radAngle) * 100);
        y.push_back(0);
        matrixData.push_back(y);

        vector<int> z;
        z.push_back(0);
        z.push_back(0);
        z.push_back(100);
        matrixData.push_back(z);

        MyMatrix::Matrix rotateMatrix(matrixData);
        matrix = rotateMatrix * matrix;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                int temp = matrix.getElement(i, j);
                temp /= 100;
                matrix.setElement(i, j, temp);
            }
        }
        // nhan ma tran bien doi voi ma tran cua hinh
        std::cout << "Rotate: " << angle << std::endl;
    }
};

#endif