#include <parser/parser.hpp>

#include <sstream>

namespace lang
{
    namespace parser
    {
        std::unique_ptr<ast::Statement> Parser::parse_let_statement()
        {
            auto statement = std::make_unique<ast::LetStatement>();
            statement->token = _current_token;

            if(!this->expectPeek(token::TokenType::IDENTIFIER))
            {
                return nullptr;
            }

            statement->name = std::make_unique<ast::Identifier>();
            statement->name->token = _current_token;
            statement->name->value = _current_token.value;

            if(!this->expectPeek(token::TokenType::ASSIGN))
            {
                return nullptr;
            }

            /* For now we are skipping the expressions until we encounter a semicolon */
            while(!this->current_token_is(token::TokenType::SEMICOLON))
            {
                this->read_next_token();
            }

            return statement;
        }

        bool Parser::current_token_is(token::TokenType t)
        {
            return _current_token.type == t;
        }

        bool Parser::peek_next_token_is(token::TokenType t)
        {
            return _next_token.type == t;
        }

        bool Parser::expectPeek(token::TokenType t)
        {
            if(this->peek_next_token_is(t))
            {
                this->read_next_token();
                return true;
            }
            else
            {   
                this->add_errors(t);
                return false;
            }
        }

        std::unique_ptr<ast::Statement> Parser::parse_statement()
        {
            switch(_current_token.type)
            {
                case token::TokenType::LET:
                    return this->parse_let_statement();

                default:
                    return nullptr;
            }
        }

        void Parser::read_next_token()
        {
            _current_token = _next_token;
            _next_token = _lexer_ptr->NextToken();
        }

        void Parser::add_errors(token::TokenType t)
        {
            std::stringstream buffer;

            buffer << "Expected next token to be " << token::tokenTypeToString(t) 
                << ", got " << token::tokenTypeToString(_next_token.type) << " instead";
            
            _errors.emplace_back(buffer.str());
        }

        std::pair<ast::Program, std::vector<std::string>> Parser::parse_program()
        {
            ast::Program program;

            while(_current_token.type != token::TokenType::END_OF_FILE)
            {
                auto statement = this->parse_statement();
                if(statement != nullptr)
                {
                    program.statements.push_back(std::move(statement));
                }
                this->read_next_token();
            }

            return std::pair{std::move(program), std::move(_errors)};
        }
    }
}