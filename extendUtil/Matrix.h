#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <vector>
#include <stdexcept>

class Matrix {
private:
    std::vector<std::vector<double>> data;
    int rows, cols;

public:
    // Constructor
    Matrix(int rows, int cols);

    // Nhập ma trận
    void input();

    // Xuất ma trận
    void print() const;

    // Phép nhân ma trận
    Matrix operator*(const Matrix& other) const;
};

#endif // MATRIX_H
