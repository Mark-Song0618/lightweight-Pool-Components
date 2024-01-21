add_executable(smoke_test test.cpp "http.h" "http.cpp")

target_link_libraries( smoke_test pool_util)

target_include_directories(smoke_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../src 	${INSTALL_INCLUDEDIR})

add_test(
NAME
	smoke_test
COMMAND
	smoke_test
)

set_tests_properties(
	smoke_test
	PROPERTIES
	PASS_REGULAR_EXPRESSION
	"PASSED"
	FAIL_REGULAR_EXPRESSION
	"FAILED"
)