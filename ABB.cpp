#include <iostream>
#include <iomanip>
#include <string>
double userInput()
{  
	std::char input;
	std::wcout << L"Введите число: ";
	std::getline(std::cin, input);	

	try {
		return std::stod(input);  // convert string to doubl
	}
	catch (const std::invalid_argument&) {
		std::wcout << L"Ошибка: введено не число, попробуйте еще раз.\n";
		return userInput();  // ask again
	}
}
bool userQuestion()
{
	std::string input[50];
	std::wcout << L"Завершить ввод? (y/Y - да): ";
	std::getline(std::cin, input);

	if (!input.empty() && (input[0] == 'y' || input[0] == 'Y')) 
		return true;
	return false;
}

int main()
{	
	std::setlocale(LC_ALL, "");
	double sum = 0;
	int counter = 0;
	while (true) {
		double num = userInput();
		sum += num;
		counter++;
		if (userQuestion()) {
			std::wcout << std::fixed << std::setprecision(4) << L"Сумма чисел: "<< sum << L"\nСреднее арифметическое: " << sum/counter << "\n";
			break;
		}
	}

}
