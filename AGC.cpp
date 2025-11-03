#include <iostream>
#include <memory>
#include <random>

struct Matrix {
    int N = 0; // default-initialized
    std::unique_ptr<std::unique_ptr<int[]>[]> rows; // 2D smart array
};

std::unique_ptr<Matrix> createMatrix(int n) {
	auto M = std::make_unique<Matrix>();
	M ->N = n;
	M ->rows = std::make_unique<std::unique_ptr<int[]>[]>(n);
	for (int i = 0; i < n; ++i) {
        	M->rows[i] = std::make_unique<int[]>(n);
        for (int j = 0; j < n; ++j) {
            M->rows[i][j] = 0;
        }
    }

    return M;
}

void printMatrix(const Matrix& mat) {
    for (int i = 0; i < mat.N; ++i) {
        for (int j = 0; j < mat.N; ++j) {
            std::cout << mat.rows[i][j] << "\t";
        }
        std::cout << "\n";
    }
}

std::unique_ptr<Matrix> copyMatrix(const Matrix& src) {
    auto dest = createMatrix(src.N);
    for (int i = 0; i < src.N; ++i) {
        for (int j = 0; j < src.N; ++j) {
            dest->rows[i][j] = src.rows[i][j];
        }
    }
    return dest;
}

std::unique_ptr<Matrix> multiplyMatrices(const Matrix& A, const Matrix& B) {
    if (A.N != B.N) {
        throw std::invalid_argument("Sizes must match");
    }
    auto C = createMatrix(A.N);
    int n = A.N;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int sum = 0;
            for (int k = 0; k < n; ++k) {
                sum += A.rows[i][k] * B.rows[k][j];
            }
            C->rows[i][j] = sum;
        }
    }
    return C;
}

void sortRows(Matrix& mat) {
    for (int i = 0; i < mat.N; ++i) {
        for (int j = 0; j < mat.N - 1; ++j) {
            int minIdx = j;
            for (int k = j + 1; k < mat.N; ++k) {
                if (mat.rows[i][k] < mat.rows[i][minIdx]) {
                    minIdx = k;
                }
            }
            if (minIdx != j) {
                std::swap(mat.rows[i][j], mat.rows[i][minIdx]);
            }
        }
    }
}

int main()
{
	int N = 5;
    	auto A = createMatrix(N);
    	auto B = createMatrix(N);

    	std::random_device rd;
    	std::mt19937 gen(rd());
    	std::uniform_int_distribution<> dis(-5, 5);
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
            		A->rows[i][j] = dis(gen);
            		B->rows[i][j] = dis(gen);
		}
	}

	std::cout << "A:" << std::endl;
	printMatrix(*A);
    	std::cout << "\nB:" << std::endl;
	printMatrix(*B);

    	auto C = multiplyMatrices(*A, *B);
    	std::cout << "\nС = A * B:" << std::endl;
	printMatrix(*C);

    	sortRows(*C);
    	std::cout << "\nМатрица C после сортировки:" << std::endl;
	printMatrix(*C);
}
