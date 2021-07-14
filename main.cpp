#include "shop.h"
#include "product.h"
#include "buy.h"
#include "person.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>
#include <cstdlib>

using namespace std;

int linesearch(vector <product> products, int len, int what) {
	int i;
	for (i = 0; i < len; i++)
		if (products[i].get_qrcode() == what)
			return i;
	return -1;
}

int linesearch(vector <product> products, int len, string what) {
	int i;
	for (i = 0; i < len; i++)
		if (products[i].get_name() == what)
			return i;
	return -1;
}

long long int get_int(char *message)
{
	long long int out;
	string in;
	int i = 0;
	while (true)
	{
		if (i>0)
			cout << message;
		i++;
		getline(cin, in);
		stringstream ss(in);
		if ((ss >> out) && !(ss >> in)) 
			if (out>0)
				return out;
			cin.clear();
			//cerr << "\nInvalid input. Please try again.\n";
	}
}
void readproduct();
void readperson();
void readbuy();
void autosave();
void personsave();
void buysave();
void outputline(unsigned long long int qrcode, const string name, unsigned long long int price, unsigned long long int count);
vector <product> products;
vector <normal> normals;
vector <vip> vips;
vector<pair<buy, vector<product>>> buys;
vector <product> buylist;
int buycode = -1;
void main() {
	cout << fixed << setprecision(3);
	unsigned long long int qrcode, price, count;
	string name;
	int long selector = 0;
	product pros;
	long int find = -1;
	normal norms;
	vip vis;
	string phone;
	int number = 0;
	int i = 0;
	int pcount = 0;
	bool setperson;
	bool flag = 0;
	buy purchase;
	product by;
	long float allprice = 0;
	string pname;
	bool notf = 1;
	bool isvip = 0;
	int select = 0;
	char ch = 'n';
	buy str;
	vector <vector <product>> salelist;
	vector <buy> buyer;
	cout << "Welcome to The <Birjand UT Store>"
		"\nmain menu\n"
		"Please Select an option and then press enter\n"
		"1. Add product\n2. Change number or price of products\n3. Delete product\n4. Add Customer\n5. Delete Customer\n6. Buy\n7. Reports\n8. Exit\n";
	readproduct();
	readperson();
	readbuy();
	while ((selector != 8) && (cin >> selector)) {
		switch (selector)
		{
		case 0:
		{
			system("cls");
			cout << "main menu\n"
				"Please Select an option and then press enter\n"
				"1. Add product\n2. Change number or price of products\n3. Delete product\n4. Add Customer\n5. Delete Customer\n6. Buy\n7. Reports\n8. Exit\n";
		
			break;
		}
		case 1:
		{
			system("cls");
			fstream file("product.txt", ios::app);
			while (!file) {
				fstream file("product.txt", ios::in);
				if (!file) {
					cerr << "File product.txt not opened! first create it";
					cin.get();
					exit(1);
				}
			}
			cout << "Enter qrcode: ";
			cin.ignore();
			qrcode = get_int("Please enter an enteger(more than 0): ");
			cout << "\nEnter price(Rial) then Enter Number: \n";
			while (cin >> price >> count) {
				cout << "Enter Name: ";
				cin.ignore();
				getline(cin,name);
				find = linesearch(products, products.size(), qrcode);
				while (find != -1)
				{
					cout << "A product with this qrcode was found please enter another Qrcode or delete it from option 3";
					qrcode = get_int("Please enter an enteger(more than 0): ");
					find = linesearch(products, products.size(), qrcode);
					if (find == -1) {
						cout << "Enter Name: ";
						cin.ignore();
						getline(cin, name);
						cin >> price >> count;
					}
				}
				pros.addproduct(qrcode, name, price, count);
				products.push_back(pros);
				for (i = 0; i < name.size(); i++) {
					if (name[i] == ' ')
						name[i] = '*';
				}
				file << qrcode << ' ' << name << ' ' << price << ' ' << count << endl;
				cout << "\nProduct succussfully added\n";
				cout << "\n Please Enter 0 for go to the MENU: ";
				break;
			}
		
			file.close();
			shop obj(products);
			break;
		}
		case 2:
		{
			system("cls");
			cout << "Change price and count of product Menu:\n";
			cout << "Please enter the Qrcode: ";
			cin.ignore();
			qrcode = get_int("Please enter an enteger(more than 0): ");
			if (products.size() == 0) {
				cout << "Qrcode not found because there isn't any product!\n";
				continue;
			}
			find = linesearch(products, products.size(), qrcode);
			if (find != -1) {
				cout << products[find].get_qrcode();
				cout << endl << "Please Select what information want to change\n"
					"1. change number of product\n"
					"2. change price of product\n";
				cin >> selector;
				if (selector == 1) {
					cout << "Enter new value: ";
					cin >> pcount;
					products[find].ch_count(pcount);
					cout << "\nProduct count succussfully changed\n";
				}
				if (selector == 2) {
					cout << "Enter new value: ";
					cin >> price;
					products[find].ch_price(price);
					cout << "\nProduct price succussfully changed\n";

				}
				autosave();
			}
			if (find == -1)
				cout << "\nQrcode Not found!";
			cout << "\n Please Enter 0 for go to the MENU: ";
			break;
		}
		case 3:
		{
			system("cls");
			cout << "Delete product menu/nFor deleting product please select: \n"
				"1. Search Name of product and delete\n"
				"2. Search Qrcode and delete\n";
			cin >> selector;
			if (selector == 1)
			{
				cout << "Enter name: ";
				cin >> name;
				find = linesearch(products, products.size(), name);
				if (find != -1) {
					products.erase(products.begin() + find);
					cout << "successfully deleted!";
				}
				if (find == -1)
					cout << "Name of product not found!";
			}
			if (selector == 2)
			{
				cout << "Enter Qrcode: ";
				cin.ignore();
				qrcode = get_int("Please enter an enteger(more than 0): ");
				fstream file2("product.txt", ios::out | ios::in | ios::binary);
				if (products.size() == 0) {
					cout << "Qrcode not found because there isn't any product!\n";
					continue;
				}
				find = linesearch(products, products.size(), qrcode);
				if (find != -1) {
					products.erase(products.begin() + find);
					cout << "successfully deleted!\n";
				}
				if (find == -1) {
					cout << "\nQrcode not found!\n";
				}
			}
			autosave();
			cout << "\n Please Enter 0 for go to the MENU: ";
			break;
		}
		case 4: {
			system("cls");
			cout << "Select type of person\n"
				"1.normal\n"
				"2.VIP\n";
			cout << "Your select: ";
			cin >> selector;
			if (selector == 1)
			{
				fstream fp("person.txt", ios::app);
				if (!fp) {
					cerr << "File not opened!";
					cin.get();
					exit(1);
				}
				cout << "Please enter Phone: ";
				while (cin >> phone) {
					cout << "Enter Name: ";
					cin.ignore();
					getline(cin, name);
					//cheaking phone
					while (phone.size() != 11 || phone.at(0) != 48) {
						cout << "Phone number must be 11 digit and start with 0 :) Please reenter phone number: ";
						cin >> phone;
					}
					if (phone.size() == 11 && phone.at(0) == 48) {
						norms.add(name, phone);
						normals.push_back(norms);
					}
					//repeated ph number
					for (int i = normals.size() - 2; i >= 0; i--) {
						if (phone == normals[i].get_phone()) {
							cout << "Phone number is repeated please first delete customer and then add it again!\n";
							normals.pop_back();
						}
					}

					for (int i = vips.size() - 1; i >= 0; i--) {
						if (phone == vips[i].get_phone()) {
							cout << "Phone number was in VIPS customers please first delete customer and then add it again!\n";
							normals.pop_back();
						}
					}
					for (i = 0; i < name.size(); i++) {
						if (name[i] == ' ')
							name[i] = '*';
					}
					norms.setnorm(0);
					setperson = 0;
					fp << setperson << ' ' << name << ' ' << phone << endl;
					break;
				}
				fp.close();
	}
			if (selector == 2)
			{
				fstream fp("person.txt", ios::app);
				if (!fp) {
					cerr << "File not opened!";
					cin.get();
					exit(1);
				}
				cout << "Please enter phone number: ";
				while (cin >> phone) {
					cout << "Please enter firstname & lastname: ";
					getline(cin, name);
				//cheaking phone
				while (phone.size() != 11 || phone.at(0) != 48) {
					cout << "Phone number must be 11 digit and start with 0 :) Please reenter phone number: ";
					cin >> phone;
				}
				if (phone.size() == 11 && phone.at(0) == 48) {
					vis.add(name, phone);
					vips.push_back(vis);
				}
				//repeated ph number
				for (int i = vips.size() - 2; i >= 0; i--) {
					if (phone == vips[i].get_phone()) {
						cout << "Phone number is repeated please first delete customer and then add it again!\n";
						vips.pop_back();
					}
				}

				for (int i = normals.size() - 1; i >= 0; i--) {
					if (phone == normals[i].get_phone()) {
						cout << "Phone number was in NORMAL customers please first delete customer and then add it again!\n";
						vips.pop_back();
					}
				}

				for (i = 0; i < name.size(); i++) {
					if (name[i] == ' ')
						name[i] = '*';
				}
				vis.setvip(1);
				setperson = 1;
				fp << setperson << ' ' << name << ' ' << phone << endl;


				break;
				}
				fp.close();
			}
			if (selector != 1 && selector != 2) {
				cout << "\nPlease type a number between 1 or 2\n";
			}
			cout << "\n Please Enter 0 for go to the MENU: ";
			break;
			break;
		}

		case 5:
		{
			system("cls");
			cout << "Please enter phone number for deleting: ";
				cin >> phone;
				for (int i = normals.size() - 1; i >= 0; i--) {
					for (int j = vips.size() - 1; j >= 0; j--) {
						if (phone == normals[i].get_phone()) {
							cout << "Customer deleted!\n";
							normals.erase(normals.begin() + i);
							flag = 1;
						}
						if (phone == vips[j].get_phone()) {
							cout << "Customer deleted!\n";
							vips.erase(vips.begin() + i);
							flag = 1;
						}
						if (flag != 1) {
							cout << "\nPhone number doesn't found, try again !EXIT!\n";
								break;
						}
					}
				}
				personsave();
				cout << "For going to MENU enter 0: ";
			break;
		}
		case 6:
		{
			system("cls");
			fstream buyinfo("buyinfo.txt", ios::app);
			if (!buyinfo) {
				cerr << "\nFile buyinfo.txt not opened! You must to first create it!\n";
				system("pause");
				cin.get();
				exit(1);
			}
			fstream buyist("buylist.txt", ios::app);
			if (!buyist) {
				cerr << "\nFile buylist.txt not opened! You must to first create it!\n";
				system("pause");
				cin.get();
				exit(1);
			}
			isvip = 0;
			notf = 1;
			qrcode = 1;
			allprice = 0;
			int g = buys.size() - 1;
			if (buys.size() != 0)
				buycode = buys[g].first.get_buycode();
			else
				buycode = -1;
			buylist.clear();
			char ch;
			cout << "Enter customer phone number: ";
			cin >> phone;
			for (int i = normals.size() - 1 ; i >=0 ; i--) {
				if (phone == normals[i].get_phone()) {
					phone = phone;
					pname = normals[i].get_name();
					notf = 0;
				}
			}
			for (int i = vips.size() - 1 ; i >= 0; i--) {
				if (phone == vips[i].get_phone()) {
					phone = phone;
					pname = vips[i].get_name();
					isvip = 1;
					notf = 0;
				}
			}

			if (notf != 0) {
				cout << "\nSorry Phone number doesn't saved, If Customer is new you must to first ADD information of customer and then return to this option\n";
				cout << "Enter 0 for goto the menu: ";
				break;
			}

			cout << "Please Enter Qrcode(s) and enter -1 after end: ";
			cin.ignore();
			while (qrcode != -1) {
				cout << "\nQrcode: ";
				cin >> qrcode;
				if (qrcode == -1)
					break;
				if (products.size() == 0) {
					cout << "Qrcode not found because there isn't any product! Enter another Qrcode or enter two 0 for exit\n";
					qrcode = -1;
					continue;
				}
				find = linesearch(products, products.size(), qrcode);
				if (find != -1) {
					count = products[find].get_count();
					cout << "Enter number of product: ";
					number = get_int("Please enter an enteger(more than 0): ");
					if (count < number) {
						cout << "\nAll Product counts end or maybe your cin number bigger than count of product!"
							"\nPlease add more number of product from 2 option\n Remaining Count: " << count;
						continue;
					}
					if (count >= number) {
						products[find].ch_count(pros.remaincount(qrcode, count, number));
					}
					allprice += number * products[find].get_price();
					name = products[find].get_name();
					price = products[find].get_price();
					by.addproduct(qrcode, name, price, number);
					buylist.push_back(by);
					//factor
					//write products
					for (int m = 0; m < name.size(); m++) {
						if (name[m] == ' ')
							name[m] = '*';
					}
				}
				if (find == -1) {
					cout << "Product Not found!";
				}
			}//while
			if (isvip == 1)				
				allprice = allprice - (allprice * 0.2);
			if (buylist.size() != 0) {
				buycode++;
				str.addbuyinfo(buycode, pname, phone, allprice);
				buys.push_back(make_pair(str, buylist));
				salelist.push_back(buylist);
				buyer.push_back(str);
				//write buys
				for (int m = 0; m < pname.size(); m++) {
					if (pname[m] == ' ')
						pname[m] = '*';
				}
				buyinfo << buycode << ' ' << pname << ' ' << phone << ' ' << allprice << endl;
				for (i = 0; i < buys[buycode].second.size(); i++) {
					qrcode = buys[buycode].second[i].get_qrcode();
					name = buys[buycode].second[i].get_name();
					for (int n = 0; n < name.size(); n++) {
						if (name[n] == ' ')
							name[n] = '*';
					}
					price = buys[buycode].second[i].get_price();
					number = buys[buycode].second[i].get_count();
					buyist << buycode << ' ' << qrcode << ' ' << name << ' ' << price << ' ' << number << endl;
				}
			}
			cout << "\nFor printing Factor Enter 5, else Enter 0 to go to MENU: ";
			cin >> select;
			if (select == 5) {
				cout << "\nBuyer info:\n";
				for (i = 0; i < buyer.size(); i++)
					buyer[i].printbuy();
				cout << "\nProduct list:\n";
				for (i = 0; i < buylist.size(); i++)
					buylist[i].print();
			}
			cin.get();
			buyinfo.close();
			buyist.close();
			autosave();
			cout << "For going to MENU enter 0: ";
			break;
		}
		case 7:
		{
			system("cls");
			cout << "Reports\n"
				"1. Product list\n"
				"2. Customer list\n"
				"3. Buys list\n"
				"4. Sale list\n";
			cin >> selector;
			if (selector == 1) {
				shop obj(products);
				obj.printproduct();
				if (products.size() == 0) {
					cout << "Products list is empty!";
				}
			}
			if (selector == 2) {
				if (normals.size() != 0)
				{
					cout << "\nNormal Customers\n";
					shop cn;
					cn.printcustomern(normals);
				}
				if (normals.size() == 0) {
					cout << "\nThere isn't Normal Customer now!\n";
				}
				if (vips.size() != 0) {
					cout << "\nVIP Customers\n";
					shop cv;
					cv.vcustomerprint(vips);
				}
				if (vips.size() == 0) {
					cout << "\nThere isn't VIP customer now!\n";
				}
			}
			if (selector == 3) {
				shop bp;
				if (buys.size() == 0) {
					cout << "\n Sorry Buy list is empty!";
					continue;
				}
				cout << "\nBuys:\n For more information cin 9 and then enter BuyCode of selected buy OR enter 10 for EXIT\n";
				bp.buyprintfirst(buys);
				cout << "Selector: ";
				cin >> select;
				if (select == 9) {
					cout << "BuyCode: ";
					cin >> buycode;
					shop bcs;
					bcs.buyprintsec(buys, buycode);
				}
				if (select != 9) {
					continue;
				}
			}
			if (selector == 4) {
				vector <product> p;
				fstream buyist2("buylist.txt", ios::in);
				if (!buyist2) {
					cerr << "\nFile buylist.txt not opened! You must to first create it!\n";
					system("pause");
					cin.get();
					exit(1);
				}
				while (buyist2 >> buycode >> qrcode >> name >> price >> number){
					for (int j = 0; j < name.size(); j++) {
						if (name[j] == '*')
							name[j] = ' ';
					}
					pros.addproduct(qrcode, name, price, number);
					p.push_back(pros);
			}
				buyist2.close();
				salelist.push_back(p);
				if (salelist.size() == 0)
					cout << "Sorry, Any product of store still not saled!";
				if (salelist.size() != 0) {
					shop sl;
					sl.saleprint(salelist);
				}
			}
				if (selector != 1 && selector != 2 && selector != 3 && selector != 4) {
					cout << "\n You must enter a number between (1-4)";
					continue;
				}
				cout << "For going to MENU enter two 0: ";
			break;
		}
		case 8:
		{
			system("cls");
			break;
		}
		default:
		{
			cout << "Please enter a number between (1-8)";
			break;
		}
		system("pause");
		}
	}
}
void autosave() {
	product pros;
	unsigned long long int qrcode, price, count;
	string name;
	fstream temp("temp.txt", ios::out);
	if (!temp) {
			cerr << "File temp.txt (file for save product.txt) not opened! You must to first create it!";
			system("pause");
			cin.get();
			exit(1);
	}
	for (int i=0 ; i<products.size() ; i++ ){		
		qrcode = products[i].get_qrcode();
		name = products[i].get_name();
		for (int i = 0; i < name.size(); i++) {
			if (name[i] == ' ')
				name[i] = '*';
		}
		price = products[i].get_price();
		count = products[i].get_count();
		temp << qrcode << ' ' << name << ' ' << price << ' ' << count << endl;
	}
	cin.get();
	temp.close();
	remove("product.txt");
	rename("temp.txt", "product.txt");
}
void readproduct() {
	product pros;
	unsigned long long int qrcode, price, count;
	string name;
	ifstream infile("product.txt", ios::in);
	if (!infile) {
		fstream infile("product.txt", ios::in);
		/*cerr << "File not opened!";
		exit(1);*/
	}
	while (infile >> qrcode >> name >> price >> count )
	{
		for (int i = 0; i < name.size(); i++) {
			if (name[i] == '*')
				name[i] = ' ';
		}
		//outputline(qrcode, name, price, count);
		pros.addproduct(qrcode, name, price, count);
		products.push_back(pros);
		shop obj(products);
	}
	infile.close();
}
void readperson() {
	string name, phone;
	normal norms;
	vip vis;
	bool setperson;
	ifstream infilep("person.txt", ios::in);
	if (!infilep) {
			cerr << "File person.txt not opened! You must to first create it!";
			system("pause");
			exit(1);
	}
	while (infilep >> setperson >> name >> phone)
	{
		for (int i = 0; i < name.size(); i++) {
			if (name[i] == '*')
				name[i] = ' ';
		}
		if (setperson == 0) {
			norms.add(name, phone);
			normals.push_back(norms);
		}
		if (setperson == 1) {
			vis.add(name, phone);
			vips.push_back(vis);
		}
	}
	infilep.close();
}

