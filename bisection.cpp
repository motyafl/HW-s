#include <iostream>
#include <cmath>
double func(double x)
{
	double f;
	f = x+20;
	return f;
}
void loop(double &a, double &b,double xt)
{
    if (func(a) * func(xt) < 0) {
			b = xt;
		}
    else {
        a = xt;
    }
}

int main()
{		
	double a = -10;
	double b = 0;
	double eps = 0.001;
	double xt{};
	double dx{};
	while(abs(b - a) > eps) {
		dx = (b - a)/2;
		xt = a + dx;
        if (func(a) == 0) {
            xt = a;
            break;
        }
        else if (func(b) == 0) {
            xt = b;
            break;
        }
        else loop(a, b, xt);
	}
	std::cout << xt << '\n' << std::endl;
}
