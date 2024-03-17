set(TEST_MAIN "unit_tests")
set(TEST_SOURCES "main.cc")
set(TEST_INCLUDES "./")

add_executable(${TEST_MAIN} ${TEST_SOURCES})

target_include_directories(${TEST_MAIN} 
    PRIVATE ${TEST_INCLUDES}
)

target_link_libraries(${TEST_MAIN}
	PRIVATE ${LIBRARY_NAME}
	PRIVATE Catch2::Catch2
)