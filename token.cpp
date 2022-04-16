#include "token.h"
#include "variable.h"


Token Token_stream::get()
{
    if (full)
    {
		full = false;
		return buffer;
	}
    char ch;
    in.get(ch);

    if (ch == '\n')
		cout << "\b\b\b" << prompt;

	if (!in.good())
		exit(0);

	if (ch == '\n' || ch == '\0')
		return Token{ print };

	while (isspace(ch))
	{
        in.get(ch);
		if (ch == '\n' || ch == '\0')
			return Token{ print };
	}


	switch (ch)
	{
	case ' ':
		return Token{ print };
	case print:
		cout << "\b\b\b" << prompt;
        break;
	case '\n':
		cout << "\b\b\b" << prompt;
        break;
	case quit:
	case '(':
	case ')':
	case '}':
	case '{':
    case ']':
    case '[':
	case '+':
	case '-':
	case '*':
	case '/':
	case '%':
	case '=':
    case '!':
    case '^':
		return Token{ ch };
	case '.':
	{
		char ch1;
        in.get(ch1);
		if (ch1 < '0' || '9' < ch1)
			error("syntax error: some number must go after '.'");
        in.putback(ch1);
	}


    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
	{
        in.putback(ch);
		double val;
        in >> val;
		char ch1;
        in.get(ch1);
		if (ch1 == '.')
			error("syntax error: exccess dot");
        in.putback(ch1);
		return Token{ number, val };
	}


	default:
		if (isalpha(ch) || ch == underline)
		{
			string s;
			s += ch;
            while (in.get(ch) && (isalpha(ch) || isdigit(ch) || ch == underline))
			{

				s += ch;
			}
			in.putback(ch);
			if (s == help_table)
			{
				return Token{ help_ };
			}

			if (s == variable) return Token(let);
			if (s == constant) return Token(consta);

			return Token{ name, s };
		}
		error("Bad Token");
	}
}


void Token_stream::putback(Token t)
{
	if (full)
		error("putback() into a full buffer");

	buffer = t;
	full = true;
}



void Token_stream::ignore(char c)
{
	if (full && c == buffer.kind)
	{
		full = false;
		return;
	}
	full = false;

	char ch = '\0';
    while (cin.get(ch))
		if (ch == c || ch == '\n') return;
}


void clean_up_mess(Token_stream& ts)
{
	ts.ignore(print);
}








