exec: clean compile bin/patoos src/main.o src/ansilib.o run

compile:
	echo "Starting compilation..."

bin/patoos: src/main.o src/ansilib.o
	echo "Linking"
	gcc -o bin/patoos $^

src/main.o: src/main.c include/ansilib.h
	echo "Compiling main.c"
	gcc -c src/main.c -o src/main.o -I./include -I./src

src/ansilib.o: src/ansilib.c include/ansilib.h
	echo "Compiling ansilib.c"
	gcc -c src/ansilib.c -o src/ansilib.o -I./include -I./src

clean:
	test -e "bin/patoos" && rm bin/patoos || echo "The main file does not exist. Skipping clean..."

run:
	bin/patoos

all: compile run