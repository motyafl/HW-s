#include <iostream>
#include <fstream>
#include <sstream>
#include <bitset>
#include <memory>

uint32_t checkBit(uint32_t number, int bitN) {
	uint32_t result {};
	number >>= (bitN-1);
	result = number&1;
	return result;
}
uint32_t setBit(uint32_t number, int bitN) {
	if (checkBit(number, bitN) == 1) return number;
	int mask = 1;
	mask <<= (bitN-1);
	number = number^mask;
	return number;
}

uint32_t resetBit(uint32_t number, int bitN) {
	if (checkBit(number, bitN) == 0) return number;
	int mask = 1;
	mask <<= (bitN-1);
	number = number^mask;
	return number;
}

int countBit(uint32_t number, int count, int stop) {
	if (stop == 32)
		return count;
	if (number&1 == 1) {
		stop++;
		count++;
		return countBit(number>>=1, count, stop);
	}
	else {
		stop++;
		return countBit(number>>=1, count, stop);
	}
}

int fullBit(uint32_t(*checkBit)(uint32_t, int), int* p, int n, int index) {
	for (int i = 0; i < n; i++) {
		uint32_t number = p[i];
		std::cout << number << std::endl;
		std::cout << std::bitset<32>(number).to_string() << '\n';
		std::cout << checkBit(number, index) << std::endl;
	}
	return -1;
}

int main()
{
	std::setlocale(LC_ALL, "");

	std::string line;
	std::ifstream in("file.txt"); 
	if (!in)
        	throw std::runtime_error("Не удалось открыть файл");

	unsigned f = 3;
	uint32_t number;
	auto ptr {std::make_unique<int[]>(f)};
	int n = 0;
	while(getline(in, line)) {
		number = static_cast<uint32_t>(std::stoul(line));
		std::stringstream is(line);
		ptr[n] = number;
		n++;
	}
	
	int bitN = 1; //индекс бита который будем проверять или заменять
	for (int i = 0; i < n; i++) { 
		number = ptr[i];
		std::cout << "Ваше число: " << number << std::endl;
		std::cout << "Ваше число в двоичной записи:" << '\n' << std::bitset<32>(number).to_string() << std::endl;
		number = setBit(number, bitN); //установка бита по индексу 
		std::cout << "Итоговое число: " << number << std::endl;
		std::cout << "Итоговое число в двоичной записи:" << '\n' << std::bitset<32>(number).to_string() << '\n' << std::endl;
		/*number = resetBit(number, bitN); 
		std::cout << number << std::endl;
		std::cout << std::bitset<32>(number).to_string() << '\n';
		int count = 0;
		int stop = 1;
		int times = countBit(number, count, stop);
		std::cout << times << std::endl << std::endl;*/
	}
	fullBit(checkBit, ptr.get(), n, bitN); //проверка всех замененных битов
}
