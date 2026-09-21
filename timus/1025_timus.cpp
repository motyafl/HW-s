             #include <iostream>
          #include <algorithm>
    	using namespace std;
      int main()<%
    int s;cin>>s;
   int*a=new 
  int[s],                           /**/        /**/
 p=s,*u=a,                       /*#####*/   /*#####*/
*o=a,sn{},                         /**/        /**/
 l=s/2+1;
  while(p--)
   cin>>*u++;
    sort(a,a+s);
      while(l--)sn+=*o++
       /2+1;cout<<sn<<endl;%>
         /*i_love_c_plus_plus*/


// ---------- Unobfuscated code ---------//

/*
#include <iostream>
#include <algorithm>
int main() {
	int s; cin >> s; //input the size of the array
	int *a = new int[s];
	int p=s, *u=a, *o=a, l=s/2 + 1; //variables to shorten the programm
	int sn{}; //variable to count the needed party members
	
	while( p-- ) { //input an array
		cin >> *(u++); 
		//use the pointer then increment it
	}

	sort(a, a+s); //sort an array
	
	while( l-- ) {
		sn += *(o++)/2 + 1; //get the halft+1 party members
	}
	cout << sn << endl;
}
*/
