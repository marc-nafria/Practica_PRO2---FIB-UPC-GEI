/** @mainpage Practicà Pro 2: Gestió d'un circuit de Tennis
Per a la resolució del problema:
+ he definit **classes** per a representar un Jugador, un Torneig i una Classificació. 
+ he definit **estructures** per a respresentar un Resultat i una Categoria.

Utilitzo **diccionaris** per a emmagatzemar el *jugadors* i els
*tornejos*, ja que així és més ràpid consultar-los en funció
del nom. El vector *ranking* conté el ranking del circuit, com 
un vector de parells (string, int) indicant el nom del jugadors
i els punts que tenen.
*/

/** @file main.cc
    @brief Implementacio del programa principal
*/


#include "Categoria.hh"
#include "Classificacio.hh"
#include "Jugador.hh"
#include "Torneig.hh"

#ifndef NO_DIAGRAM
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#endif

using namespace std;

map<string, Jugador> jugadors;  /**< Diccionari que emmagatzema als jugadors */
map<string, Torneig> tornejos;  /**< Diccionari que emmagatzema els tornejos */
vector<Categoria> categories;   /**< Vector que conté les categories */
vector<pair<string, int>> ranking; /**< Vector que conté el ranking */


/** @brief Actualitza el ranking del circuit i 
 * informa als jugadors de la posicio actual.
 * pre: Cert.
 * post: S'actualitza el ranking i es comunica a cada
 * jugador la seva nova posició.
 */
void actualitzar_ranking() 
{
    /* obtenim els punts de cada jugador */
    for (int i = 0; i < ranking.size(); ++i) {
        ranking[i].second = jugadors[ranking[i].first].consultar_punts();
    }
    
    /* Utilitzarem el bubble sort */
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

    /* comuniquem a cada jugador la seva nova posicio */
    for (int i = 0; i < ranking.size(); ++i) {
        jugadors[ranking[i].first].actualitzar_ranking(i + 1);
    }
}

