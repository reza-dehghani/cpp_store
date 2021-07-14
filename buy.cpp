#include "buy.h"
#include "product.h"
#include <iostream>
#include <iomanip>
using namespace std;
void buy::addbuyinfo(int bc, string n, string ph, long float pall) {
	buycode = bc;
	name = n;
	phone = ph;
	allprice = pall;
}
void buy::printbuy(){
	cout << left << "BuyCode= " << setw(10) << buycode << "\tCustomer Name= " << setw(15) << name << "\tCustomer phone= " << setw(12) << phone << "\tAll Price= " << setw(20) << allprice << endl;
}
/*
void buy::printbuyinfo(int s) {
	for (int i = 0; i < s; i++)
	{
		cout<<""
	}
}*/