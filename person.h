#pragma once
#include <iostream>
#include <string>
using namespace std;

class person
{
public:
	void add(string n, string ph);
	void print();
	string get_phone() { return phone; }
	string get_name() { return name; }
private:
	string name;
	string phone;
};

class normal : public person
{
public:
	void setnorm(bool a);
private:
	bool isnorm;
};

class vip : public person 
{
public:
	void setvip(bool a);
private:
	bool isvip;
};