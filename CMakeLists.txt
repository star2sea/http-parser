cmake_minimum_required(VERSION 2.6)
project(http_parser)

set(SRC_C parser/http_parser.h parser/http_parser.c)
set(SRC_CPP httpparser.h httpparser.cpp httpmessage.h httpmessage.cpp)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

include_directories(${PROJECT_SOURCE_DIR})

add_library(http_parser STATIC ${SRC_C} ${SRC_CPP})

add_executable(httpparser_test test/test.cpp)
target_link_libraries(httpparser_test http_parser)


install(FILES parser/http_parser.h DESTINATION include/http_parser/parser)
install(FILES httpmessage.h httpparser.h DESTINATION include/http_parser)

install(TARGETS http_parser DESTINATION lib)