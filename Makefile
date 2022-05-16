CC=g++ -D_GLIBCXX_DEBUG -O2 -Wall -Wextra -Werror -Wno-sign-compare -std=c++11

all: program.exe clean


program.exe: program.o Classificacio.o Torneig.o Jugador.o
	$(CC) -o program.exe program.o Classificacio.o Torneig.o Jugador.o

program.o: program.cc Jugador.hh Torneig.hh Classificacio.hh Categoria.hh
	$(CC) -c program.cc

Classificacio.o: Classificacio.cc Classificacio.hh
	$(CC) -c Classificacio.cc

Torneig.o: Torneig.cc Torneig.hh 
	$(CC) -c Torneig.cc

Jugador.o: Jugador.cc Jugador.hh Classificacio.hh
	$(CC) -c Jugador.cc

clean:
	rm -f *o
