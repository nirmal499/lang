#include <token/token.hpp>

#include <unordered_map>

namespace lang
{
    namespace token
    {
        std::string tokenTypeToString(TokenType type)
        {
            static const std::unordered_map<TokenType, std::string> tokenTypeStrings
            {
                {TokenType::UNDEFINED, "UNDEFINED"},
                {TokenType::END_OF_FILE, "END_OF_FILE"},
                {TokenType::IDENTIFIER, "IDENTIFIER"},
                {TokenType::DOUBLE, "DOUBLE"},
                {TokenType::ASSIGN, "="},
                {TokenType::PLUS, "+"},
                {TokenType::MINUS, "-"},
                {TokenType::BANG, "!"},
                {TokenType::ASTERISK, "*"},
                {TokenType::SLASH, "/"},
                {TokenType::LT, "<"},
                {TokenType::GT, ">"},
                {TokenType::EQ, "=="},
                {TokenType::NOTEQ, "!="},
                {TokenType::COMMA, ","},
                {TokenType::SEMICOLON, ";"},
                {TokenType::LPAREN, "("},
                {TokenType::RPAREN, ")"},
                {TokenType::LBRACE, "{"},
                {TokenType::RBRACE, "}"},
                {TokenType::FUNCTION, "FUNCTION"},
                {TokenType::LET, "LET"},
                {TokenType::TRUE, "TRUE"},
                {TokenType::FALSE, "FALSE"},
                {TokenType::IF, "IF"},
                {TokenType::ELSE, "ELSE"},
                {TokenType::RETURN, "RETURN"}
            };

            auto it = tokenTypeStrings.find(type);
            if (it != tokenTypeStrings.end())
            {
                return it->second;
            } 
            else 
            {
                return "UNKNOWN_TOKEN";
            }
        }

        TokenType check_for_identifier(std::string identifier_value)
        {
            static const std::unordered_map<std::string, TokenType> keywords = {
                {"fn", TokenType::FUNCTION},
                {"let", TokenType::LET},
                {"true", TokenType::TRUE},
                {"false", TokenType::FALSE},
                {"if", TokenType::IF},
                {"else", TokenType::ELSE},
                {"return", TokenType::RETURN},
            };

            auto it = keywords.find(identifier_value);
            if(it != keywords.end())
            {
                return it->second;
            }

            return TokenType::IDENTIFIER;
        }

        std::ostream& operator<<(std::ostream& out, const Token& tok)
        {
            return out << "{'" << tokenTypeToString(tok.type) <<"' : '" << tok.value << "'}\n";
        }
    }
}

