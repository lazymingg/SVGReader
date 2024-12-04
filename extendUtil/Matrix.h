#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <vector>
#include <stdexcept>

using namespace std;

namespace MyMatrix
{
class Matrix {

private:
    std::vector<std::vector<double>> matrix;
    int rows, cols;

public:
    // Constructor
    Matrix(int rows, int cols);
    Matrix(vector<vector<double>> matrix);

    //copy constructor
    Matrix(const Matrix &matrix);

    // Nhập ma trận
    void input();

    // Xuất ma trận
    void print() const;

    // Phép nhân ma trận
    Matrix operator*(const Matrix& other) const;
    
    //getter setter
    int getRows() const;
    int getCols() const;
    std::vector<std::vector<double>> getMatrix() const;
    void setMatrix(std::vector<std::vector<int>> matrix);
    void setRows(int rows);
    void setCols(int cols);
    double getElement(int posX, int posY);
    void setElement(int posX, int posY, double value);
};
}
#endif
