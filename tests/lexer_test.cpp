#include <iostream>
#include <cassert>
#include <vector>

#include <token/token.hpp>
#include <lexer/lexer.hpp>

using namespace lang::token;
using namespace lang::lexer;

int main()
{
	std::string input = R"(
let five = 5;
let ten = 10;

let add = fn(x, y) {
  x + y;
};

let result = add(five, ten);
!-/*5;
5 < 10 > 5;

if (5 < 10) {
	return true;
} else {
	return false;
}

10 == 10;
10 != 9;
)";

    auto lexer = Lexer{input};

    std::vector<Token> tests = {
        {TokenType::LET, "let"},
		{TokenType::IDENTIFIER, "five"},
		{TokenType::ASSIGN, "="},
		{TokenType::DOUBLE, "5"},
		{TokenType::SEMICOLON, ";"},
		{TokenType::LET, "let"},
		{TokenType::IDENTIFIER, "ten"},
		{TokenType::ASSIGN, "="},
		{TokenType::DOUBLE, "10"},
		{TokenType::SEMICOLON, ";"},
		{TokenType::LET, "let"},
		{TokenType::IDENTIFIER, "add"},
		{TokenType::ASSIGN, "="},
		{TokenType::FUNCTION, "fn"},
		{TokenType::LPAREN, "("},
		{TokenType::IDENTIFIER, "x"},
		{TokenType::COMMA, ","},
		{TokenType::IDENTIFIER, "y"},
		{TokenType::RPAREN, ")"},
		{TokenType::LBRACE, "{"},
		{TokenType::IDENTIFIER, "x"},
		{TokenType::PLUS, "+"},
		{TokenType::IDENTIFIER, "y"},
		{TokenType::SEMICOLON, ";"},
		{TokenType::RBRACE, "}"},
		{TokenType::SEMICOLON, ";"},
		{TokenType::LET, "let"},
		{TokenType::IDENTIFIER, "result"},
		{TokenType::ASSIGN, "="},
		{TokenType::IDENTIFIER, "add"},
		{TokenType::LPAREN, "("},
		{TokenType::IDENTIFIER, "five"},
		{TokenType::COMMA, ","},
		{TokenType::IDENTIFIER, "ten"},
		{TokenType::RPAREN, ")"},
		{TokenType::SEMICOLON, ";"},
		{TokenType::BANG, "!"},
		{TokenType::MINUS, "-"},
		{TokenType::SLASH, "/"},
		{TokenType::ASTERISK, "*"},
		{TokenType::DOUBLE, "5"},
		{TokenType::SEMICOLON, ";"},
		{TokenType::DOUBLE, "5"},
		{TokenType::LT, "<"},
		{TokenType::DOUBLE, "10"},
		{TokenType::GT, ">"},
		{TokenType::DOUBLE, "5"},
		{TokenType::SEMICOLON, ";"},
		{TokenType::IF, "if"},
		{TokenType::LPAREN, "("},
		{TokenType::DOUBLE, "5"},
		{TokenType::LT, "<"},
		{TokenType::DOUBLE, "10"},
		{TokenType::RPAREN, ")"},
		{TokenType::LBRACE, "{"},
		{TokenType::RETURN, "return"},
		{TokenType::TRUE, "true"},
		{TokenType::SEMICOLON, ";"},
		{TokenType::RBRACE, "}"},
		{TokenType::ELSE, "else"},
		{TokenType::LBRACE, "{"},
		{TokenType::RETURN, "return"},
		{TokenType::FALSE, "false"},
		{TokenType::SEMICOLON, ";"},
		{TokenType::RBRACE, "}"},
		{TokenType::DOUBLE, "10"},
		{TokenType::EQ, "=="},
		{TokenType::DOUBLE, "10"},
		{TokenType::SEMICOLON, ";"},
		{TokenType::DOUBLE, "10"},
		{TokenType::NOTEQ, "!="},
		{TokenType::DOUBLE, "9"},
		{TokenType::SEMICOLON, ";"},
		{TokenType::END_OF_FILE, ""},
    };

    for(const auto& test_token: tests)
    {
        auto tok = lexer.NextToken();
		
		// std::cout << test_token << tok;
        assert(test_token == tok);
    }

	std::cout << "ALL TESTS PASSED. NO ERRORS\n";

	return 0;
}