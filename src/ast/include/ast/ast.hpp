#ifndef __AST_HPP__
#define __AST_HPP__

#include <vector>
#include <string>
#include <memory>

#include <token/token.hpp>

namespace lang
{
    namespace ast
    {
        struct Node
        {
            virtual std::string token_value() = 0;/* Used for debugging purpose */
            virtual ~Node(){}
        };

        /* 
            The AST we are going to construct consists solely of Nodes that are connected to
            each other - it's a tree after all. Some of these nodes implement the Statement and some the
            Expression interface

            Difference between expression and statement ?
            Expressions produce values, statements don’t. `let x = 5` doesn’t produce a value,
            whereas 5 does (the value it produces is 5)
        */

        struct Statement: public Node
        {
            virtual void statement_node() = 0;
            virtual ~Statement(){}
        };

        struct Expression: public Node
        {
            virtual void expression_node() = 0;
            virtual ~Expression(){}
        };

        struct Program
        {
            std::vector<std::unique_ptr<Statement>> statements;
        };

        /* Statements */

        struct Identifier: public Expression
        {
            token::Token token; // The token.IDENTIFIER token
            std::string value;

            void expression_node() override {}

            std::string token_value() override
            {
                return token.value;
            }

            ~Identifier() override {}
        };

        /*  let statement:

            `let x = 5` doesn’t produce a value,
            whereas 5 does (the value it produces is 5)
        */
        struct LetStatement: public Statement
        {
            token::Token token; // The token.LET token

            /* name to hold the identifier of the binding */
            std::unique_ptr<Identifier> name;

            /* value for the expression that produces the value */
            std::unique_ptr<Expression> value;

            void statement_node() override {}

            std::string token_value() override
            {
                return token.value;
            }
            
            ~LetStatement() override {}

        };
    }
}

#endif