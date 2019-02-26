CXX = g++ -std=c++17 -Wall

default: Lexer

headers: src/analyze.hpp src/delimiters.hpp src/identifiers.hpp src/keywords.hpp src/operators.hpp src/separators.hpp

Lexer: headers src/main.cpp
	${CXX} src/main.cpp -o bin/Lexer

clean:
	rm -rf bin/Lexer
