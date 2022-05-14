CC=g++ -D_GLIBCXX_DEBUG -O2 -Wall -Wextra -Werror -Wno-sign-compare -std=c++11

program.exe: program.o Classificacio.o CircuitIO.o ConjuntTornejos.o ConjuntJugadors.o Torneig.o Jugador.o
	$(CC) -o program.exe *.o

program.o: program.cc ConjuntTornejos.hh ConjuntJugadors.hh Jugador.hh Torneig.hh CircuitIO.hh Classificacio.hh Categoria.hh Resultat.hh
	$(CC) -c program.cc

Classificacio.o: Classificacio.cc Classificacio.hh Resultat.hh
	$(CC) -c Classificacio.cc

CircuitIO.o: CircuitIO.cc CircuitIO.hh ConjuntJugadors.hh ConjuntTornejos.hh 
	$(CC) -c CircuitIO.cc

ConjuntTornejos.o: ConjuntTornejos.cc ConjuntTornejos.hh Torneig.hh Classificacio.hh
	$(CC) -c ConjuntTornejos.cc

ConjuntJugadors.o: ConjuntJugadors.cc ConjuntJugadors.hh Jugador.hh Classificacio.hh
	$(CC) -c ConjuntJugadors.cc

Torneig.o: Torneig.cc Torneig.hh 
	$(CC) -c Torneig.cc

Jugador.o: Jugador.cc Jugador.hh
	$(CC) -c Jugador.cc

clean:
	rm -f *.o
