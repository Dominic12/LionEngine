cmake_minimum_required(VERSION 3.15)
project(LionV8)

set(CMAKE_CXX_STANDARD 20)

add_executable(LionV8 main.cpp tokenizer/tokenizer.cpp tokenizer/token.cpp helpers/Logger.cpp helpers/Logger.h parser/Parser.cpp parser/Parser.h parser/AbstractSyntaxTree.h)