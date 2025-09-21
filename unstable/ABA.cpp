#include <iostream>
int incrBrightness(int alpha, int red, int green, int blue)
{
	red = red*1.1;
	green = green*1.1;
	blue = blue*1.1;
	if (red > 255) red = 255;
	if (green > 255) green = 255;
	if (blue > 255) blue = 255;
	std::wcout << std::dec << L"Яркость была увеличена на 10%. Новые значения компонентов:\nA = " << alpha << "\n" << "R = " << red << "\n" << "G = " << green << "\n" << "B = " << blue << "\n";
	return 0;
}

int main()
{
	std::setlocale(LC_ALL, "");
	uint32_t num;
	std::wcout << L"Введите 32-битное число цвета в шестнадцатеричном формате: ";
	std::cin >> std::hex >> num;

	int mask = 0x000000FF;
	int mA = (num>>24) & mask;
	int mR = (num>>16) & mask;
	int mG = (num>>8) & mask;
	int mB = num & mask;
	std::wcout << std::dec << L"Введенные компоненты в десятичном формате: \nA = " << mA << "\nR = " << mR << "\nG = " << mG << "\nB = " << mB << "\n";
	std::wcout << std::hex << L"В шетснадцатеричном: \nA = 0x" << mA << "\nR = 0x" << mR << "\n" << "G = 0x" << mG << "\nB = 0x" << mB << "\n";

	if (mA < 128)
		std::wcout << L"Цвет полупрозрачный.\n";
	else
		std::wcout << L"Цвет непрозрачный.\n";

	incrBrightness(mA, mR, mG, mB);
}
