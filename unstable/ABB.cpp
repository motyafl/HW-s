#include <iostream>
#include <iomanip>
int userQuestion()
{
	std::string ask;
	std::cout << "Do you want to stop? ";
	std::cin >> ask;
	if (ask == "Y" or ask == "y") return 1;
	else return 0;
}

int main()
{
	double sum = 0;
	int counter = 0;
	while(true)
	{
		double num;
		std::cout << "Enter a number: ";
		std::cin >> num;
		sum += num;
		counter += 1;
		bool a = userQuestion();
		if (a == 1) 
		{
			std::cout << std::fixed << std::setprecision(4) << sum << "\n" << sum/counter;
			break;
		}
	}

}
