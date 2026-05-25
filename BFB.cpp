#include <iostream>
#include <stdexcept>
#include <string>

namespace MathStructure {

    class MatrixException : public std::runtime_error {
    public:
        explicit MatrixException(const std::string& msg) : std::runtime_error(msg) {}
    };

    class IndexOutOfBoundsException : public MatrixException {
    public:
        IndexOutOfBoundsException() : MatrixException("Индекс вышел за допустимые границы матрицы") {}
    };

    class DimensionMismatchException : public MatrixException {
    public:
        explicit DimensionMismatchException(const std::string& msg) : MatrixException(msg) {}
    };

    class Matrix {
    private:
        int rows;
        int cols;
        int** data;
        static int createdCount;

    public:
        Matrix(int r, int c) : rows(r), cols(c) {
            this->data = new int*[rows];
            for (int i = 0; i < rows; ++i) {
                this->data[i] = new int[cols]{0};
            }
            ++createdCount;
        }

        Matrix(const Matrix& other) : rows(other.rows), cols(other.cols) {
            this->data = new int*[rows];
            for (int i = 0; i < rows; ++i) {
                this->data[i] = new int[cols];
                for (int j = 0; j < cols; ++j) {
                    this->data[i][j] = other.data[i][j];
                }
            }
            ++createdCount;
        }

        ~Matrix() {
            for (int i = 0; i < rows; ++i) {
                delete[] this->data[i];
            }
            delete[] this->data;
            --createdCount;
        }

        Matrix& operator=(const Matrix& other) {
            if (this != &other) {
                for (int i = 0; i < rows; ++i) {
                    delete[] this->data[i];
                }
                delete[] this->data;

                this->rows = other.rows;
                this->cols = other.cols;
                this->data = new int*[rows];
                for (int i = 0; i < rows; ++i) {
                    this->data[i] = new int[cols];
                    for (int j = 0; j < cols; ++j) {
                        this->data[i][j] = other.data[i][j];
                    }
                }
            }
            return *this;
        }

        int& operator()(int row, int col) {
            if (row < 0 || row >= rows || col < 0 || col >= cols) {
                throw IndexOutOfBoundsException();
            }
            return this->data[row][col];
        }

        const int& operator()(int row, int col) const {
            if (row < 0 || row >= rows || col < 0 || col >= cols) {
                throw IndexOutOfBoundsException();
            }
            return this->data[row][col];
        }

        Matrix operator+(const Matrix& other) const {
            if (this->rows != other.rows || this->cols != other.cols) {
                throw DimensionMismatchException("Размеры матриц не совпадают для сложения");
            }
            Matrix result(rows, cols);
            for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < cols; ++j) {
                    result.data[i][j] = this->data[i][j] + other.data[i][j];
                }
            }
            return result;
        }

        Matrix operator*(const Matrix& other) const {
            if (this->cols != other.rows) {
                throw DimensionMismatchException("Размеры матриц несовместимы для умножения");
            }
            Matrix result(this->rows, other.cols);
            for (int i = 0; i < this->rows; ++i) {
                for (int j = 0; j < other.cols; ++j) {
                    result.data[i][j] = 0;
                    for (int k = 0; k < this->cols; ++k) {
                        result.data[i][j] += this->data[i][k] * other.data[k][j];
                    }
                }
            }
            return result;
        }

        static int getCreatedCount() { return createdCount; }

        class Iterator {
        private:
            const Matrix& matrix;
            int r, c;

        public:
            Iterator(const Matrix& m, int startR = 0, int startC = 0) 
                : matrix(m), r(startR), c(startC) {}

            bool hasNext() const {
                return r < matrix.rows;
            }

            int next() {
                int value = matrix.data[r][c];
                ++c;
                if (c >= matrix.cols) {
                    c = 0;
                    ++r;
                }
                return value;
            }
        };

        Iterator begin() const { return Iterator(*this, 0, 0); }
    };

    int Matrix::createdCount = 0;
}

int main() {
    try {
        MathStructure::Matrix m(2, 2);
        m(0, 0) = 5;
        std::cout << "Значение элемента: " << m(0, 0) << std::endl;
        std::cout << "Попытка обращения к некорректному индексу..." << std::endl;
        m(5, 5) = 10;
    } catch (const MathStructure::MatrixException& e) {
        std::cout << "Перехвачено пользовательское исключение: " << e.what() << std::endl;
    }
    return 0;
}

