#ifndef __LEXER_HPP_
#define __LEXER_HPP_


#include <string>
#include <token/token.hpp>

namespace lang
{
    namespace lexer
    {
        class Lexer
        {
            private:
                char peek_char();

                void read_char();


                void skipWhitespace();

                /* 
                    identifier: [_a-zA-Z][a-zA-Z0-9]*
                */
                std::string read_identifier();
                
                /* 
                    Number: [0-9.]+
                */
                std::string read_double();

            public:
                token::Token NextToken();

                Lexer(std::string input):
                    _input(std::move(input))
                {
                    _size_of_input = _input.size();

                    _next_position = 0;

                    /* Initializing _position and _ch before we can call this->next_token()*/
                    this->read_char();
                }
            private:
                std::string _input;
                size_t _size_of_input;

                /* current position in input (points to current char) */
                size_t _position; /* points to the character in the input that corresponds to the _ch char */

                /* current reading position in input (after current char) */
                size_t _next_position; /* points to the "next" character in the input */
                /* Its act as a lookahead */

                /* current char under examination */
                char _ch;
        };
    }
}

#endif