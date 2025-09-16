#include <iostream>
int incrBrightness(int alpha, int red, int green, int blue)
{
	red = red*1.1;
	green = green*1.1;
	blue = blue*1.1;
	if (red > 255) red = 255;
	if (green > 255) green = 255;
	if (blue > 255) blue = 255;
	std::cout << std::dec << "Brightness was increased by 10%. New values are: \n A = " << alpha << "\n" << "R = " << red << "\n" << "G = " << green << "\n" << "B = " << blue << "\n";
	return 0;
}

int main()
{
	uint32_t num = 0x80FFACFF;
	int mask = 0x000000FF;
	int mA = (num>>24) & mask;
	int mR = (num>>16) & mask;
	int mG = (num>>8) & mask;
	int mB = num & mask;
	std::cout << std::dec << "A = " << mA << "\n" << "R = " << mR << "\n" << "G = " << mG << "\n" << "B = " << mB << "\n";
	std::cout << std::hex << "A = 0x" << mA << "\n" << "R = 0x" << mR << "\n" << "G = 0x" << mG << "\n" << "B = 0x" << mB << "\n";

	if (mA < 128)
		std::cout << "Colour is half alpha";
	else
		std::cout << "Colour is not alpha";

	incrBrightness(mA, mR, mG, mB);
/*
	for (int i = 0xFF; i != i<<24; i <<= 8)
	{
		//std::cout << std::hex << i << "\n";
		int res = num&i;
		std::cout << std::hex << i << "\n";
	}
	*/
	/*
	int mask = 0xFF;
	mask <<= 8;
	num = mask & num;
	num >>= 8;
	std::cout << std::hex << mask << "\n";
	std::cout << std::dec << num << "\n0x" << std::hex << num << std::endl;
	*/
}
