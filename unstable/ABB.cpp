#include <iostream>
#include <iomanip>
#include <string>
int userInput()
{
	double number = 0;
	std::string input = "";
	std::wcout << L"Введите число: ";
	std::getline(std::cin, input); 
	number = std::stod(input);
	return number;
}
int userQuestion()
{
	char ask;
	std::wcout << L"Завершить ввод?(y/Y - да) ";
	std::cin >> ask;
	if (ask == 121 or ask == 89) return 1;
	else return 0;
}

int main()
{
	std::setlocale(LC_ALL, "");
	double sum = 0;
	int counter = 0;
	while(true)
	{
		double num = userInput();
		sum += num;
		counter += 1;
		bool a = userQuestion();
		if (a == 1) 
		{
			std::wcout << std::fixed << std::setprecision(4) << L"Сумма чисел: "<< sum << L"\nСреднее арифметическое: " << sum/counter << "\n";
			break;
		}
	}

}
