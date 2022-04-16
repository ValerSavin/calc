#pragma once

#include "std_lib_facilities.h"
#include "token.h"
#include "variable.h"


unsigned long long factorial(double n);


double expression (Token_stream& ts, Symbol_table& var_table);


double primary (Token_stream& ts, Symbol_table& var_table);


double secondary (Token_stream& ts, Symbol_table& var_table);


double term (Token_stream& ts, Symbol_table& var_table);


double declaration (Token_stream& ts, Symbol_table& var_table);


double statement (Token_stream& ts, Symbol_table& var_table);


void calculate (Symbol_table& var_table);

void help_table_();
