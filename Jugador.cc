/** @file Jugador.cc
 * @brief Implementació de la classe Jugador.
 */

#include "Jugador.hh"

#include <iostream>
#include <string>

using namespace std;

Jugador::Jugador(string nom, int ranking)
{
    this->nom = nom;

    this->punts = 0;
    this->ranking = ranking;

    this->jocs_favor = 0;
    this->jocs_contra = 0;

    this->sets_favor = 0;
    this->sets_contra = 0;

    this->partits_favor = 0;
    this->partits_contra = 0;

    this->tornejos_disputats = 0;

}

Jugador::Jugador(const Jugador &j)
{
    this->nom = j.nom;

    this->punts = j.punts;
    this->ranking = j.ranking;

    this->jocs_favor = j.jocs_favor;
    this->jocs_contra = j.jocs_contra;

    this->sets_favor = j.sets_favor;
    this->sets_contra = j.sets_contra;

    this->partits_favor = j.partits_favor;
    this->partits_contra = j.partits_contra;

    this->tornejos_disputats = 0;

}

void Jugador::afegir_resultat(const Resultat &r)
{
    this->punts += r.punts;

    this->jocs_favor += r.jocs_favor;
    this->jocs_contra += r.jocs_contra;

    this->sets_favor += r.sets_favor;
    this->sets_contra += r.sets_contra;

    this->partits_favor += r.partits_favor;
    this->partits_contra += r.partits_contra;

    this->tornejos_disputats++;
}

void Jugador::retirar_resultat(const Resultat &r)
{
    this->punts -= r.punts;
}

void Jugador::actualitzar_ranking(int r)
{
    this->ranking = r;
}
void Jugador::escriure_estadistiques() const {
    cout << nom
         << " Rk:" << this->ranking
         << " Ps:" << this->punts
         << " Ts:" << this->tornejos_disputats
         << " WM:" << this->partits_favor
         << " LM:" << this->partits_contra
         << " WS:" << this->sets_favor
         << " LS:" << this->sets_contra
         << " WG:" << this->jocs_favor
         << " LG:" << this->jocs_contra
         << endl;
}

int Jugador::consultar_punts() const
{
    return this->punts;
}
