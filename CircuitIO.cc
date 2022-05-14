#include "CircuitIO.hh"
#include "ConjuntJugadors.hh"
#include "ConjuntTornejos.hh"

#include <iostream>
#include <vector>

using namespace std;

void llegir_conjunt_categories(vector<Categoria> &categories, int C, int K) {
    /* inicialitzem el vector amb una mida C */
    categories = vector<Categoria>(C);

    string nom_categoria;

    for (int i = 0; i < C; ++i) {
        /* per a cada categoria, llegim el nom, i inicialitzem
        el seu vector punts_per_nivell amb una mida de K */
        cin >> nom_categoria;
        categories[i].nom = nom_categoria;
        categories[i].punts_per_nivell = vector<int>(K);
    }

    int punts;

    for (int i = 0; i < C; ++i)
        /* per a cada categoria llegim els seus punts per 
        nivell */
        for (int j = 0; j < K; ++j) {
            cin >> punts;
            categories[i].punts_per_nivell[j] = punts;
        }

}

void llegir_conjunt_tornejos(ConjuntTornejos &tornejos, int T,
                             const vector<Categoria> &categories) {
    /* afegim els tornejos un a un llegint de la entrada el seu
    nom i la seva categoria */
    for (int i = 0; i < T; ++i) {
        string nom_torneig;
        cin >> nom_torneig;

        int id_categoria;
        cin >> id_categoria;

        tornejos.afegir_torneig(nom_torneig, categories[id_categoria - 1]);
    }
}

void llegir_conjunt_jugadors(ConjuntJugadors &jugadors, int J) {
    string nom_jugador;

    /* afegim cada jugador llegint el seu nom, i el Conjunt Jugadors
    jugadors ja els iniciailtzara a 0 */
    for (int i = 0; i < J; ++i) {
        cin >> nom_jugador;
        jugadors.afegir_jugador(nom_jugador);
    }
}

void llistar_conjunt_categories(const vector<Categoria> &categories, int C, int K) {
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




