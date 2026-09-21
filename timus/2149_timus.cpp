#include<iostream>
#include<bitset>

int main() {

int n;
char arr[500];

// -- Producing a binary number from how pigeons head is pointed -- //

std::cin >> n;
std::cin >> arr;
std::cin.ignore();

int c=n/2, k=n/2, b=n-1;
std::bitset<100> ar{};
/*
   where c and k is for produing the masks 0011 and 0101 respectively
   b is for bit setting in a binary number ar to turn ><<> into  1001
*/


for( char i : arr ) {
    switch (i) {
        case 62: ar.set(b);b--;break;
        case 60: b--;break;
    } // bits are set from right to left just like the char arr[] is read
}

//std::cout << std::bitset<16>(ar) << std::endl;

// ------------- The working part of the algorithm ---------------- //

std::bitset<100> m1 = 0, m3 = 0;

while (c--) {
    m1 = (m1 << 1) | std::bitset<100>(1); // equivalent to m1 = m1 * 1 + 1
}

while (k--) {
    m3 = (m3 << 2) | std::bitset<100>(1); // equivalent to m3 = m3 * 4 + 1
}

// Flipping only first n bits
std::bitset<100> total_mask;
for (int i = 0; i < n; i++) total_mask.set(i);

std::bitset<100> m2 = total_mask ^ m1;
std::bitset<100> m4 = total_mask ^ m3;

int c1 = (m1 ^ ar).count();
int c2 = (m2 ^ ar).count();
int c3 = (m3 ^ ar).count();
int c4 = (m4 ^ ar).count();

std::cout << ( ((c1 >= c2) ? c2 : c1) >= ((c3 >= c4) ? c4 : c3) ?
               ((c3 >= c4) ? c4 : c3) : ((c1 >= c2) ? c2 : c1) ) << std::endl;

/* Explaining the trenary operators:

// ----- finding the lowest possible mask -----//

if (c1 >= c2) { c1 = c2; }

if (c3 >= c4) { c3 = c4; }

if (c1 >= c3) { c1 = c3; }

cout << c1.count() << endl;

*/
/* Explaining how masks are produced:

    If we start from m = 0 and do m = m*2 + 1
    We will get this numbers {1, 3, 7, 15}
    and patterns {01, 0011, 000111, 00001111}

    If we start from m = 0 and do m = m*4 + 1
    We will get this numbers {1, 5, 21, 85}
    and patterns {01, 0101, 010101, 01010101}

    The inverse masks are produced by m^(1 << n)-1,
    flipping only first n bits
*/

}
