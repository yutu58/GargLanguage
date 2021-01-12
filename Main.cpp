#include <iostream>
#include <fstream>
#include <streambuf>
#include <string>
#include <sstream>
#include "Lexer/Lexer.cpp"
#include "Lexer/Tokens.h"
#include "Lexer/Lexer.h"
#include "Parser/Parser.cpp"
#include "Parser/common.h"

using namespace std;

int main(){
	auto vec =  LEXER::Tokenize("code.garg");

	for (auto x : vec)
	{
	cout << x.tokenValue << "->" << LEXER::tokenMap.find(x.tokenType)->second << "\n";
	}
    
	Parse(vec);
       
	/*let user enter filename*/
	ifstream codefile("code.garg");
	std::stringstream buf;
	buf << codefile.rdbuf();
	string code = buf.str();
			
	cout << code;
	/*
	ofstream assembly("compiled.s");
	assembly << data + text + globals + externs + mn + epilogue + subs;
	assembly.close();*/
	/*system("gcc -o compiled compiled.s");
	system("./compiled");*/
	/*remove("compiled.s");*/
}
