/** @mainpage Practicà Pro 2: Gestió d'un circuit de Tennis
 *
 * En aquesta resolució del problema, he definit classes per a representar un
 * Jugador, un ConjuntJugadors, un Torneig, un ConjuntTornejos i una
 * Classificacio. He pensat que conceptes com una Categoria i un Resultat no
 * necessitaven ser classes, ja que no tenien mètodes propis, sino que només
 * emmagatzemaven informació. Per això les he definit com a estructures (struc).
 * A'més, en les classes que representen conjunts faig us de diccionaris per a
 * trobar més facilment els objectes. Aquestes classes serveixen per a executar
 * mètodes dels objectes que contenen, principalment. També utilitzo els
 * BinTree, que he agafat d'altres practiques anteriors.
 */

/** @file main.cc
    @brief Implementacio del programa principal
*/

#include "ConjuntJugadors.hh"

#include "ConjuntTornejos.hh"

#include "CircuitIO.hh"

#ifndef NO_DIAGRAM
#include "Categoria.hh"
#include "Classificacio.hh"
#include "Jugador.hh"
#include "Resultat.hh"
#include "Torneig.hh"

#include <iostream>
#include <map>
#include <vector>
//#include <ctime>
#endif

using namespace std;

int main()
{

    /* llegim nombre de categories */
    int C;
    cin >> C;

    /* llegim nombre maxim nivells */
    int K;
    cin >> K;

    /* llegim C strings (identificadors de categories */
    vector<Categoria> categories;
    llegir_conjunt_categories(categories, C, K);  /* especificat a CircuitIO.hh*/

    /* llegim nombre de tornejos */
    int T;
    cin >> T;

    /* llegim T parells de de string t i enter c (nom torneig, categoria) */
    ConjuntTornejos tornejos;
    llegir_conjunt_tornejos(tornejos, T,
                            categories); /* especificat a CircuitIO.hh */

    /* llegim nombre de jugadors */
    int J;
    cin >> J;

    /* llegim P strings, identificadors jugadors */
    ConjuntJugadors jugadors;
    llegir_conjunt_jugadors(jugadors, J);

    /* -----------------------------------------------------------------------------*/
    /*            a partir d'aqui comencem a llegir les instruccions */
    /* -----------------------------------------------------------------------------*/

    string instruccio;
    cin >> instruccio;

    while (instruccio != "fin") {

        cout << "#" << instruccio;

        if (instruccio == "nuevo_jugador" or instruccio == "nj") {
            string nom_jugador;
            cin >> nom_jugador;

            cout << " " << nom_jugador << endl;

            if (jugadors.afegir_jugador(nom_jugador)) {
                ++J;
                cout << J << endl;
            }
            else {
                cout << "error: ya existe un jugador con ese nombre" << endl;
            }
        }
        else if (instruccio == "nuevo_torneo" or instruccio == "nt") {
            string nom_torneig;
            cin >> nom_torneig;

            int id_categoria;
            cin >> id_categoria;

            cout << " " << nom_torneig << " " << id_categoria << endl;

            if (id_categoria >= 1 and id_categoria <= C) {
                /* existeix categoria */
                if (tornejos.afegir_torneig(nom_torneig,
                                            categories[id_categoria - 1])) {
                    /* el troneig s'ha afegit */
                    ++T;
                    cout << T << endl;
                }
                else {
                    cout << "error: ya existe un torneo con ese nombre" << endl;
                }
            }
            else {
                cout << "error: la categoria no existe" << endl;
            }
        }
        else if (instruccio == "baja_jugador" or instruccio == "bj") {
            string nom_jugador;
            cin >> nom_jugador;

            cout << " " << nom_jugador << endl;

            if (jugadors.borrar_jugador(nom_jugador)) {
                tornejos.borrar_jugador(nom_jugador);
                --J;
                cout << J << endl;
            }
            else {
                cout << "error: el jugador no existe" << endl;
            }
        }
        else if (instruccio == "baja_torneo" or instruccio == "bt") {
            string nom_torneig;
            cin >> nom_torneig;

            cout << " " << nom_torneig << endl;

            Classificacio darrera_classificacio;

            if (tornejos.borrar_torneig(nom_torneig, darrera_classificacio)) {
                /* retirem els punts obtinguts a la darrera classificacio del
                 * torneig */
                jugadors.retirar_classificacio(darrera_classificacio);
                jugadors.actualitzar_ranking();
                --T;
                cout << T << endl;
            }
            else {
                cout << "error: el torneo no existe" << endl;
            }
        }
        else if (instruccio == "iniciar_torneo" or instruccio == "it") {
            string nom_torneig;
            cin >> nom_torneig;

            cout << " " << nom_torneig << endl;

            tornejos.iniciar_torneig(
                nom_torneig,
                jugadors.consultar_ranking()); /* ens garantitzen que el torneig
                                                 existeix */
        }
        else if (instruccio == "finalizar_torneo" or instruccio == "ft") {
            string nom_torneig;
            cin >> nom_torneig;

            cout << " " << nom_torneig << endl;

            Classificacio darrera_classificacio;
            Classificacio fi_torneig = tornejos.finalitzar_torneig(nom_torneig,
                darrera_classificacio);

            jugadors.retirar_classificacio(darrera_classificacio);
            jugadors.afegir_classificacio(fi_torneig);
            jugadors.actualitzar_ranking();
        }
        else if (instruccio == "listar_ranking" or instruccio == "lr") {
            cout << endl;
            jugadors.escriure_ranking();
        }
        else if (instruccio == "listar_jugadores" or instruccio == "lj") {
            cout << endl;
            jugadors.escriure_jugadors();
        }
        else if (instruccio == "consultar_jugador" or instruccio == "cj") {
            string nom_jugador;
            cin >> nom_jugador;

            cout << " " << nom_jugador << endl;

            if (!jugadors.escriure_jugador(nom_jugador)) {
                cout << "error: el jugador no existe" << endl;
            }
        }
        else if (instruccio == "listar_torneos" or instruccio == "lt") {
            cout << endl;
            tornejos.escriure_tornejos();
        }
        else if (instruccio == "listar_categorias" or instruccio == "lc") {
            cout << endl;
            llistar_conjunt_categories(categories, C,
                                       K); /* especificat a CircuitIO.hh */
        }

        /* i per ultim llegim la seguent instruccio */
        cin >> instruccio;
    }
}
