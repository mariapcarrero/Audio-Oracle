cmake_minimum_required(VERSION 3.10)
project(FactorOracleString)

set(CMAKE_CXX_STANDARD 11)

add_library(FO FactorOracle.cpp FactorOracle.h)
add_executable(FactorOracleString main.cpp)
add_executable(TestLCS catch2.hpp catch.hpp test_lcs.cpp )
add_executable(TestAddLetter catch2.hpp catch.hpp test_add_letter.cpp)
add_executable(TestFindBetter catch2.hpp catch.hpp test_find_better.cpp)
add_executable(TestFOS catch2.hpp catch.hpp test_fos.cpp)
target_link_libraries(FactorOracleString FO)
target_link_libraries(TestLCS FO)
target_link_libraries(TestAddLetter FO)
target_link_libraries(TestFindBetter FO)
target_link_libraries(TestFOS FO)
function(SIMPLE SETUPFO)
    target_compile_options(${SETUPFO} PUBLIC -fsanitize=address)
    target_link_libraries(${SETUPFO} -fsanitize=address)
endfunction()

function(TESTS TestName)
    add_test(NAME ${TestName}_ COMMAND ${TestName})
endfunction()

tests(TestLCS)
tests(TestAddLetter)
tests(TestFindBetter)
tests(TestFOS)
simple(FactorOracleString)
simple(TestLCS)
simple(TestAddLetter)
simple(TestFindBetter)
simple(TestFOS)