#include "person.h"
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;
void person::add(string n, string ph) {
	name = n;
	phone = ph;
	}
void person::print(){
	cout << left << "Name: " << setw(16) << name << "\tPhone number: " << setw(12) << phone << endl;
}
void normal::setnorm(bool a) {
	isnorm = a;
}
void vip::setvip(bool a) {
	isvip = a;
}