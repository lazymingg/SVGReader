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
    cout << "\n\n\n";
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
            int sum = 0;
            for (int k = 0; k < cols; k++)
            {
            sum += matrix[i][k] * other.matrix[k][j];
            }
            result.setElement(i, j, sum);
        }
    }

    return result;
}

int MyMatrix::Matrix::getRows() const
{
    return this->rows;
}

int MyMatrix::Matrix::getCols() const
{
    return this->cols;
}

void MyMatrix::Matrix::setMatrix(std::vector<std::vector<int>> matrix)
{
    for (int i = 0; i < this->rows; i++)
        for (int j = 0; j < this->cols; j++)
            this->matrix[i][j] = matrix[i][j];
}

std::vector<std::vector<int>> MyMatrix::Matrix::getMatrix() const
{
    return this->matrix;
}

void MyMatrix::Matrix::setRows(int rows)
{
    this->rows = rows;
}

void MyMatrix::Matrix::setCols(int cols)
{
    this->cols = cols;
}

int MyMatrix::Matrix::getElement(int posX, int posY)
{
    return this->matrix[posX][posY];
}

void MyMatrix::Matrix::setElement(int posX, int posY, int value)
{
    this->matrix[posX][posY] = value;
}
