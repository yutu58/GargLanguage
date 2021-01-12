#ifndef TOKENS_H
#define TOKENS_H

#include <unordered_set>
#include <string>
#include <unordered_map>

namespace LEXER
{
    enum class TokenType
    {
        Identifier,
        Keyword,
        String,
        Literal,
        BOperator,
        Delim,
        Definer,
        Ocurly,
        Ccurly,
        Obracket,
        Cbracket,
        Semic,
        Function,
        Statement,
        Expression,
        Eof,
        File
    };

    static const std::unordered_set<std::string> keywords = { "if", "for", "while", "print"};
    static const std::unordered_set<std::string> definers = { "int", "str"};
    static const std::unordered_set<std::string> boperators = { "+", "-", "*", "/", "=", "==", "+=", "-=", "*=", "/=", "<", ">", "<=", ">="};
    static const std::unordered_set<char> delims = { '(', ')', '{', '}', ';' };
    static const char Ocurly = '{';
    static const char Ccurly = '}';
    static const char Obracket = '(';
    static const char Cbracket = ')';
    static const char Semic = ';';
    static const std::unordered_set<char> whitespace = { '\n', '\r', '\t', ' ' };
    static const std::unordered_map<LEXER::TokenType, std::string> tokenMap = {
        {LEXER::TokenType::Identifier, "Identifier"},
        {LEXER::TokenType::Keyword, "Keyword"},
        {LEXER::TokenType::String, "String"},
        {LEXER::TokenType::Literal, "Literal"},
        {LEXER::TokenType::BOperator, "Binary Operator"},
        {LEXER::TokenType::Delim, "Delimiter"},
        {LEXER::TokenType::Definer, "Definer"},
        {LEXER::TokenType::Ocurly, "Opening Curly"},
        {LEXER::TokenType::Ccurly, "Closing Curly"},
        {LEXER::TokenType::Obracket, "Opening Bracket"},
        {LEXER::TokenType::Cbracket, "Closing Bracket"},
        {LEXER::TokenType::Semic, "Semicolumn"},
        {LEXER::TokenType::Function, "Function"},
        {LEXER::TokenType::Statement, "Statement"},
        {LEXER::TokenType::Expression, "Expression"},
        {LEXER::TokenType::Eof, "Eof"},
        {LEXER::TokenType::File, "File"}
        };



    struct Token
    {
        std::string tokenValue;
        TokenType tokenType;

        Token() = delete;

        Token(const std::string& tokenValue_, TokenType tokenType_): tokenValue(tokenValue_), tokenType(tokenType_){ /* empty */ }

        Token(const Token& token): tokenValue(token.tokenValue), tokenType(token.tokenType) { /* empty */ }


    };
}

#endif

/*https://codereview.stackexchange.com/questions/221608/lexer-using-c-and-regex*/
