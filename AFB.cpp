#include <iostream>
#include <fstream>
#include <sstream>

int main()
{
	std::ifstream in("file.txt");
	std::string line;
	int i = 6;
	uint32_t n = 53738;
	std::cout << std::bitset<32>(n).to_string() << '\n';
	n >>= (i-1);
	uint32_t no = n&1;
	std::cout << std::bitset<32>(no).to_string() << '\n';

	while( getline(in, line)) {
		std::stringstream is(line);
 		uint32_t number{static_cast<uint32_t>(std::stoul(line))};
		std::cout << number << '\n';
	}
}
