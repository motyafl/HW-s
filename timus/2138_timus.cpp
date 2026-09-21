#include <iostream>
using namespace std;

int main() {
	long long int divs[4] = {256*256*256,256*256,256,1};
	int temp[4] = {};
	long long n, ans{}, *d = divs;
	int o=4, *p=temp;
	char no_need[4];

	cin >> no_need; // technically we dont need to \
					// know what computer is it
	cin >> n;

	for ( int i = 0; i < 3; i++ ) {
		while( n >= divs[i] ) {
			n -= divs[i];
			++temp[i];
		}
	}
	temp[3] = n;

	for ( int i = 3; i > -1; i-- ) {
			ans += temp[i] * (*d++);
	}

	//while(o--) cout<<*p++<<" ";cout<<endl;

	cout << ans << endl;

}
