#include <iostream>
#include <stdexcept>

class Matrix {
private:
    int** data;
    int rows;
    int cols;

public:
    Matrix() : data(nullptr), rows(0), cols(0) {}

    Matrix(int r, int c) : rows(r), cols(c) {
        data = new int*[rows];
        for (int i = 0; i < rows; ++i) {
            data[i] = new int[cols]{0};
        }
    }

    Matrix(const Matrix& other) : rows(other.rows), cols(other.cols) {
        if (other.data != nullptr) {
            data = new int*[rows];
            for (int i = 0; i < rows; ++i) {
                data[i] = new int[cols];
                for (int j = 0; j < cols; ++j) {
                    data[i][j] = other.data[i][j];
                }
            }
        } else {
            data = nullptr;
        }
    }

    ~Matrix() {
        clear();
    }

    void clear() {
        if (data != nullptr) {
            for (int i = 0; i < rows; ++i) {
                delete[] data[i];
            }
            delete[] data;
            data = nullptr;
        }
        rows = 0;
        cols = 0;
    }

    int getRows() const { return rows; }
    int getCols() const { return cols; }

    int* operator[](int index) {
        if (index < 0 || index >= rows) {
            throw std::out_of_range("Индекс строки вышел за границы");
        }
        return this->data[index];
    }

    const int* operator[](int index) const {
        if (index < 0 || index >= rows) {
            throw std::out_of_range("Индекс строки вышел за границы");
        }
        return this->data[index];
    }

    operator bool() const {
        return this->data != nullptr && this->rows > 0 && this->cols > 0;
    }

    friend Matrix operator+(const Matrix& a, const Matrix& b);
    friend Matrix operator*(const Matrix& a, int scalar);
};

Matrix operator+(const Matrix& a, const Matrix& b) {
    if (a.rows != b.rows || a.cols != b.cols) {
        throw std::invalid_argument("Размеры матриц не совпадают");
    }
    Matrix result(a.rows, a.cols);
    for (int i = 0; i < a.rows; ++i) {
        for (int j = 0; j < a.cols; ++j) {
            result.data[i][j] = a.data[i][j] + b.data[i][j];
        }
    }
    return result;
}

Matrix operator*(const Matrix& a, int scalar) {
    Matrix result(a.rows, a.cols);
    for (int i = 0; i < a.rows; ++i) {
        for (int j = 0; j < a.cols; ++j) {
            result.data[i][j] = a.data[i][j] * scalar;
        }
    }
    return result;
}

class StorageInfo {
protected:
    int nonZeroCount;

public:
    StorageInfo(int count) : nonZeroCount(count) {}
    virtual ~StorageInfo() = default;

    int getNonZeroCount() const { return nonZeroCount; }
};

class SparseMatrix : public Matrix, public StorageInfo {
public:
    SparseMatrix(int r, int c, int nzCount) : Matrix(r, c), StorageInfo(nzCount) {}
};

int main() {
    Matrix m1(2, 2);
    m1[0][0] = 1; m1[0][1] = 2;
    m1[1][0] = 3; m1[1][1] = 4;

    if (m1) {
        Matrix m2 = m1 + m1;
        Matrix m3 = m1 * 3;
    }

    SparseMatrix sm(5, 5, 4);
    return 0;
}

