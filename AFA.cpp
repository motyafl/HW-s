#include <iostream>
#include <stdexcept>
#include <cstring>
class String {
	char* str;
	static int objCount; 
	int counter = 0;
  public:
    String(const char* line) { //конструктор
	++objCount;
	size_t len = std::strlen(line);
        str = new char[len+1];
	for (int i = 0; i < len; ++i)
            str[i] = line[i];

    }
    String(const String& other) { //копирующий конструктор
	++objCount;
	size_t len = other.size();
        str = new char[len+1];
	for (int i = 0; i < len; ++i)
            str[i] = other[i]; 
    }

    String(String&& obj) {
        str = obj.str;        
        obj.str = nullptr;    
    }

    char& operator[](size_t index) {
	if (index < 0 || index >= size())
            throw std::out_of_range("String index out of range");
        
    	return str[index];
    }

    const char& operator[](size_t index) const {
	if (index < 0 || index >= size())
            throw std::out_of_range("String index out of range");
        
    	return str[index];
    }

    size_t size() const {
        return std::strlen(str);
    }
    void append(const char* line) {
	size_t len = std::strlen(line);
	size_t lenOrig = size();
	char* NewS = new char[len+lenOrig+1];

	int k {0};
	for (int i = 0; i < lenOrig; ++i) {
            NewS[i] = str[i];
	    k = i;
	}
	for (int i = 0; i < len+lenOrig; i++) {
	    k++;
	    NewS[k] = line[i];
	}


	
	/*
	std::strcpy(NewS, str);

        // Copy new string
        std::strcpy(NewS + lenOrig, line);
	*/
	delete[] str;
	str = NewS;
    }

    void append(const char symb) {
	size_t lenOrig = size();
	char* NewS = new char[lenOrig+2];

	int k {0};
	for (int i = 0; i < lenOrig; ++i) {
            NewS[i] = str[i];
	    k = i;
	}
	NewS[k+1] = symb;
	delete[] str;
	str = NewS;
    
    }

    int nSymbol(const char letter, int n = 0) {
	if (str[n] == '\0')
		return counter;
	if (str[n] == letter) {
		counter++;
		return nSymbol(letter, n+1);
	}
	else if (str[n] != letter) {
		return nSymbol(letter, n+1);
	}
	return n;
    }

    const char* c_str() const {
    	return str;
    }


    static int getObjectCount() {
	    return objCount;
    }

    ~String() {
        delete[] str;
    }
};
/*
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
    
    int String::objCount = 0;

int main()
{
    const char* str {"Mira"};
    String S(str);
    String F("Miai");
    String S1(S);
    String S2(std::move(F));
    const char* love {"LoveU"};
    S.append(love);
    for(int i=0; i < S.size(); i++) {
	    std::cout << S[i] << std::endl;
    }
    int count = String::getObjectCount();
    std::cout << count << std::endl;

    const char e = 'i';
    int symb = S2.nSymbol(e);
    std::cout << symb << std::endl;
}
