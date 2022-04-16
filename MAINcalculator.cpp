#include "std_lib_facilities.h"
#include "calculate.h"
#include <fstream>


int main()
try
{
	Symbol_table var_table{};
    var_table.define_name("pi", 3.141592653589793, true);
    var_table.define_name("e", 2.718281828459045, true);
	calculate(var_table);
}

catch (exception& e)
{
	cerr << "exception: " << e.what() << endl;
	return 1;
}
catch (...)
{
	cerr << "Oops, unknown exception" << endl;
	return 2;
}
