#include "Torneig.hh"

#include <vector>
#include <iostream>
#include <string>

Torneig::Torneig(Categoria categoria_torneig) {
    this->categoria = categoria_torneig;
}
void Torneig::iniciar_torneig(const vector<pair<string, int> > &ranking) {
    /* entre un nombre n */
    int n;
    cin >> n;
    
    /* inicialitzem el ranking */
    this->ranking = vector<string>(n);

    /* i hi copiem els respectius jugadors */
    for (int i = 0; i < n; ++i) {
        int ordre;
        cin >> ordre;
        this->ranking[i] = ranking[ordre - 1].first;
    }

    /* ara contruim el arbre d'emparellament, que ja treurà l'output */
    construir_arbre_emparellaments(arbre_emparellaments, 1, 2, n);
    cout << endl;
}
Classificacio Torneig::finalitzar_torneig() {
    /* borrem la nova classificació ja que pot quedar-hi algo
    de l'última edició del torneig */
    nova_classificacio.borrar_classificacio();

    /* inicialitzem l'arbre que emmagatzema els resultats com
    un arbre buit */
    arbre_resultat = BinTree<string>();

    /* llegim es resultats dels partits i els guardem a l'arbre */
    llegir_arbre_resultat(arbre_resultat);

    /* en base als resultats llegits, actulitzem l'arbre d'emparellaments
    amb cada guanyador de cada partit */

    ranking_punts = vector<int> (ranking.size());
    modificar_arbre_emparellaments(arbre_emparellaments, arbre_resultat, 0);

    /* escribim l'output de la funció amb l'ajuda dels dos arbres */
    escriure_arbres(arbre_emparellaments, arbre_resultat);
    cout << endl;

    /* escribim els punts de cada jugador per ordre del ranking en el
    moment de començar el torneig */
    escriure_ranking();
    
    /* en acabar el torneig, la nova classificació a es la darrera */
    darrera_classificacio.copiar_classificacio(nova_classificacio);

    /* i retornem la classificació per que es puguin actualitzar els 
    jugadors des del programa principal */
    return nova_classificacio;
}
void Torneig::borrar_jugador(string nom_jugador) {
    this->darrera_classificacio.borrar_jugador(nom_jugador);
}

/* ------------------Arbre d'emparells-------------------*/
void Torneig::modificar_arbre_emparellaments(BinTree<int> &a, const BinTree<string> &b, int nivell)  {
    /* cas base, arribem a una fulla */
    if (a.left().empty() and a.right().empty()) {
        nova_classificacio.establir_punts(ranking[a.value() - 1],
        categoria.punts_per_nivell[nivell]);
        ranking_punts[a.value() - 1] = categoria.punts_per_nivell[nivell];
        return;
    }

    /* si no modifiquem els subarbres dret i esquerre */
    BinTree<int> left = a.left();
    BinTree<int> right = a.right();

    modificar_arbre_emparellaments(left, b.left(), nivell + 1);
    modificar_arbre_emparellaments(right, b.right(), nivell + 1);
    
    /* el valor de la arrel es el guanyador dels dos jugadors
    que s'enfronten. Un el trobem a la esquerra i l'altre a la dreta */
    int guanyador = llegir_partit(left.value(), right.value(), b.value());
    a = BinTree<int>(
        guanyador,
        left,
        right);

    /* i al guanyador li actualitzem els punts en funció del nivell en el que estem,
    d'aquesta manera assegurem que, al llegir-lo en postordre, al final de recorre'l,
    cada jugadors tindrà els punts del nivell més alt en el que hagi guanyat */
    nova_classificacio.establir_punts(ranking[guanyador - 1],
        categoria.punts_per_nivell[nivell]);
    ranking_punts[guanyador - 1] = categoria.punts_per_nivell[nivell];

}
void Torneig::construir_arbre_emparellaments(BinTree<int> &a, int i, int k, int k_max) {
    /* cas base k - i > k_max */

    if (k - i + 1 > k_max) {
        a = BinTree<int>(i);
        cout << a.value() << "."  << ranking[a.value() - 1];
        return;
    }

    BinTree<int> left = BinTree<int>();
    BinTree<int> right = BinTree<int>();

    cout << "(";
    construir_arbre_emparellaments(left, i, k * 2, k_max);
    cout << " ";
    construir_arbre_emparellaments(right, k - i + 1, k * 2, k_max);
    cout << ")";

    a = BinTree<int>(i, left, right);
}

