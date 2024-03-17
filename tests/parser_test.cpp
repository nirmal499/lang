#include <iostream>
#include <cassert>
#include <utility>

#include <token/token.hpp>
#include <lexer/lexer.hpp>
#include <parser/parser.hpp>
#include <ast/ast.hpp>

using namespace lang::token;
using namespace lang::lexer;
using namespace lang::parser;
using namespace lang::ast;

bool test_let_statement(Statement* statement, std::string test)
{
    if(statement->token_value() != "let")
    {
        return false;
    }

    LetStatement* let_statement = dynamic_cast<LetStatement*>(statement);
    if(let_statement == nullptr)
    {
        return false;
    }

    if(let_statement->name->value != test || let_statement->name->token_value() != test)
    {
        return false;
    }

    return true;
}

int main()
{

    std::string input1 = R"(
let x = 5;
let y = 10;
let foobar = 838383;

)";

    std::string input2 = R"(
let x 5;
let = 10;
let 838383;

)";

    auto lexer = std::make_unique<Lexer>(input2);
    auto parser = Parser{std::move(lexer)};

    auto [program, errors] = parser.parse_program();
    
    if(errors.size() != 0)
    {   
        std::cout << "Parser has " << errors.size() << " errors\n";
        for(const auto& error: errors)
        {
            std::cout << "Parser error: " << error << "\n";
        }

        return 1;
    }

    assert(program.statements.size() == 3);

    std::vector<std::string> tests = {
        {"x"},
        {"y"},
        {"foobar"},
    };

    for(size_t i = 0 ; i < 3 ; i++)
    {
        std::string test = tests.at(i);
        Statement* statement = program.statements[i].get();

		assert(test_let_statement(statement, test) == true);
    }

	std::cout << "ALL TESTS PASSED. NO ERRORS\n";

    return 0;
}