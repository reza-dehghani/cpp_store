#pragma once
#include <string>
using namespace std;
class buy {
private:
	string name;
	string phone;
	int buycode;
	long float allprice;
public:
	void addbuyinfo(int bc, string n, string ph, long float pall);
	void printbuy();
	string get_name() { return name; };
	string get_phone() { return phone; };
	int get_buycode() { return buycode; };
	long float get_allprice() { return allprice; };

};