void personsave() {
	string name, phone;
	normal norms;
	vip vis;
	bool setperson;
	fstream temp2("temp2.txt", ios::out);
	if (!temp2) {
			cerr << "File temp2.txt (file for save person.txt) not opened! You must to first create it!";
			system("pause");
			cin.get();
			exit(1);
	}
	for (int i = 0 ; i < normals.size() ; i++) {
		setperson = 0;
		name = normals[i].get_name();
		for (int j = 0; j < name.size(); j++) {
			if (name[j] == ' ')
				name[j] = '*';
		}
		phone = normals[i].get_phone();
		temp2 << setperson << ' ' << name << ' ' << phone << endl;
	}
	for (int i = 0; i < vips.size(); i++) {
		setperson = 1;
		name = vips[i].get_name();
		for (int j = 0; j < name.size(); j++) {
			if (name[j] == ' ')
				name[j] = '*';
		}
		phone = vips[i].get_phone();
		temp2 << setperson << ' ' << name << ' ' << phone << endl;
	}
	cin.get();
	temp2.close();
	remove("person.txt");
	rename("temp2.txt", "person.txt");
}

void buysave() {
	buy str;
	string name;
	string pname;
	string phone;
	int bc, buycode, number, k = 0;
	long float allprice;
	unsigned long long int qrcode, price, count;
	fstream buyinfo("buyinfotemp.txt", ios::out);
		if (!buyinfo) {
			cerr << "\nFile buyinfotemp.txt not opened! You must to first create it!\n";
			system("pause");
			cin.get();
			exit(1);
	}
	fstream buyist("buylisttemp.txt", ios::out);
		if (!buyist) {
			cerr << "\nFile buylisttemp.txt not opened! You must to first create it!\n";
			system("pause");
			cin.get();
			exit(1);
	}
	for (int i = 0; i < buys.size(); i++) {
		k = 0;
		while (k < 1){
			buycode = buys[i].first.get_buycode();
			for (int j = 0; j < buys[buycode].second.size(); j++)
			{
				qrcode = buys[buycode].second[j].get_qrcode();
				name = buys[buycode].second[j].get_name();
				for (int m = 0; m < name.size(); m++) {
					if (name[m] == ' ')
						name[m] = '*';
				}
				price = buys[buycode].second[j].get_price();
				number = buys[buycode].second[j].get_count();
				buyist << buycode << ' ' << qrcode << ' ' << name << ' ' << price << ' ' << number << endl;

				pname = buys[i].first.get_name();
				for (int n = 0; n < pname.size(); n++) {
					if (pname[n] == ' ')
						pname[n] = '*';
				}
				phone = buys[i].first.get_phone();
				allprice = buys[i].first.get_allprice();
				buyinfo << buycode << ' ' << pname << ' ' << phone << ' ' << allprice << endl;
				k++;
			}
		}
	}
	cin.get();
	buyinfo.close();
	buyist.close();
	remove("buyinfo.txt");
	rename("buyinfotemp.txt", "buyinfo.txt");
	remove("buylist.txt");
	rename("buylisttemp.txt", "buylist.txt");
}

