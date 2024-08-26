cmake_minimum_required(VERSION 3.0)

# enable C++11 and warnings
set(CMAKE_CXX_FLAGS "--std=gnu++11 ${CMAKE_CXX_FLAGS}")
set(CMAKE_CXX_FLAGS "-Wall ${CMAKE_CXX_FLAGS}")
#set(CMAKE_CXX_FLAGS "-fsanitize=address ${CMAKE_CXX_FLAGS}")

find_package(GTest)
find_package(BISON)
find_package(FLEX)
find_package(Boost COMPONENTS system)
include_directories(${Boost_INCLUDE_DIRS})

include_directories(.)
include_directories(./src)
include_directories(./test)

############################################################################

# parser generation
set(ParserDir "./src/clike")
flex_target(ClikeScanner ${ParserDir}/lexer.l ${ParserDir}/lexer.cpp)
bison_target(ClikeParser ${ParserDir}/parser.yy ${ParserDir}/parser.cpp DEFINES_FILE ${ParserDir}/parser.h VERBOSE REPORT_FILE ${ParserDir}/parser_report.txt)
add_flex_bison_dependency(ClikeScanner ClikeParser)

set(ParserSources
  ${FLEX_ClikeScanner_OUTPUTS}
  ${BISON_ClikeParser_OUTPUTS}
  src/clike/integer_parser.cpp
  src/clike/constant_value_literal.cpp
  src/clike/external_variables.cpp
  src/clike/ast_type.cpp
  src/clike/ast_builder.cpp
)

set(ParserLibrary parser)
add_library(${ParserLibrary} STATIC ${ParserSources})

############################################################################

set(CmdSources
  test/test_common.cpp # todo: temp for testing
  src/cmd_main.cpp
)

set(CmdLibraries
  ${ParserLibrary}
)

set(TestSources
  test/test_common.cpp
  test/test_basic.cpp
  test/test_integer.cpp
)

set(TestLibraries
  ${ParserLibrary}
  GTest::GTest
  GTest::Main
)

############################################################################

# unit tests
set(TestExecutable run_tests)
add_executable(${TestExecutable} ${TestSources})
target_link_libraries(${TestExecutable} ${TestLibraries})

# command line interface
set(CmdExecutable cmd)
add_executable(${CmdExecutable} ${CmdSources})
target_link_libraries(${CmdExecutable} ${CmdLibraries})

