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
            throw std::out_of_range("Индекс заходит за границы строки");
        
    	return str[index];
    }

    const char& operator[](size_t index) const {
	if (index < 0 || index >= size())
            throw std::out_of_range("Индекс заходит за границы строки");
        
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

int String::objCount = 0;

int main()
{
    setlocale(LC_ALL, "");
    const char* str {"Hello"};
    String S(str);
    const char* aStr {"World"};
    S.append(aStr);
    for(int i=0; i < S.size(); i++) {
	    std::cout << S[i];
    }
    std::cout << std::endl;
    std::cout << "Количество созданных объектов: " << String::getObjectCount() << std::endl;

    String S1(std::move(S));
    const char e = '!';
    S1.append(e);
    for(int i=0; i < S1.size(); i++) {
	    std::cout << S1[i];
    }
    std::cout << std::endl;
    const char s = 'l';
    int symb = S1.nSymbol(s);
    std::cout << "Количество символов " << s << ": " << symb << std::endl;
}
