#include <iostream>
#include <stdexcept>

class Matrix {
private:
    int rows;
    int cols;
    int** data;

public:
    Matrix(int r, int c) : rows(r), cols(c) {
        data = new int*[rows];
        for (int i = 0; i < rows; ++i) {
            data[i] = new int[cols]{0};
        }
    }

    Matrix(const Matrix& other) : rows(other.rows), cols(other.cols) {
        data = new int*[rows];
        for (int i = 0; i < rows; ++i) {
            data[i] = new int[cols];
            for (int j = 0; j < cols; ++j) {
                data[i][j] = other.data[i][j];
            }
        }
    }

    ~Matrix() {
        for (int i = 0; i < rows; ++i) {
            delete[] data[i];
        }
        delete[] data;
    }

    int getAt(int r, int c) const {
        if (r < 0 || r >= rows || c < 0 || c >= cols) {
            throw std::out_of_range("Index out of bounds");
        }
        return data[r][c];
    }

    void setAt(int r, int c, int value) {
        if (r < 0 || r >= rows || c < 0 || c >= cols) {
            throw std::out_of_range("Index out of bounds");
        }
        data[r][c] = value;
    }

    void print() const {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                std::cout << data[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    friend class MatrixOperations;
};

class MatrixOperations {
public:
    static Matrix add(const Matrix& a, const Matrix& b) {
        if (a.rows != b.rows || a.cols != b.cols) {
            throw std::invalid_argument("Dimensions mismatch");
        }
        Matrix result(a.rows, a.cols);
        for (int i = 0; i < a.rows; ++i) {
            for (int j = 0; j < a.cols; ++j) {
                result.data[i][j] = a.data[i][j] + b.data[i][j];
            }
        }
        return result;
    }

    static Matrix multiply(const Matrix& a, const Matrix& b) {
        if (a.cols != b.rows) {
            throw std::invalid_argument("Dimensions mismatch");
        }
        Matrix result(a.rows, b.cols);
        for (int i = 0; i < a.rows; ++i) {
            for (int j = 0; j < b.cols; ++j) {
                result.data[i][j] = 0;
                for (int k = 0; k < a.cols; ++k) {
                    result.data[i][j] += a.data[i][k] * b.data[k][j];
                }
            }
        }
        return result;
    }
};

