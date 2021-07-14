#include "product.h"
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;
void product::addproduct(unsigned long long int qr, string n, unsigned long long int p, unsigned long long int c){
	unsigned long long int def = 1;
	qrcode = (qr<0 || qr==0) ? def : qr;
	name = n;
	price = (p<0 || qr==0) ? def : p;
	count = (c<0) ? def : c;
}
/*
product::product(long long qrcode, char name, long long price, long long count) {
	addproduct(qrcode, name,price, count);
}

ostream &operator<<(ostream& output, const product &p) {
*/
void product::print()
{
	cout << left << "QrCode: "<< setw(12) << qrcode << "Name: " << setw(30) << name << setw(7) << "Price: " << setw(12) << price << setw(7) << "Number: " << setw(12) << count
		<< endl;
}
void product::ch_count(int c) {
		count = c;
}
void product::ch_price(int p) {
	price = p;
}
unsigned long long int product::remaincount(unsigned long long int qrcode, unsigned long long int count, int number)
{
	if (count >= number) {
		count = count - number;
		return count;
	}
	if (count < number) {
		cout <<"\nRemein count of product: " << count<<"\n";
	}
}
void product::setqrcode(int qr){
	qrcode = qr;
}
void product::setname(string n) {
	name = n;
}
void product::setprice(int p) {
	price = p;
}
void product::setcount(int c) {
	count = c;
}