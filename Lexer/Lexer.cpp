#include "Lexer.h"
#include<fstream>
#include<iostream>
#include<regex>
namespace LEXER
{
    Token getToken(std::string buffer, LineNo line)
    {
        if (boperators.find(buffer) != boperators.end())
        {
            return Token(buffer, TokenType::BOperator);
        }
        else if (keywords.find(buffer) != keywords.end())
        {
            return Token(buffer, TokenType::Keyword);
        }
        else if (definers.find(buffer) != definers.end())
        {
            return Token(buffer, TokenType::Definer);
        }

        std::regex iden("[a-zA-Z][a-zA-Z0-9_]*");
        std::regex str("\".*\"");
        std::regex lit("^[0-9]+$");
        //std::regex;

        if (std::regex_match(buffer, iden))
        {
            return Token(buffer, TokenType::Identifier);
        }
        if (std::regex_match(buffer, str))
        {
            return Token(buffer, TokenType::String);
        }
        if (std::regex_match(buffer, lit))
        {
            return Token(buffer, TokenType::Literal);
        }


        /* No support for comments yet*/

        /* Will only reach here if all else fails, invalid string */

        std::cout << "Invalid expression at line number " << line << " : " << buffer;
        std::cin.get();
        exit(0);

    }


    std::vector<Token> Tokenize(std::string filename)
    {
        std::ifstream file(filename, std::ios::in);

        if (file.fail())
        {
            std::cout << "Unable to open file!\n";
            std::cin.get();
            exit(0);
        }

        LineNo line = 1;
        std::string buffer = "";

        char ch;
        std::vector<Token> tokens;

        while (file >> std::noskipws >> ch)
        {
            if (ch == '\n' || ch == '\r')
                line += 1;

            if (delims.find(ch) != delims.end())
            {
                if (buffer != "")
                {
                    tokens.push_back(getToken(buffer, line));
                    buffer = "";
                }
                if (ch == Ocurly){tokens.push_back(Token(std::string(1, ch), TokenType::Ocurly));}
                else if (ch == Ccurly){tokens.push_back(Token(std::string(1, ch), TokenType::Ccurly));}
                else if (ch == Obracket){tokens.push_back(Token(std::string(1, ch), TokenType::Obracket));}
                else if (ch == Cbracket){tokens.push_back(Token(std::string(1, ch), TokenType::Cbracket));}
                else if (ch == Semic){tokens.push_back(Token(std::string(1, ch), TokenType::Semic));}
                continue;
            }
            

            else if (whitespace.find(ch) != whitespace.end())
            {
                if (buffer != "")
                {
                    tokens.push_back(getToken(buffer, line));
                    buffer = "";
                }
                continue;
            }
            else
            {
                buffer += ch;
            }

        }
        return tokens;

    }
}

/*https://codereview.stackexchange.com/questions/221608/lexer-using-c-and-regex*/
