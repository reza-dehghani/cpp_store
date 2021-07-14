#pragma once
#include <iostream>
#include <string>
using namespace std;
class product {
public:
	void addproduct(unsigned long long int qr, string n, unsigned long long int p, unsigned long long int c);
	void print();
	int get_qrcode(){ return qrcode; }
	string get_name(){ return name; }
	unsigned long long int get_price() { return price; }
	unsigned long long int remaincount(unsigned long long int qrcode, unsigned long long int count, int number);
	unsigned long long int get_count() { return count; }
	void ch_count(int c);
	void ch_price(int p);
	void setqrcode(int);
	void setname(string);
	void setprice(int);
	void setcount(int);
private:
	unsigned long long int qrcode;
	string name;
	unsigned long long int price;
	unsigned long long int count;
};