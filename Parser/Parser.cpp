#include <iostream>
#include <vector>
#include <stack>
#include "grammar.h"
#include "tree.hh"
#include "Assemble.cpp"

using namespace std;


stack<LEXER::TokenType> es;
stack<LEXER::TokenType> given;

int Parse(vector<LEXER::Token> vec){
	tree<LEXER::TokenType> tr;
	tree<LEXER::TokenType>::iterator top, currentFunc, currentStatement, currentIt;
	top = tr.insert(tr.begin(), LEXER::TokenType::File);
	
	
	es.push(LEXER::TokenType::Eof);
	given.push(LEXER::TokenType::Eof);
	
	for(int i = vec.size()-1; i>=0; i--){
		given.push(vec[i].tokenType);
	}
	
	
	while(es.size() > 0){
		LEXER::TokenType next = es.top();
		es.pop();
		cout << LEXER::tokenMap.find(next)->second << "& found " <<  LEXER::tokenMap.find(given.top())->second << "\n";	
		switch(next){
			case (LEXER::TokenType::Eof):
				/*the previous function has now been defined, unless code is empty*/
				if (given.size() == 1){continue;}
				else {
					es.push(LEXER::TokenType::Eof);
					es.push(LEXER::TokenType::Function);
				}
				break;
			case (LEXER::TokenType::Function):
				currentFunc = tr.append_child(top, LEXER::TokenType::Function);
				currentIt = currentFunc;
				es.push(LEXER::TokenType::Ccurly);
				es.push(LEXER::TokenType::Statement);
				es.push(LEXER::TokenType::Ocurly);
				es.push(LEXER::TokenType::Cbracket);
				//paramters
				es.push(LEXER::TokenType::Obracket);
				es.push(LEXER::TokenType::Identifier);
				break;
			case (LEXER::TokenType::Identifier):
				tr.append_child(currentIt, LEXER::TokenType::Identifier);
				if (given.top() != LEXER::TokenType::Identifier){
					cout << "Expected Identifier but got " + LEXER::tokenMap.find(given.top())->second << "\n";
					return -1;
				}
				else {
					given.pop();
				}
				break;
			case (LEXER::TokenType::Obracket):
				tr.append_child(currentIt, LEXER::TokenType::Obracket);
				if (given.top() != LEXER::TokenType::Obracket){
					cout << "Expected opening bracket but got " + LEXER::tokenMap.find(given.top())->second << "\n";
					return -1;
				}
				else{
					given.pop();
				}
				break;
			case (LEXER::TokenType::Cbracket):
				tr.append_child(currentIt, LEXER::TokenType::Cbracket);
				if (given.top() != LEXER::TokenType::Cbracket){
					cout << "Expected closing bracket but got " + LEXER::tokenMap.find(given.top())->second << "\n";
					return -1;
				}
				else{
					given.pop();
				}
				break;
			case (LEXER::TokenType::Statement):
				currentStatement = tr.append_child(currentIt, /*??*/LEXER::TokenType::Statement);
				currentIt = currentStatement;
				switch(given.top()){
					case(LEXER::TokenType::Ocurly):
						
						break;
					case(LEXER::TokenType::Keyword):
						
						break;
					case(LEXER::TokenType::Definer):
						es.push(LEXER::TokenType::Semic);
						es.push(LEXER::TokenType::Expression);
						es.push(LEXER::TokenType::BOperator);
						es.push(LEXER::TokenType::Identifier);
						es.push(LEXER::TokenType::Definer);
						break;
					default:
						return -1;
				}
				break;
			case (LEXER::TokenType::Expression):
				switch(given.top()){
					case (LEXER::TokenType::Literal):
						es.push(LEXER::TokenType::Literal);
						break;
					case (LEXER::TokenType::String):
					
						break;
					case (LEXER::TokenType::Identifier):
						
						break;
					default:
						return -1;
				}
				break;
			case (LEXER::TokenType::Definer):
				tr.append_child(currentIt, LEXER::TokenType::Definer);
				given.pop();
				break;
			case (LEXER::TokenType::BOperator):
				tr.append_child(currentIt, LEXER::TokenType::BOperator);
				if (given.top() != LEXER::TokenType::BOperator){
					cout << "Expected binary operator but got " + LEXER::tokenMap.find(given.top())->second << "\n";
					return -1;
				}
				else {
					given.pop();
				}
				break;
			case (LEXER::TokenType::Semic):
				if (given.top() != LEXER::TokenType::Semic){
					cout << "Expected semicolumn but got " + LEXER::tokenMap.find(given.top())->second << "\n";
					return -1;
				}
				else {
					given.pop();
				}
				currentIt = tr.parent(currentIt);
				break;
			case (LEXER::TokenType::Ocurly):
				if (given.top() != LEXER::TokenType::Ocurly){
					cout << "Expected opening curly but got " + LEXER::tokenMap.find(given.top())->second << "\n";
					return -1;
				}
				else {
					given.pop();
				}
				break;
			case (LEXER::TokenType::Ccurly):
				if (given.top() != LEXER::TokenType::Ccurly){
					cout << "Expected closing curly but got " + LEXER::tokenMap.find(given.top())->second << "\n";
					return -1;
				}
				else {
					given.pop();
				}
				break;
			case (LEXER::TokenType::Literal):
				tr.append_child(currentIt, LEXER::TokenType::Literal);
				if (given.top() != LEXER::TokenType::Literal){
					cout << "Expected literal but got " + LEXER::tokenMap.find(given.top())->second << "\n";
					return -1;
				}
				else {
					given.pop();
				}
				break;
			default:
				return -1;
		}
	}
	int res = 0;
	res = assemble(vec, tr);
	return res;
}
