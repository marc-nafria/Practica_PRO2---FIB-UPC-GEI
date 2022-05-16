#include "Classificacio.hh"
#include "Resultat.hh"

#include <vector>
#include <map>
#include <string>

using namespace std;

void Classificacio::copiar_classificacio (const Classificacio &copia) {
    jugadors.clear();
    
    this->jugadors = copia.jugadors;
}

void Classificacio::afegir_partit(
    string nom_jugador, int jocs_favor, int jocs_contra,
    int sets_favor, int sets_contra, int resultat_partit) {

    /* sumem les estadístiques del partit a les del jugadors */
    jugadors[nom_jugador].jocs_favor += jocs_favor;
    jugadors[nom_jugador].jocs_contra += jocs_contra;
    jugadors[nom_jugador].sets_favor += sets_favor;
    jugadors[nom_jugador].sets_contra += sets_contra;

    if (resultat_partit == 1) {
        jugadors[nom_jugador].partits_favor += 1;
    }
    else if (resultat_partit == -1) {
        jugadors[nom_jugador].partits_contra += 1;
    }
}

void Classificacio::establir_punts(string nom_jugador, int punts)
{
    jugadors[nom_jugador].punts = punts;
}

void Classificacio::borrar_jugador(string nom_jugador) {
    /* borrem el jugado corresponent */
    jugadors.erase(nom_jugador);
}

map<string, Resultat> Classificacio::consultar_classificacio() const {
    return jugadors;
}

void Classificacio::borrar_classificacio() {
    /* borrem tot el diccionari ijuagdors */
    jugadors.clear();
}

