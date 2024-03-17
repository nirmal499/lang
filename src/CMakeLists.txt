
add_library(${LIBRARY_NAME} STATIC 
    token/token.cpp
    lexer/lexer.cpp
    repl/repl.cpp
    parser/parser.cpp 
    ast/ast.cpp
)

target_include_directories(${LIBRARY_NAME}
	PUBLIC "token/include"
	PUBLIC "lexer/include"
	PUBLIC "repl/include"
	PUBLIC "parser/include"
	PUBLIC "ast/include"
)