#include <iostream>
#include <stdexcept>
class String {
  	char** str;
  public:
    String(const char* line) { //копирующий конструктор
        str = new char*[sizeof(line)];
        }
    };
/*

    String(const char* other) { //копирующий конструктор
        str = new char*[];
	for (int i = 0; i < other.size(); ++i) {
            str[i] = other[i];
        }


    int &at(int row, int col) { //обращение к значению матрицы
        if (row < 0 || row >= rows || col < 0 || col >= cols)
            throw std::out_of_range("Matrix index out of range");
        return matrix[row][col];
    }

    String add(const char& other) { //копирование матрицы и запись в копию суммы двух матриц
        char result(*this);
        for (int i = 0; i < other.size(); ++i) {
          result.at(i) = this->at(i);
        }
        return result;
    }

    ~String() {
        for (int i = 0; i < rows; ++i) {
            delete[] matrix[i];
        }
        delete[] matrix;
    }*/
};

int main()
{
    const char str {"Mira"};
    String S(str);
    std::cout << S << std::endl;
}
