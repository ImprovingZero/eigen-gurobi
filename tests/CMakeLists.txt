cmake_minimum_required(VERSION 3.1)
################################################################################

add_executable(${PROJECT_NAME}_tests
    main.cpp
    QPTest.cpp
)

# Catch2
target_link_libraries(${PROJECT_NAME}_tests PUBLIC ${PROJECT_NAME} Catch2::Catch2)

foreach(source IN ITEMS ${test_sources})
   source_group("tests" FILES "${source}")
endforeach()

# Register tests
set(PARSE_CATCH_TESTS_ADD_TO_CONFIGURE_DEPENDS ON)
include(Catch)
catch_discover_tests(${PROJECT_NAME}_tests)
