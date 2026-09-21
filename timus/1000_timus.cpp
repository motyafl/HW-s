#include <iostream>

class nUmBeR {
private:
	int value;
public:
	nUmBeR( int val ) : value{val} {};

	int get_val() const { return value; }

	friend std::istream& operator>>(std::istream& input, nUmBeR& n) {
		input >> n.value;
		return input;
	}

	int operator+(const nUmBeR& other) const {
		return value + other.get_val();
	}

	~nUmBeR() {}
};

int main() 
{
	nUmBeR a(0), b(0);
	std::cin >> a >> b;
	int c = a + b;
	std::cout << c << std::endl;
}