void readbuy() {
	product by;
	buy str;
	string name;
	string pname;
	string phone;
	int bc, buycode,probuycode;
	long float allprice;
	unsigned long long int qrcode, price, count;
	buy purchase;
	int number;
	ifstream buyinfo("buyinfo.txt", ios::in);
		if (!buyinfo) {
			cerr << "\nFile buyinfo.txt not opened! You must to first create it!\n";
			system("pause");
			cin.get();
			exit(1);
	}
	fstream buylst("buylist.txt", ios::in);
		if (!buylst) {
			cerr << "\nFile buylist.txt not opened! You must to first create it!\n";
			system("pause");
			cin.get();
			exit(1);
	}
	while (buyinfo >> buycode >> pname >> phone >> allprice)
	{
		buylist.clear();
		for (int i = 0; i < pname.size(); i++) {
			if (pname[i] == '*')
				pname[i] = ' ';
		}
		buylst.close();
		fstream buylst("buylist.txt", ios::in);
		while (buylst >> probuycode >> qrcode >> name >> price >> number) {
			if (buycode == probuycode) {
				for (int j = 0; j < name.size(); j++) {
					if (name[j] == '*')
						name[j] = ' ';
				}
				by.addproduct(qrcode, name, price, number);
				buylist.push_back(by);
			}
		}
			str.addbuyinfo(buycode, pname, phone, allprice);
			buys.push_back(make_pair(str, buylist));
		}

	buyinfo.close();
	buylst.close();
}

void outputline(unsigned long long int qrcode, const string name, unsigned long long int price, unsigned long long int count)
{
	cout << left << setw(10) << qrcode << setw(13) << name
		<< setw(7) << price << right << count << endl;
}