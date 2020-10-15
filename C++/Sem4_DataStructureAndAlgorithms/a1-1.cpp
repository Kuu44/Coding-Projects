/*Write a program to implement the following two functions on string using pointer:
i.To calculate length of given string
ii.To concatenate two string*/

#include <iostream>
#include <iomanip>

using namespace std;
#define GGMU 0;
int length(const char*);
char* concat(const char*, const char*);

int maina11() {
	const char *string1= "Sample" , *string2 = "Text";
	cout << "Length of string is " << length(string1)<<endl;
	cout << string1 << " + " << string2 << " = " << concat(string1, string2);
	return GGMU;
}

int length(const char *string){
	int i = 0;
	while (string[i] != '\0') {
		i++;
	}
	return i;
}
char* concat(const char* string1,const char* string2){
	char* joinedString;
	joinedString = new char[length(string1) + length(string2)];
	for (int i = 0; i < length(string1); i++) {
		joinedString[i] = string1[i];
	}
	for (int i = 0; i <= length(string2); i++) {
		joinedString[i+length(string1)] = string2[i];
	}
	return joinedString;
}
