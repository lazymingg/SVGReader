#include "Matrix.h"

using namespace std;

MyMatrix::Matrix::Matrix(int rows, int cols)
{
    this->rows = rows;
    this->cols = cols;
    matrix.resize(rows);
    for (int i = 0; i < rows; i++)
    {
        matrix[i].resize(cols);
    }
}

MyMatrix::Matrix::Matrix(vector<vector<int>> matrix)
{
    this->rows = matrix.size();
    this->cols = matrix[0].size();
    this->matrix = matrix;
}

MyMatrix::Matrix::Matrix(const Matrix &matrix)
{
    this->rows = matrix.rows;
    this->cols = matrix.cols;
    this->matrix = matrix.matrix;
}

void MyMatrix::Matrix::input()
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            cin >> matrix[i][j];
        }
    }
}

void MyMatrix::Matrix::print() const
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

MyMatrix::Matrix MyMatrix::Matrix::operator*(const Matrix &other) const
{
    if (cols != other.rows)
    {
        throw invalid_argument("Invalid matrix size");
    }

    Matrix result(rows, other.cols);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < other.cols; j++)
        {
            result.matrix[i][j] = 0;
            for (int k = 0; k < cols; k++)
            {
                result.matrix[i][j] += matrix[i][k] * other.matrix[k][j];
            }
        }
    }

    return result;
}
