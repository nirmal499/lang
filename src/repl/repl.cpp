#include <repl/repl.hpp>

#include <token/token.hpp>
#include <lexer/lexer.hpp>

namespace lang
{
    namespace repl
    {

        void start(std::istream& cin, std::ostream& cout)
        {
            const char* PROMPT = ">> ";
            std::string line{};

            while(true)
            {
                std::cout << PROMPT;
                std::getline(std::cin, line);
                if(line.empty())
                {
                    break;
                }

                lang::lexer::Lexer lexer(line);
                auto tok = lexer.NextToken();
                while(tok.type != lang::token::TokenType::END_OF_FILE)
                {
                    std::cout << tok;
                    tok = lexer.NextToken();
                }
            }
        }
    }
}