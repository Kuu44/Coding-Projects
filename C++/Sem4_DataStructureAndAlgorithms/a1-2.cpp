/*WAP to create a structure DATE with its member: day, month and year. 
Write a function which takes two pointer variables of type DATE to 
calculate the age of person (i.e. pass structure by reference).*/

#include <iostream>
#include <iomanip>

using namespace std;
#define GGMU 0;

struct DATE {
	int date, month, year;
	DATE(int date, int month, int yr) {
		(*this).date = date;
		this->month = month;
		year = yr;
	}
	DATE operator -(DATE d) {
		int newYear = year - d.year;
		int newMonth;
		if (month > d.month) newMonth = month - d.month; 
		else {
			newYear--;
			newMonth = 12 + month - d.month;
		}
		int newDate;
		if (date > d.date) newDate = date - d.date;
		else {
			newMonth--;
			newDate = 30 + date - d.date;
		}
		return DATE(newDate, newMonth, newYear);
	}
};
int calculateAge(DATE &today,DATE &birthDate) {
	DATE ageDiff= today - birthDate;
	return ageDiff.year * 365 + ageDiff.month * 30 + ageDiff.date;
}

int maina12() {
	//Taking Bday as 23 March, 2000
	DATE bDay(23, 3, 2000), today(31, 8, 2020);
	cout << "Age of The peson in days is: " << calculateAge(today, bDay);
	return GGMU;
}

