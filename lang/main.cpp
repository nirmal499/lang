#include <iostream>
#include <repl/repl.hpp>

int main()
{
    std::cout << "Hello, This is the <lang> programming language\n";
    std::cout << "Feel free to type in commands\n";
    lang::repl::start(std::cin, std::cout);
    return 0;
}