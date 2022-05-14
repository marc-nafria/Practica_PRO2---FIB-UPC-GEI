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

    /* busquem al jugador corresponent */
    map<string, Resultat>::iterator it = jugadors.find(nom_jugador);

    /* ens assegurem que ja el tenim. Si fós el primer cop que
    s'afegiex un partit d'aquest jugador l'hem d'afegir al diccionari */
    if (it == jugadors.end()) {
        Resultat r;
        it = jugadors.insert(it, make_pair(nom_jugador, r));
    }

    /* sumem les estadístiques del partit a les del jugadors */
    (*it).second.jocs_favor += jocs_favor;
    (*it).second.jocs_contra += jocs_contra;
    (*it).second.sets_favor += sets_favor;
    (*it).second.sets_contra += sets_contra;

    if (resultat_partit == 1) {
        (*it).second.partits_favor += 1;
    }
    else if (resultat_partit == -1) {
        (*it).second.partits_contra += 1;
    }
}

bool Classificacio::establir_punts(string nom_jugador, int punts)
{
    /* busquem al jugador en qüestió */
    map<string, Resultat>::iterator it = jugadors.find(nom_jugador);

    /* assegurem que existeixi, tot i que en teoria no fa falta */
    if (it == jugadors.end()) {
        return false;
    }

    /* només actualitzem els punts en el cas de que siguin més 
    que els que ja té, i retornem s'hi s'han actualitzat o no */
    if ((*it).second.punts >= punts) return false;
    (*it).second.punts = punts;
    return true;
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

