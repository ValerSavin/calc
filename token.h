#pragma once

#include "std_lib_facilities.h"

struct Token
{
  char kind;
  double value;
  string name;

  Token (char ch)
    : kind{ ch }{ }

  Token (char ch, double val)
	  : kind{ ch }, value{ val } { }

  Token (char ch, string n)
	  : kind{ ch }, name{ n } { }
};


class Token_stream
{
public:
  Token_stream () : in{ cin } { }
  Token_stream (istream& s) : in{ s } { }

  Token get ();

  void putback (Token t);
  void ignore (char);

private:
  istream& in;
  bool full{ false };
  Token buffer{ '\0' };
};


void clean_up_mess (Token_stream& ts);


constexpr char quit = 'q';
constexpr char print = ';';
constexpr char number = '8';
constexpr char name = 'a';
constexpr char let = 'L';
constexpr char consta = 'C';
constexpr char underline = '_';
constexpr char help_ = 'h';

const string prompt = "> ";
const string result = "= ";
const string variable = "let";
const string constant = "const";
const string help_table = "help";


