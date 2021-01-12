#include "tree.hh"
#include <string>
#include <iostream>
#include "common.h"

string data = ".data\n";
string text = ".text\nformat_int: .asciz \"%ld\"\n";
string globals = ".global main\n";
string externs = ".extern printf\n";

string prologue = "push {ip, lr}\n";
string epilogue = "pop {ip, pc}\n";

string subs = "\n";


int assemble(vector<LEXER::Token> vec, tree<LEXER::TokenType> tr){
	tree<LEXER::TokenType>::iterator mainIt;
	
	mainIt = find(tr.begin(), tr.end(), LEXER::TokenType::File);
	tree<LEXER::TokenType>::pre_order_iterator funcs = tr.begin(mainIt);
	while(funcs != tr.end(mainIt)){
		LEXER::TokenType epic = (*funcs);
		cout << LEXER::tokenMap.find(epic)->second << "\n";
		++funcs;
	}
	return 0;
} 
