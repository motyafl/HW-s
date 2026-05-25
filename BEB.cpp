#include <iostream>
#include <stdexcept>

class Matrix {
private:
    int rows;
    int cols;
    int** data;
    static int totalMatrices;

public:
    class RowProxy {
    private:
        int* rowData;
        int size;
    public:
        RowProxy(int* row, int size) : rowData(row), size(size) {}
        int& operator[](int j) {
            if (j < 0 || j >= size) {
                throw std::out_of_range("Индекс столбца вышел за границы");
            }
            return rowData[j];
        }
        const int& operator[](int j) const {
            if (j < 0 || j >= size) {
                throw std::out_of_range("Индекс столбца вышел за границы");
            }
            return rowData[j];
        }
    };

    Matrix(int r, int c) : rows(r), cols(c) {
        data = new int*[rows];
        for (int i = 0; i < rows; ++i) {
            data[i] = new int[cols]{0};
        }
        ++totalMatrices;
    }

    Matrix(const Matrix& other) : rows(other.rows), cols(other.cols) {
        data = new int*[rows];
        for (int i = 0; i < rows; ++i) {
            data[i] = new int[cols];
            for (int j = 0; j < cols; ++j) {
                data[i][j] = other.data[i][j];
            }
        }
        ++totalMatrices;
    }

    ~Matrix() {
        for (int i = 0; i < rows; ++i) {
            delete[] data[i];
        }
        delete[] data;
        --totalMatrices;
    }

    Matrix& operator=(const Matrix& other) {
        if (this != &other) {
            for (int i = 0; i < rows; ++i) {
                delete[] data[i];
            }
            delete[] data;

            rows = other.rows;
            cols = other.cols;
            data = new int*[rows];
            for (int i = 0; i < rows; ++i) {
                data[i] = new int[cols];
                for (int j = 0; j < cols; ++j) {
                    data[i][j] = other.data[i][j];
                }
            }
        }
        return *this;
    }

    RowProxy operator[](int i) {
        if (i < 0 || i >= rows) {
            throw std::out_of_range("Индекс строки вышел за границы");
        }
        return RowProxy(data[i], cols);
    }

    const RowProxy operator[](int i) const {
        if (i < 0 || i >= rows) {
            throw std::out_of_range("Индекс строки вышел за границы");
        }
        return RowProxy(data[i], cols);
    }

    Matrix operator+(const Matrix& other) const {
        if (rows != other.rows || cols != other.cols) {
            throw std::invalid_argument("Несоответствие размерностей матриц при сложении");
        }
        Matrix result(rows, cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                result.data[i][j] = data[i][j] + other.data[i][j];
            }
        }
        return result;
    }

    Matrix operator*(const Matrix& other) const {
        if (cols != other.rows) {
            throw std::invalid_argument("Несоответствие размерностей матриц при умножении");
        }
        Matrix result(rows, other.cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < other.cols; ++j) {
                result.data[i][j] = 0;
                for (int k = 0; k < cols; ++k) {
                    result.data[i][j] += data[i][k] * other.data[k][j];
                }
            }
        }
        return result;
    }

    operator bool() const {
        if (rows != cols) return false;
        return getDeterminant(data, rows) != 0;
    }

    static int getTotalMatrices() { return totalMatrices; }

private:
    static int getDeterminant(int** matrix, int n) {
        if (n == 1) return matrix[0][0];
        if (n == 2) return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];

        int det = 0;
        int** submatrix = new int*[n - 1];
        for (int i = 0; i < n - 1; ++i) submatrix[i] = new int[n - 1];

        for (int x = 0; x < n; ++x) {
            int subi = 0;
            for (int i = 1; i < n; ++i) {
                int subj = 0;
                for (int j = 0; j < n; ++j) {
                    if (j == x) continue;
                    submatrix[subi][subj] = matrix[i][j];
                    subj++;
                }
                subi++;
            }
            int sign = (x % 2 == 0) ? 1 : -1;
            det += sign * matrix[0][x] * getDeterminant(submatrix, n - 1);
        }

        for (int i = 0; i < n - 1; ++i) delete[] submatrix[i];
        delete[] submatrix;

        return det;
    }
};

int Matrix::totalMatrices = 0;

int main() {
    try {
        std::cout << "Исходное количество матриц: " << Matrix::getTotalMatrices() << std::endl;

        Matrix m1(2, 2);
        m1[0][0] = 2; m1[0][1] = 1;
        m1[1][0] = 1; m1[1][1] = 3;

        Matrix m2(2, 2);
        m2[0][0] = 1; m2[0][1] = 0;
        m2[1][0] = 0; m2[1][1] = 1;

        std::cout << "Количество матриц после создания m1 и m2: " << Matrix::getTotalMatrices() << std::endl;

        Matrix sum = m1 + m2;
        std::cout << "Элемент sum[0][0]: " << sum[0][0] << std::endl;

        if (m1) {
            std::cout << "Матрица m1 невырожденная (определитель не равен 0)" << std::endl;
        } else {
            std::cout << "Матрица m1 вырожденная (определитель равен 0)" << std::endl;
        }

        Matrix m3(3, 2);
        std::cout << "Попытка сложить матрицы разных размеров..." << std::endl;
        Matrix errorSum = m1 + m3;

    } catch (const std::invalid_argument& e) {
        std::cout << "Перехвачена ошибка операции: " << e.what() << std::endl;
    } catch (const std::out_of_range& e) {
        std::cout << "Перехвачена ошибка индекса: " << e.what() << std::endl;
    }

    return 0;
}
