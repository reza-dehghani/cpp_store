#include "shop.h"

void shop::printproduct(){
	for (int i = 0; i < products.size(); i++)
	products[i].print();
}
void shop::printcustomern(vector <normal> n) {
	for (int i = 0; i < n.size(); i++)
		n[i].print();
}
void shop::vcustomerprint(vector <vip> v) {
	for (int i = 0; i < v.size(); i++)
		v[i].print();
}
void shop::buyprintfirst(vector<pair<buy, vector<product>>> b) {
	for (int i = 0; i < b.size(); i++)
	{
		b[i].first.printbuy();
	}
}
void shop::buyprintsec(vector<pair<buy, vector<product>>> b,int  bc) {
	for (int i = 0; i < b[bc].second.size(); i++)
		b[bc].second[i].print();
}
void shop::saleprint(vector <vector <product>> sl) {
	for (int i = 0; i < sl.size(); i++)
		for (int j = 0; j<sl[i].size(); j++)
			sl[i][j].print();
}
shop::shop() {}