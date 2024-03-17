set(TEST_MAIN "unit_tests")

set(LEXER_TEST "lexer_test.cpp")

add_executable(${TEST_MAIN} ${LEXER_TEST})

target_link_libraries(${TEST_MAIN}
	PRIVATE ${LIBRARY_NAME}
)