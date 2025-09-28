#include <iostream>
#include <string>
/*int strSize () {
	char str = {f; g; h}
	for(str; str 
}*/
int main ()
{
	char str[100] {};
	int vows {0};//счетчик гласных
	int cons {0};//счетчик согласных
	std::cin.getline(str, 100);
	//char *pStr = str;
	//std::cout << *pStr << std::endl;
	for(char *pStr = str; *pStr != '\0'; pStr++) {
		if (*pStr >= 65 && *pStr <= 90) {
			if (*pStr == 65 || *pStr == 69 || *pStr == 73 || *pStr == 79 || *pStr == 85 || *pStr == 89) {
				*pStr = static_cast<char>(*pStr + 1);
				vows++;
			}

			else {
				*pStr = static_cast<char>(*pStr - 1);
				cons ++;
			}
		}

		else if (*pStr >= 97 && *pStr <= 122) {
			if (*pStr == 97 || *pStr == 101 || *pStr == 105 || *pStr == 107 || *pStr == 111 || *pStr == 117) {
				*pStr = static_cast<char> (*pStr + 1);
				vows++;
			}

			else {
				*pStr = static_cast<char> (*pStr - 1);
				cons ++;
			}
		}

		else continue;
	}

	std::cout << str << std::endl;


	/*for(int i = 0; i < 100; i++) {
		if (*pStr == '\0') break;
		std::cout << *pStr << std::endl;

		pStr ++;
	}*/
	
}
