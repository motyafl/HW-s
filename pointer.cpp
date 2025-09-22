#include <iostream>
int loop(int(&refArr)[], int &refNum, int &refCout)
{
	
	for (int i : refArr) {
		std::cout << i << '\n' << std::endl;
	}
	std::cout << refNum << '\n' << refCout << '\n' << std::endl;
	return 0;
}
int main()
{
	int arr[3] = {1, 2, 3};
	int number = 10;
	int count = 5;
	int &coutRef = count; //reference
	int *pN = &number; //pointer
	int *pArr = arr; //pointer to the array
	int *&refpN = pN; //pointer to the pointer 
	//refpN = pArr; //repoint the pointer to the pointer
	//refpN = &count;
	std::cout << number << '\n' << *pN << '\n' << refpN << '\n' << count << '\n' << coutRef << '\n' << std::endl;

	loop(arr, number, count);
}
