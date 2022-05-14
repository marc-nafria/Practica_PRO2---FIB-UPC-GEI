/** @file ConjuntJugadors.cc
 * @brief Implementació de la classe ConjuntJugadors
 */

#include "ConjuntJugadors.hh"

#include "Jugador.hh"
#include "Classificacio.hh"

#ifndef NO_DIAGRAM
#include <vector>
#include <algorithm>
#include <string>
#include <map>
#endif

using namespace std;

bool ConjuntJugadors::afegir_jugador(string nom_jugador)
{

    if (jugadors.insert(make_pair(nom_jugador, Jugador(nom_jugador,
                                  ranking.size() + 1))).second) {
        ranking.push_back(make_pair(nom_jugador, 0));
        return true;
    }

    return false;
}

bool ConjuntJugadors::borrar_jugador(string nom_jugador)
{
    if (jugadors.erase(nom_jugador)) {
        for (int i = 0; i < ranking.size(); ++i) {
            if (ranking[i].first == nom_jugador) {
                ranking.erase(ranking.begin() + i);

                for (int j = i; j < ranking.size(); ++j) {
                    map<string, Jugador>::iterator it = jugadors.find(ranking[j].first);
                    (*it).second.actualitzar_ranking(j + 1);
                }

                return true;
            }
        }
    }

    return false;
}

void ConjuntJugadors::afegir_classificacio(Classificacio &c)
{
    map<string, Resultat> cl = c.consultar_classificacio();


    for (map<string, Resultat>::iterator it_cl = cl.begin(); it_cl != cl.end();
            ++it_cl) {
        string nom_jugador = (*it_cl).first;

        map<string, Jugador>::iterator it =
            jugadors.find(nom_jugador);

        if (it != jugadors.end()) {
            (*it).second.afegir_resultat((*it_cl).second);
        }
    }
}

void ConjuntJugadors::retirar_classificacio(Classificacio &c)
{
    map<string, Resultat> cl = c.consultar_classificacio();


    for (map<string, Resultat>::iterator it_cl = cl.begin(); it_cl != cl.end();
            ++it_cl) {
        string nom_jugador = (*it_cl).first;

        map<string, Jugador>::iterator it =
            jugadors.find(nom_jugador);

        if (it != jugadors.end()) {
            (*it).second.retirar_resultat((*it_cl).second);
        }
    }
}

void ConjuntJugadors::escriure_ranking() const
{
    for (int i = 0; i < ranking.size(); ++i) {
        map<string, Jugador>::const_iterator it =
            jugadors.find(ranking[i].first);

        cout << i + 1 << " " << ranking[i].first << " "
             << ranking[i].second << endl;
    }
}

void ConjuntJugadors::escriure_jugadors() const
{
    cout << jugadors.size() << endl;

    for (map<string, Jugador>::const_iterator it = jugadors.begin();
            it != jugadors.end(); ++it) {
        (*it).second.escriure_estadistiques();
    }
}

bool ConjuntJugadors::escriure_jugador(string nom_jugador) const
{

    map<string, Jugador>::const_iterator it =
        jugadors.find(nom_jugador);

    if (it == jugadors.end()) {
        return false;
    }

    (*it).second.escriure_estadistiques();

    return true;
}

vector<pair<string, int> > ConjuntJugadors::consultar_ranking() const
{
    return ranking;
}


void ConjuntJugadors::actualitzar_ranking() 
{
    for (int i = 0; i < ranking.size(); ++i) {
        map<string, Jugador>::const_iterator it =
            jugadors.find(ranking[i].first);

        ranking[i].second = (*it).second.consultar_punts();
    }
    
    ordenar_ranking();
    informar_ranking();
}

void ConjuntJugadors::ordenar_ranking()
{
    // Utilitzarem el bubble sort
    int n = ranking.size();
    int i, j;
    bool canviat = true;
    for (i = 0; i < n - 1 and canviat; i++) {
        canviat = false;
        for (j = 0; j < n - i - 1; j++)
            if (ranking[j].second < ranking[j + 1].second) {
                pair<string, int> aux = ranking[j];
                ranking[j] = ranking[j + 1];
                ranking[j + 1] = aux;
                canviat = true;
            }
    }
}

void ConjuntJugadors::informar_ranking()
{
    for (int i = 0; i < ranking.size(); ++i) {
        map<string, Jugador>::iterator it = jugadors.find(ranking[i].first);

        (*it).second.actualitzar_ranking(i + 1);
    }
}
