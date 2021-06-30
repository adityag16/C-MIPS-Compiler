CPPFLAGS += -std=c++11 -W -Wall -g -Wno-unused-parameter
CPPFLAGS += -I include

all : bin/c_compiler

bin/c_compiler : bin/print_python bin/print_MIPS
	chmod u+x bin/c_compiler c_translator_formative.sh c_compiler_formative.sh

src/C_parser.tab.cpp src/C_parser.tab.hpp : src/C_parser.y
	bison -v -d src/C_parser.y -o src/C_parser.tab.cpp

src/C_lexer.yy.cpp : src/C_lexer.flex src/C_parser.tab.hpp
	flex -o src/C_lexer.yy.cpp  src/C_lexer.flex

bin/print_python : src/print_python.o src/C_parser.tab.o src/C_lexer.yy.o src/C_parser.tab.o
	mkdir -p bin
	g++ $(CPPFLAGS) -o bin/print_python $^

bin/print_MIPS : src/print_MIPS.o src/C_parser.tab.o src/C_lexer.yy.o src/C_parser.tab.o
	mkdir -p bin
	g++ $(CPPFLAGS) -o bin/print_MIPS $^	


clean :
	rm src/*.o
	rm bin/print_python bin/print_MIPS
	rm src/*.tab.cpp
	rm src/*.yy.cpp
	rm -r tmp/
