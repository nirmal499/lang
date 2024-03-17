#include <lexer/lexer.hpp>

namespace lang
{
    namespace lexer
    {
        char Lexer::peek_char()
        {
            if(_next_position >= _size_of_input)
            {
                return '\0';
            }
            else
            {
                return _input.at(_next_position);
            }
        }

        void Lexer::read_char()
        {
            if(_next_position >= _size_of_input)
            {
                _ch = '\0';
            }
            else
            {
                _ch = _input[_next_position];
            }
            _position = _next_position;
            _next_position++;
        }


        void Lexer::skipWhitespace()
        {
            while(std::isspace(_ch) || _ch == '\t' || _ch == '\n' || _ch == '\r')
            {
                this->read_char();
            }
        }

        /* 
            identifier: [_a-zA-Z][a-zA-Z0-9]*
        */
        std::string Lexer::read_identifier()
        {
            auto start = _position;

            while(std::isalnum(_ch))
            {
                this->read_char();
            }

            auto length = _position - start;
            return _input.substr(start, length);
        }
                
        /* 
            Number: [0-9.]+
        */
        std::string Lexer::read_double()
        {
            auto start = _position;
            while(std::isdigit(_ch) || _ch == '.')
            {
                this->read_char();
            }

            auto length = _position - start;
            return _input.substr(start, length);
        }

        token::Token Lexer::NextToken()
        {
            token::Token tok{};

            this->skipWhitespace();

            switch(_ch)
            {
                case '=':
                    if(this->peek_char() == '=')
                    {
                        /* we checked that the lookahead is '='. It means we have '==' */
                        tok = token::Token{token::TokenType::EQ, _input.substr(_position, 2)};
                        this->read_char(); // Consume the next '='
                    }
                    else
                    {
                        tok = token::Token{token::TokenType::ASSIGN, std::string(1, _ch)};
                    }
                    break;
                case ';':
                    tok = token::Token{token::TokenType::SEMICOLON, std::string(1, _ch)};
                    break;
                case '(':
                    tok = token::Token{token::TokenType::LPAREN, std::string(1, _ch)};
                    break;
                case ')':
                    tok = token::Token{token::TokenType::RPAREN, std::string(1, _ch)};
                    break;
                case ',':
                    tok = token::Token{token::TokenType::COMMA, std::string(1, _ch)};
                    break;
                case '+':
                    tok = token::Token{token::TokenType::PLUS, std::string(1, _ch)};
                    break;
                case '-':
                    tok = token::Token{token::TokenType::MINUS, std::string(1, _ch)};
                    break;
                case '/':
                    tok = token::Token{token::TokenType::SLASH, std::string(1, _ch)};
                    break;
                case '*':
                    tok = token::Token{token::TokenType::ASTERISK, std::string(1, _ch)};
                    break;
                case '<':
                    tok = token::Token{token::TokenType::LT, std::string(1, _ch)};
                    break;
                case '>':
                    tok = token::Token{token::TokenType::GT, std::string(1, _ch)};
                    break;
                case '{':
                    tok = token::Token{token::TokenType::LBRACE, std::string(1, _ch)};
                    break;
                case '}':
                    tok = token::Token{token::TokenType::RBRACE, std::string(1, _ch)};
                    break;
                case '!':
                    {   
                        /* we checked that the lookahead is '='. It means we have '!=' */
                        if(this->peek_char() == '=')
                        {
                            tok = token::Token{token::TokenType::NOTEQ, _input.substr(_position, 2)};
                            this->read_char(); // Consume next '='
                        }
                        else
                        {
                            tok = token::Token{token::TokenType::BANG, std::string(1, _ch)};
                        }
                    }
                    break;
                case '\0':
                    tok = token::Token{token::TokenType::END_OF_FILE, ""};
                    break;
                default:
                    {
                        if(std::isalpha(_ch) || _ch == '_')
                        {
                            /* 
                                identifier: [_a-zA-Z][a-zA-Z0-9]*
                            */
                            tok.value = this->read_identifier();
                            tok.type = token::check_for_identifier(tok.value);

                            return std::move(tok);
                        }
                        else if(std::isdigit(_ch) || _ch == '.')
                        {
                            /* 
                                Number: [0-9.]+
                            */
                            tok = {
                                .type = token::TokenType::DOUBLE,
                                .value = this->read_double()
                            };

                            return std::move(tok);
                        }
                        else
                        {
                            tok = token::Token{token::TokenType::UNDEFINED, std::string(1, _ch)};
                        }
                    }
            }

            this->read_char(); // Get ready for the next call of this->NextToken()
            
            return std::move(tok);
        }
    }
}