int main()
{

    /* llegim nombre de categories */
    int C;
    cin >> C;
    categories = vector<Categoria>(C);

    /* llegim nombre maxim nivells */
    int K;
    cin >> K;

    /* llegim C strings i C*K enters */
    for (int i = 0; i < C; ++i) {
        string nom_categoria;

        /* per a cada categoria, llegim el nom, i inicialitzem
        el seu vector punts_per_nivell amb una mida de K */
        cin >> nom_categoria;
        categories[i].nom = nom_categoria;
        categories[i].punts_per_nivell = vector<int>(K);
    }

    for (int i = 0; i < C; ++i) {
        int punts;

        /* per a cada categoria llegim els seus punts per 
        nivell */
        for (int j = 0; j < K; ++j) {
            cin >> punts;
            categories[i].punts_per_nivell[j] = punts;
        }
    }

    /* llegim nombre de tornejos */
    int T;
    cin >> T;

    /* llegim T parells de de string t i enter c (nom torneig, categoria) */
    for (int i = 0; i < T; ++i) {
        string nom_torneig;
        cin >> nom_torneig;

        int id_categoria;
        cin >> id_categoria;

        /* i afegim el torneig al diccionari */
        tornejos.insert(make_pair(nom_torneig, Torneig(categories[id_categoria - 1])));
    }

    /* llegim nombre de jugadors */
    int J;
    cin >> J;

    /* llegim P strings, identificadors jugadors */
    for (int i = 0; i < J; ++i) {
        string nom_jugador;
        cin >> nom_jugador;

        /* afegim el jugadors al diccionari i al final del ranking */
        jugadors.insert(make_pair(nom_jugador, Jugador(nom_jugador, ranking.size() + 1)));
        ranking.push_back(make_pair(nom_jugador, 0));
    }

    /* -----------------------------------------------------------------------------*/
    /*            a partir d'aqui comencem a llegir les instruccions                */
    /* -----------------------------------------------------------------------------*/

    string instruccio;
    cin >> instruccio;

    while (instruccio != "fin") {

        /* treiem l'entrada comentada (cada intrucció afegirà el que queda
        d'instrucció) */
        cout << "#" << instruccio;

        if (instruccio == "nuevo_jugador" or instruccio == "nj") {
            string nom_jugador;
            cin >> nom_jugador;

            cout << " " << nom_jugador << endl;

            if (jugadors.insert(make_pair(nom_jugador,
                Jugador(nom_jugador, ranking.size() + 1))).second) {

                /* si al afegir el jugadors al diccionari aquest no hi 
                estava, l'afegim al ranking */
                ranking.push_back(make_pair(nom_jugador, 0));
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
                if (tornejos.insert(make_pair(nom_torneig, Torneig(categories[id_categoria - 1]))).second) {
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

            /* buquem el jugador en el diccionari */
            map<string, Jugador>::iterator it =
                jugadors.find(nom_jugador);

            if (it != jugadors.end()) {

                /* si el trobem, el borrem abans de tots els tornejos */
                map<string, Torneig>::iterator it_t;
                for (it_t = tornejos.begin(); it_t != tornejos.end(); ++it_t) {
                    (*it_t).second.borrar_jugador(nom_jugador);
                }

                /* i a tots els jugadors que estaven per sota en el ranking 
                els hi hem d'avançar un posició */
                int r = (*it).second.consultar_ranking();
                ranking.erase(ranking.begin() + r);
                for (int j = r; j < ranking.size(); ++j) {
                    jugadors[ranking[j].first].actualitzar_ranking(j + 1);
                }

                /* finalment el borrem del diccionari */
                jugadors.erase(nom_jugador);

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

            map<string, Torneig>::const_iterator it = tornejos.find(nom_torneig);

            if (it != tornejos.end()) {
                /* si el trobem, hem de fer algunes coses abans de borrar-lo */

                /* en primer lloc retirem del circuit la última classificació 
                del torneig, com a un diccionari de string i Resultat */
                map<string, Resultat> cl = (*it).second.consultar_darrera_classificacio().consultar_classificacio();

                /* el recorrem i afegim cada resultat al jugador corresponent */
                for (map<string, Resultat>::const_iterator it_cl = cl.begin(); it_cl != cl.end();
                        ++it_cl) {

                    jugadors[(*it_cl).first].retirar_resultat((*it_cl).second);
                }

                /* ara ja el podem borrar */
                tornejos.erase(it);

                /* i actualitzem el ranking per que hi poden
                haver jugadors que hagin perdut punts */
                actualitzar_ranking();

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

            /* iniciem el torneig (nom_torneig) */
            tornejos[nom_torneig].iniciar_torneig(ranking);
        }
        else if (instruccio == "finalizar_torneo" or instruccio == "ft") {
            string nom_torneig;
            cin >> nom_torneig;

            cout << " " << nom_torneig << endl;

            /* copiem la classificació com un diccionari de string i resultat */
            map<string, Resultat> darrera_classificacio = 
                tornejos[nom_torneig].consultar_darrera_classificacio().consultar_classificacio();

            /* el recorrem i afegim cada resultat al jugador corresponent */
            for (map<string, Resultat>::const_iterator it = darrera_classificacio.begin(); it != darrera_classificacio.end();
                    ++it) {

                jugadors[(*it).first].retirar_resultat((*it).second);
            }

            /* obtenim la classificació resultant al finalitzar el torneig, com un diccionari
            de string i Resultat */
            map<string, Resultat> fi_torneig = tornejos[nom_torneig].finalitzar_torneig().consultar_classificacio();

            /* el recorrem i afegim cada resultat al jugador corresponent */
            for (map<string, Resultat>::const_iterator it = fi_torneig.begin(); it != fi_torneig.end();
                    ++it) {

                jugadors[(*it).first].afegir_resultat((*it).second);
            }

            /* actulitzem el ranking perque els punts dels jugadors
            poden haver canviat */
            actualitzar_ranking();
        }
        else if (instruccio == "listar_ranking" or instruccio == "lr") {
            cout << endl;

            /* recorrem el ranking i imprimim els valors */
            for (int i = 0; i < ranking.size(); ++i) {
                cout << i + 1 << " " << ranking[i].first << " "
                     << ranking[i].second << endl;
            }
        }
        else if (instruccio == "listar_jugadores" or instruccio == "lj") {
            cout << endl;

            /* escribim el total de jugadors */
            cout << jugadors.size() << endl;

            /* i en ordre els anem escrint un a un */
            for (map<string, Jugador>::const_iterator it = jugadors.begin();
                    it != jugadors.end(); ++it) {
                (*it).second.escriure_estadistiques();
            }
        }
        else if (instruccio == "consultar_jugador" or instruccio == "cj") {
            string nom_jugador;
            cin >> nom_jugador;

            cout << " " << nom_jugador << endl;

            /* busquem el jugador dins de diccionari */
            map<string, Jugador>::const_iterator it =
            jugadors.find(nom_jugador);

            if (it == jugadors.end()) {
                cout << "error: el jugador no existe" << endl;
            }
            else {
                /* si el trobem escribim les seves estadístiques al
                output */
                (*it).second.escriure_estadistiques();
            }
        }
        else if (instruccio == "listar_torneos" or instruccio == "lt") {
            cout << endl;

            cout << tornejos.size() << endl;

            /* recorrem el diccionari i els anem imprimint */
            for (map<string, Torneig>::const_iterator it = tornejos.begin();
                    it != tornejos.end(); ++it) {

                cout << (*it).first << " " << (*it).second.consultar_nom_categoria() << endl;
            }
        }
        else if (instruccio == "listar_categorias" or instruccio == "lc") {
            cout << endl;
            
            /* imprimim els valors C i K amb el format corresponent */
            cout << C << " " << K << endl;

            for (int i = 0; i < C; ++i) {
                /* per a cada categoria imprimim el seu nom, i iterem en
                punts_per_nivell per a imprimir cada valor */
                cout << categories[i].nom;

                for (int j = 0; j < K; ++j) {
                    cout << " " << categories[i].punts_per_nivell[j];
                }

                cout << endl;
            }
        }

        /* i per ultim llegim la seguent instruccio */
        cin >> instruccio;
    }
}
