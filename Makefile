exec: clean compile bin/patoos src/main.o src/ansilib.o src/tableslib.o src/processmanagementlib.o run

compile:
	echo "Starting compilation..."

bin/patoos: src/main.o src/ansilib.o src/tableslib.o src/processmanagementlib.o
	echo "Linking"
	gcc -o bin/patoos $^

src/main.o: src/main.c include/ansilib.h include/tableslib.h include/colorslib.h include/processmanagementlib.h
	echo "Compiling main.c"
	gcc -c src/main.c -o src/main.o -I./include -I./src

src/ansilib.o: src/ansilib.c include/ansilib.h
	echo "Compiling ansilib.c"
	gcc -c src/ansilib.c -o src/ansilib.o -I./include -I./src

src/tableslib.o: src/tableslib.c include/tableslib.h
	echo "Compiling tableslib.c"
	gcc -c src/tableslib.c -o src/tableslib.o -I./include -I./src

src/colorslib.o: include/colorslib.h
	echo "Compiling colorslib.h"
	gcc -c -I./include

src/processmanagementlib.o: src/processmanagementlib.c include/processmanagementlib.h
	echo "Compiling processmanagementlib.c"
	gcc -c src/processmanagementlib.c -o src/processmanagementlib.o -I./include -I./src

clean:
	test -e "bin/patoos" && rm bin/patoos || echo "The main file does not exist. Skipping clean..."

run:
	bin/patoos

all: compile run
