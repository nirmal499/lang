#ifndef __TOKEN_HPP
#define __TOKEN_HPP

#include <string>
#include <iostream>

namespace lang
{
    namespace token
    {
        enum class TokenType
        {
            UNDEFINED,/* signifies a character we don’t know about */
            END_OF_FILE,/* End of file */

            // Identifiers + literals
            IDENTIFIER, // add, foobar, x, y, ...
            DOUBLE, // 1343456

            // Operators
            ASSIGN,
            PLUS,
            MINUS,
            BANG,
            ASTERISK,
            SLASH,

            LT,
            GT,

            EQ,
            NOTEQ,

            // Delimiters
            COMMA ,
            SEMICOLON,

            LPAREN,
            RPAREN,
            LBRACE,
            RBRACE,

            // Keywords
            FUNCTION,
            LET,
            TRUE,
            FALSE,
            IF,
            ELSE,
            RETURN,
        };

        std::string tokenTypeToString(TokenType type);

        struct Token
        {
            TokenType type;
            std::string value;

            bool operator==(const Token& tok) const
            {
                return (this->type == tok.type) && (this->value == tok.value);
            }

            bool operator!=(const Token& tok) const
            {
                return !(*this == tok);
            }
        };

        std::ostream& operator<<(std::ostream& out, const Token& tok);

        TokenType check_for_identifier(std::string identifier_value);
    }
}

#endif