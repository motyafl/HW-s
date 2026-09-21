#include <iostream>
#include <cmath>

int main() {
        int divs[8] = {2,3,4,5,6,7,8,9};
        long long int temp[9] = {};
        long long int n, o=5, *p=temp;

        std::cin >> n;
        long long int Q {}; 
        
        bool is_zero = (n == 0) ? true : false;

        for ( int i = 0; i < 8; i++) {
                while( n%divs[7-i] == 0 && n != 0 ) {
                        n /= divs[7-i];
                        temp[i]++;
                        temp[8]++;
                }
        }

        if (temp[8] == 0 && n == 1) Q++;
        if (n == 0) { Q = 10; n++; }

        //while(o--) std::cout<<*p++<<" ";std::cout<<std::endl;
        // ------ Converting from array to a number ------ //

        for ( int i = 0; i < 8; i++ ) {
                while(temp[7-i] > 0) {
                        temp[8]--;
                        Q += divs[i] * std::pow(10, temp[8]);
                        temp[7-i]--;
                }
        }

	std::cout << (n==1 ? Q : -1) << std::endl;
}
