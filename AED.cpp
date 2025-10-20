#include <iostream>
#include <random>
#include <stdexcept>
class Matrix {
    int rows, cols;
    int** matrix;
  public:
    Matrix(int r, int c) { //конструктор
        rows = r;
        cols = c;
        matrix = new int*[rows];
        for (int i = 0; i < rows; ++i)
            matrix[i] = new int[cols];
    }

    Matrix(const Matrix& other) { //копирующий конструктор
        rows = other.rows;
        cols = other.cols;
        matrix = new int*[rows];
        for (int i = 0; i < rows; ++i) {
            matrix[i] = new int[cols];
            for (int j = 0; j < cols; ++j)
                matrix[i][j] = other.matrix[i][j];
        }
    }

    int &at(int row, int col) { //обращение к значению матрицы
        if (row < 0 || row >= rows || col < 0 || col >= cols)
            throw std::out_of_range("Matrix index out of range");
        return matrix[row][col];
    }
    const int &at(int row, int col) const { //константное обращение
          if (row < 0 || row >= rows || col < 0 || col >= cols)
            throw std::out_of_range("Matrix index out of range");
        return matrix[row][col];}

    Matrix add(const Matrix& other) { //копирование матрицы и запись в копию суммы двух матриц
        Matrix result(*this);
        for (int i = 0; i < rows; ++i) {
          for (int j = 0; j < cols; ++j) {
                 result.at(i, j) = this->at(i, j) + other.at(i, j);
            }
        }
        return result;
    }

    ~Matrix() {
        for (int i = 0; i < rows; ++i) {
            delete[] matrix[i];
        }
        delete[] matrix;
    }
};

void printM(const Matrix &M, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        std::cout << "\n";
        for (int j = 0; j < cols; ++j) {
            std::cout << M.at(i, j) << " ";
        }
    }
    std::cout << std::endl;


}

int main()
{
    int rows = 4;
    int cols = 4;

    std::random_device rd;  // hardware entropy (if available)
    std::mt19937 gen(rd()); // Mersenne Twister engine
    std::uniform_int_distribution<> dist(-100, 100);
    Matrix M1(rows, cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            M1.at(i, j) = dist(gen);
        }
    }

    Matrix M2(rows, cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            M2.at(i, j) = dist(gen);
        }
    }

    Matrix Mr = M1.add(M2);
    std::wcout << L"Матрица 1";
    printM(M1, rows, cols);
    std::wcout << L"\nМатрица 2";
    printM(M2, rows, cols);
    std::wcout << L"\nСумма двух матриц";
    printM(Mr, rows, cols);
}
