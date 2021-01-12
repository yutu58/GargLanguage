#ifndef LEXER_H
#define LEXER_H

#include "Tokens.h"
#include <vector>

using LineNo = unsigned int;
namespace LEXER
{
    std::vector<Token> Tokenize(std::string filename);
    Token getToken(std::string buffer, LineNo line);
}


#endif

/*https://codereview.stackexchange.com/questions/221608/lexer-using-c-and-regex*/
