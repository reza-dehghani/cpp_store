#pragma once
#include <vector>
#include "product.h"
#include "person.h"
#include "buy.h"

class shop {
	vector <product> products;
	vector <normal> normals;
	vector <vip> vips;
	public:
		shop();
		shop(vector<product> p){ products = p; }
		void ncustomer(vector <normal> n) { normals = n; }
		void vcustomer(vector <vip> v) { vips = v; }
		void printproduct();
		void printcustomern(vector <normal> n);
		void vcustomerprint(vector <vip> v);
		void buyprintfirst(vector<pair<buy, vector<product>>> b);
		void buyprintsec(vector<pair<buy, vector<product>>> b, int  bc);
		void saleprint(vector <vector <product>> sl);
};