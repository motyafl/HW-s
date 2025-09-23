#include <iostream>
double func(double x)
{
	double f;
	f = x*x-10;
	return f;
}

int main()
{		
	double a = 0;
	double b = 10;
	double eps = 0.000001;
	double xt;
	double dx;
	while(abs(b - a) > eps) {
		dx = (b - a)/2;
		xt = a + dx;
		if (func(a) * func(xt) < 0) {
			b = xt;
		}
		else a = xt;
	}
	std::cout << xt << '\n' << std::endl;
}
