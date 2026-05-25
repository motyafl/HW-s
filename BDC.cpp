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
        this->data = new int*[this->rows];
        for (int i = 0; i < this->rows; ++i) {
            this->data[i] = new int[this->cols]{0};
        }
    }

    Matrix(const Matrix& other) : rows(other.rows), cols(other.cols) {
        if (other.data != nullptr) {
            this->data = new int*[this->rows];
            for (int i = 0; i < this->rows; ++i) {
                this->data[i] = new int[this->cols];
                for (int j = 0; j < this->cols; ++j) {
                    this->data[i][j] = other.data[i][j];
                }
            }
        } else {
            this->data = nullptr;
        }
    }

    virtual ~Matrix() {
        this->clear();
    }

    void clear() {
        if (this->data != nullptr) {
            for (int i = 0; i < this->rows; ++i) {
                delete[] this->data[i];
            }
            delete[] this->data;
            this->data = nullptr;
        }
        this->rows = 0;
        this->cols = 0;
    }

    int getRows() const { return this->rows; }
    int getCols() const { return this->cols; }

    int* operator[](int index) {
        if (index < 0 || index >= this->rows) {
            throw std::out_of_range("Индекс строки вышел за границы");
        }
        return this->data[index];
    }

    const int* operator[](int index) const {
        if (index < 0 || index >= this->rows) {
            throw std::out_of_range("Индекс строки вышел за границы");
        }
        return this->data[index];
    }

    operator bool() const {
        return this->data != nullptr && this->rows > 0 && this->cols > 0;
    }

    void print() const {
        for (int i = 0; i < this->rows; ++i) {
            for (int j = 0; j < this->cols; ++j) {
                std::cout << this->data[i][j] << " ";
            }
            std::cout << "\n";
        }
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

    int getNonZeroCount() const { return this->nonZeroCount; }
};

class SparseMatrix : public Matrix, public StorageInfo {
public:
    SparseMatrix(int r, int c, int nzCount) 
        : Matrix(r, c), StorageInfo(nzCount) {}
};

int main() {
    try {
        Matrix m1(2, 2);
        m1[0][0] = 1; m1[0][1] = 2;
        m1[1][0] = 3; m1[1][1] = 4;

        if (m1) {
            std::cout << "Матрица m1 успешно инициализирована. Вывод m1:" << std::endl;
            m1.print();
        }

        std::cout << "Сложение матриц (m1 + m1):" << std::endl;
        Matrix m2 = m1 + m1;
        m2.print();

        std::cout << "Умножение матрицы на число (m1 * 3):" << std::endl;
        Matrix m3 = m1 * 3;
        m3.print();

        std::cout << "Проверка множественного наследования (SparseMatrix):" << std::endl;
        SparseMatrix sm(5, 5, 4);
        std::cout << "Размер сетки: " << sm.getRows() << "x" << sm.getCols() << std::endl;
        std::cout << "Ненулевых элементов: " << sm.getNonZeroCount() << std::endl;

    } catch (const std::exception& e) {
        std::cout << "Исключение: " << e.what() << std::endl;
    }
    return 0;
}