/* ------------------Arbre resultat------------------------*/
void Torneig::llegir_arbre_resultat(BinTree<string> &a) {
    /* llegim resultat */
    string r;
    cin >> r;

    /* cas base, estem en una fulla? */
    if (r == "0") {
        a = BinTree<string>("0");
        return;
    }

    /* si no llegim també el subarbre dret i esquerra */
    BinTree<string> left = BinTree<string>();
    BinTree<string> right = BinTree<string>();

    llegir_arbre_resultat(left);
    llegir_arbre_resultat(right);

    /* i ara els juntem */
    a = BinTree<string>(r, left, right);
}
/* ------------------Altres------------------------*/
int Torneig::llegir_partit(int j1, int j2, string resultat) {

    /* per consultar els resultats tractarem la string resultat
    com un vector de caràcters, fent la conversió a enter mitjançant
    la resta int(caràcter - '0') */
    
    /* cas: juguen tots els sets */
    if (resultat.length() == 11) {

        /* mirem qui ha guanyat: */
        /* 1: guanya j1, -1:guanya j2 */
        int guanyador = 1; 
        if (resultat[8] < resultat[10]) {
            guanyador = -1;
        }

        /* afegim les estadístiques del jugador 1 */
        nova_classificacio.afegir_partit(ranking[j1 - 1],
            int(resultat[0] - '0') + int(resultat[4] - '0') + int(resultat[8] - '0'),
            int(resultat[2] - '0') + int(resultat[6] - '0') + int(resultat[10] - '0'),
            1 + int(guanyador ==  1),
            1 + int(guanyador == -1),
            guanyador);

        /* afegim les estacístiques del jugdor 2 */
        nova_classificacio.afegir_partit(
            ranking[j2 - 1],
            int(resultat[2] - '0') + int(resultat[6] - '0') + int(resultat[10] - '0'),
            int(resultat[0] - '0') + int(resultat[4] - '0') + int(resultat[8] - '0'),
            1 + int(guanyador == -1),
            1 + int(guanyador ==  1),
            -guanyador);

        /* retornem la posició del jugador guanyador */
        if (guanyador == 1) return j1;
        return j2;
    }

    /* cas: juguen només dos sets */
    if (resultat.length() == 7) {

        /* mirem qui ha guanyat */
        /* 1: guanya j1, -1: guanya j2 */
        int guanyador = 1;
        if (resultat[0] < resultat[2]) {
            guanyador = -1;
        }

        /* afegim les estadístiques del jugador 1 */
        nova_classificacio.afegir_partit(
            ranking[j1 - 1],
            int(resultat[0] - '0') + int(resultat[4] - '0'),
            int(resultat[2] - '0') + int(resultat[6] - '0'),
            2*int(guanyador ==  1),
            2*int(guanyador == -1),
            guanyador);

        /* afegim les estacístiques del jugdor 2 */
        nova_classificacio.afegir_partit(
            ranking[j2 - 1],
            int(resultat[2] - '0') + int(resultat[6] - '0'),
            int(resultat[0] - '0') + int(resultat[4] - '0'),
            2*int(guanyador == -1),
            2*int(guanyador ==  1),
            -guanyador);

        /* retornem la posició del jugador guanyador */
        if (guanyador == 1) return j1;
        return j2;
    }

    /* cas: partit abortat */
    else {
        //* mirem qui ha guanyat */
        /* 1: guanya j1, -1: guanya j2 */
        int guanyador = 1;
        if (resultat[0] < resultat[2]) {
            guanyador = -1;
        }

        /* afegim les estadístiques del jugador 1 */
        nova_classificacio.afegir_partit(
            ranking[j1 - 1], 0, 0, 0, 0, guanyador);

        /* afegim les estacístiques del jugdor 2 */
        nova_classificacio.afegir_partit(
            ranking[j2 - 1], 0, 0, 0, 0, -guanyador);

        /* retornem la posició del jugador guanyador */
        if (guanyador == 1) return j1;
        return j2;
    }
}
/* ------------------Sortida del torneig-------------------*/
void Torneig::escriure_arbres(const BinTree<int> &a, const BinTree<string> &b) {
    /* cas base: fulla de l'arbre de resultats */
    if (b.value() == "0") return;
    
    /* escribim en el format corresponent */
    cout << "(";
    cout << a.left().value() << "." << ranking[a.left().value() - 1] 
        << " vs "
        << a.right().value() << "." << ranking[a.right().value() - 1]
        << " "
        << b.value();


    /* pas inductiu: fer el mateix per als subarbres */
    escriure_arbres(a.left(), b.left());
    escriure_arbres(a.right(), b.right());
    
    cout << ")";
}
void Torneig::escriure_ranking() {
    /* recorrem simultaniamen el ranking i el ranking_punts, 
    per associar cada jugador amb els seus punts corresponents */
    for (int i = 0; i < ranking_punts.size(); ++i) {
        if (ranking_punts[i] != 0) {
            cout << i + 1 << "." << ranking[i] << " " 
            << ranking_punts[i] << endl;
        }
    }
}

/* ------------------Consulta------------------------ */
Classificacio Torneig::consultar_darrera_classificacio() const {
    return this->darrera_classificacio;
}
string Torneig::consultar_nom_categoria() const {
    return this->categoria.nom;
}
