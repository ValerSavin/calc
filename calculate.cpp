#include "std_lib_facilities.h"
#include "token.h"
#include "variable.h"

void help_table_()
{
    cout << "Calculator" << '\n'
         << "Operands: +, -, /, *, %, !, ^" << '\n'
         << "> To define a variable enter 'let <name> = <expression>'" << '\n'
         << "> To define a constant enter 'constant <name> = <expression>'" << '\n'
         << "> To assign a value to a variable '<name> = <expression>'" << '\n'
         << "> Defined const: 'pi' and 'e'" << '\n'
         << "> For exit enter 'quit', for print answer press 'enter'" << '\n'
         << "to output an instruction print 'help'"
         << endl;
}


unsigned long long factorial(double n)
{
	if (n < 0)
        error("Factorial does not work with negative numbers");
	if (n > 20)
        error("Sorry, factorial is not working for numbers > 20");

    unsigned long long r = static_cast<unsigned long long>(n);

    for (auto i = n - 1; i > 0; i--)
        r *= i;
    return (r == 0) ? 1 : r; // если 0, возвращаем 1, если !=0, возвращаем значение
}


double expression(Token_stream& ts, Symbol_table& var_table);

double primary(Token_stream& ts, Symbol_table& var_table)
{
    Token t = ts.get();
	switch (t.kind)
	{
	case '(':
	{
		double d = expression(ts, var_table);
		t = ts.get();
		if (t.kind != ')')
			error("')' expected");
		return d;
	}
    case '[':
    {
        double d = expression(ts, var_table);
        t = ts.get();
        if (t.kind != ']')
            error("']' expected");
        return d;
    }
	case '{':
	{
		double d = expression(ts, var_table);
		t = ts.get();
		if (t.kind != '}')
			error("'}' expected");
		return d;
	}

	case '-':
		return -primary(ts, var_table);
	case '+':
		return +primary(ts, var_table);

	case number:
		return t.value;
	case name:
	{
		Token n = ts.get();
		if (n.kind == '=') {
			double d = expression(ts, var_table);
			var_table.set_value(t.name, d);
			return d;
		}
		else {
			ts.putback(n);
			return var_table.get_value(t.name);
		}
	}
	default:
		error("primary expected");
	}
}


double secondary(Token_stream& ts, Symbol_table& var_table)
{
    double left = primary(ts, var_table);
    Token t = ts.get();
	while (true)
	{
		switch (t.kind)
		{
		case '!':
			t = ts.get();
			if (t.kind == '!')
				error("secondary: '!!' - wrong function");
			else
            {
				left = static_cast<double>(factorial(left));
			}
			break;
		case '^':
		{
			double right = expression(ts, var_table);
            left = pow(left, right); // pow(a,b) - возведение в степень
			return left;
		}
		default:
			ts.putback(t);
			return left;
		}
	}
}


double term(Token_stream& ts, Symbol_table& var_table)
{
	double left = secondary(ts, var_table);
	while (true)
	{
		Token t = ts.get();

		switch (t.kind)
		{
        case '*':
            left *= secondary(ts, var_table);
			break;

		case '/':
		{
			double d = secondary(ts, var_table);
            if (d == 0.0) error("term: divide by zero");
			left /= d;
			break;
		}
		case '%':
		{
			double d = secondary(ts, var_table);
            if (d == 0.0) error("term: %: divided by 0");
			left = fmod(left, d);
			break;
		}
		default:
			ts.putback(t);
			return left;
		}
	}
}


double expression(Token_stream& ts, Symbol_table& var_table)
{
	double left = term(ts, var_table);
	while (true)
	{
		Token t = ts.get();

		switch (t.kind)
		{
		case '+':
			left += term(ts, var_table);
			break;

		case '-':
			left -= term(ts, var_table);
			break;

		default:
			ts.putback(t);
			return left;
		}
	}
}

double declaration(Token n, Symbol_table& var_table)
{
	Token_stream ts;
	Token t = ts.get();
	if (t.kind != name)
		error("declaration: name expected in declaration");

	string var = t.name;
	Token t2 = ts.get();
	
	if (t2.kind != '=')
		error("= missing declaration of ", var);


	if (var_table.is_declared(var))
		error("decalration: redefining of variable");

	double d = expression(ts, var_table);
	var_table.define_name(var, d, n.kind == let);
	return d;
}

double statement(Token_stream& ts, Symbol_table& var_table)
{
    Token t = ts.get();
	switch (t.kind)
	{
	case let: case consta:
		return declaration(t.kind, var_table);
	default:
        ts.putback(t);
		return expression(ts, var_table);
	}
}
 

void calculate(Symbol_table& var_table)
{
    ifstream fil("calc.txt");
    Token_stream ts(fil);
	while (true)
	{
		try
        {
            cout << prompt;
			Token t = ts.get();
			while (t.kind == print)
				t = ts.get();
			if (t.kind == quit)
				return;
			if (t.kind == help_)
			{
                help_table_();
                continue;
            }
            ts.putback(t);
            cout << "\b\b\b" << result << statement(ts, var_table) << endl;
		}
		catch (exception& e)
		{
			cout << "\b\b\b" << e.what() << "\n";
			clean_up_mess(ts);
		}
	}
}
