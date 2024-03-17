#ifndef __PARSER_HPP__
#define __PARSER_HPP__

#include <token/token.hpp>
#include <ast/ast.hpp>
#include <lexer/lexer.hpp>

#include <utility>
#include <memory>

namespace lang
{
    namespace parser
    {
        class Parser
        {   
            private:
                std::unique_ptr<ast::Statement> parse_let_statement();

                bool current_token_is(token::TokenType t);

                bool peek_next_token_is(token::TokenType t);

                bool expectPeek(token::TokenType t);

                std::unique_ptr<ast::Statement> parse_statement();

                void read_next_token();

                void add_errors(token::TokenType t);

            public:
                std::pair<ast::Program, std::vector<std::string>> parse_program();

                Parser(std::unique_ptr<lexer::Lexer> lexer_ptr):
                    _lexer_ptr(std::move(lexer_ptr))
                {
                    /* Read two tokens, so _current_token and _next_token are both set */
                    this->read_next_token();
                    this->read_next_token();
                }

            private:
                std::unique_ptr<lexer::Lexer> _lexer_ptr;

                /* current token under examination, to decide what to do next */
                token::Token _current_token;

                /* next token after _current_token, we need it incase _current_token doesn’t give us enough information */
                token::Token _next_token;

                std::vector<std::string> _errors;
        };
    }
}


#endif