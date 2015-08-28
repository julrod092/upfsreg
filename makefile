all: upfsreg

upfsreg: bin src/upfsreg.o
	g++ src/upfsreg.o -o bin/upfsreg -g

upfsreg.o: src/practica.cpp src/input.h
	g++ -c src/upfsreg.cpp

bin:
	mkdir bin

clean:
	rm -rf src/*.o bin/upfsreg

run: upfsreg
	./bin/upfsreg 1 a a1 1000 1 examples/example0.fs
