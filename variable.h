#pragma once

#include "std_lib_facilities.h"

struct Variable
{
  string name;
  double value;
  bool is_const;
  Variable (string n, double v)
	  : name{ n }, value{ v }, is_const{ false } { }
  Variable (string n, double v, bool c)
	  : name{ n }, value{ v }, is_const{ c } { }
};


class Symbol_table
{
public:
	double get_value(string s);

	void set_value(string s, double d);

	bool is_declared(string s);

	double define_name(string var, double val, bool c);
   
	void print_constants();

    Variable& operator[](unsigned int i);

    unsigned int size();

private:
	vector<Variable> var_table;
};
