#include <iostream>
#include <stdexcept>
#include <string>


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

class DynamicMatrix {
private:
	const int rows;
	const int cols;
	int** data;

public:
	DynamicMatrix(int r, int c) : rows(r), cols(c) {
        	this->data = new int*[rows];
            	for (int i = 0; i < rows; ++i) {
                	this->data[i] = new int[cols]{0};
		}
        }

        DynamicMatrix(const DynamicMatrix& other) : rows(other.rows), cols(other.cols) {
        	this->data = new int*[rows];
            	for (int i = 0; i < rows; ++i) {
                	this->data[i] = new int[cols];
                	for (int j = 0; j < cols; ++j) {
                    		this->data[i][j] = other.data[i][j];
                	}
            	}
        }

        ~DynamicMatrix() {
        	for (int i = 0; i < rows; ++i) {
                	delete[] this->data[i];
            	}
            	delete[] this->data;
        }
	
	void show() {
		for (int i = 0; i < rows; ++i) {
                	for (int j = 0; j < cols; ++j) {
				std::cout << this->data[i][j] << " ";
                	}
			std::cout << std::endl;
            	}
	}
	
	DynamicMatrix& operator=(const DynamicMatrix& other) {
	    	if (this->rows != other.rows || this->cols != other.cols) {
                	throw DimensionMismatchException("Размеры матриц не совпадают для присваивания");
            	}
            	if (this != &other) {
                	for (int i = 0; i < rows; ++i) {
                    		delete[] this->data[i];
                	}
                	delete[] this->data;

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

        DynamicMatrix operator+(const DynamicMatrix& other) const {
         	if (this->rows != other.rows || this->cols != other.cols) {
                	throw DimensionMismatchException("Размеры матриц не совпадают для сложения");
            	}
            	DynamicMatrix result(rows, cols);
            	for (int i = 0; i < rows; ++i) {
                	for (int j = 0; j < cols; ++j) {
                    		result.data[i][j] = this->data[i][j] + other.data[i][j];
                	}
            	}
            	return result;
        }
};

int main() {
	try {
        DynamicMatrix m1(2, 2);
	DynamicMatrix m2(2, 2);

        m1(0, 0) = 5;
        std::cout << "Значение элемента (0,0): " << m1(0, 0) << std::endl;

    m2 = m2;
	m2 = m1 + m1;
	m1 = m2 + m1;

	std::cout << "Матрица m1:\n";
	m1.show();
	std::cout << "Матрица m2:\n";
	m2.show();

        std::cout << "Попытка обращения к некорректному индексу (5,5):" << std::endl;
        m1(5, 5) = 10;
	} catch (const MatrixException& e) {
        std::cout << "Перехвачено пользовательское исключение: " << e.what() << std::endl;
    }
}

