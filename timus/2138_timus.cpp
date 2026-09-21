#include <iostream>

#include <cmath>
using namespace std;

int main() {
int divs[4] = {256*256*256,256*256,256,0};
int temp[4] = {};
int nums[5] = {64,66,16,0};
long long n = 1078071040;// 16777216;
int o=4, k=4, *p=temp, *r=nums;

for ( int i = 0; i < 3; i++ ) {
	while( n >= divs[i] ) {
		n -= divs[i];
		++temp[i];
	}
	cout << n << endl;
}

temp[3] = n;

/*
int Q = 0;
for ( int i = 0; i < 4; i++ ) {
	while(temp[i] > 0) {
		temp[4]--;
		Q += divs[i]*pow(10, temp[4]);
		temp[i]--;
	}
}
*/

//cout << (n==1 ? "Divisidable!" : "-1") << endl;
while(o--) cout<<*p++<<" ";cout<<endl;
while(k--) cout<<*r++<<" ";cout<<endl;

}
