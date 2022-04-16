#include "variable.h"
#include "std_lib_facilities.h"

double Symbol_table::get_value(string s)
{
  for (auto x : var_table)
    if (x.name == s)
      return x.value;
  error("get: undefined name ", s);
}



bool Symbol_table::is_declared(string s)
{
  for (auto x : var_table)
    if (x.name == s) return true;
  return false;
}

void Symbol_table::print_constants()
{
	for (auto x : var_table)
	{
		if (!x.is_const)
			cout << x.name << " = " << x.value << endl;
	}
		
}



void Symbol_table::set_value(string s, double d)
{
	for (auto x : var_table)
	{		
			if (x.name == s || x.name == "e" || x.name == "pi")
			{
				if (x.is_const == false) error(s, " is constant");
				x.value = d;
				return;
			}
	}
	error("set: undefined name ", s);
}


double Symbol_table::define_name (string var, double val, bool c)
{
  if (is_declared(var))
      for (auto x : var_table)
		  if (x.name == var)
		  {
			  x.value = val;
			  x.is_const = c;
		  }
  var_table.push_back(Variable{ var, val, c });
  return val;
}

Variable& Symbol_table::operator[](unsigned int i)
{
	return var_table[i];
}

unsigned int Symbol_table::size()
{
	return var_table.size();
}
