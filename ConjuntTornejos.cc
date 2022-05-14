#include "ConjuntTornejos.hh"
#include "Torneig.hh"
#include "Classificacio.hh"

#include <iostream>
#include <map>

using namespace std;

ConjuntTornejos::ConjuntTornejos() {};

bool ConjuntTornejos::afegir_torneig(string nom_torneig,
                                     Categoria categoria_torneig)
{
    /*
    Torneig t = Torneig(nom_torneig, categoria_torneig);

      if (tornejos.find(nom_torneig) != tornejos.end()) {
          return false;
      }

    tornejos.insert(tornejos.end(), make_pair(nom_torneig, t));

    return true;
    */
    return (tornejos.insert(make_pair(nom_torneig, Torneig(nom_torneig,
                                      categoria_torneig))).second);
}

bool ConjuntTornejos::borrar_torneig(string nom_torneig,
                                     Classificacio &darrera_classificacio)
{
    map<string, Torneig>::const_iterator it = tornejos.find(nom_torneig);

    if (it != tornejos.end()) {
        darrera_classificacio.copiar_classificacio((*it).second.consultar_darrera_classificacio());
        tornejos.erase(it);
        return true;
    }

    return false;
}

void ConjuntTornejos::iniciar_torneig(string nom_torneig,
                                      const vector<pair<string, int> > &ranking)
{
    map<string, Torneig>::iterator it = tornejos.find(nom_torneig);
    (*it).second.iniciar_torneig(ranking);
}

Classificacio ConjuntTornejos::finalitzar_torneig(string nom_torneig, Classificacio &darrera_classificacio)
{
    map<string, Torneig>::iterator it =
        tornejos.find(nom_torneig);

    darrera_classificacio.copiar_classificacio((*it).second.consultar_darrera_classificacio());
    return (*it).second.finalitzar_torneig();
}

void ConjuntTornejos::escriure_tornejos()
{

    cout << tornejos.size() << endl;

    for (map<string, Torneig>::const_iterator it = tornejos.begin();
            it != tornejos.end(); ++it) {

        cout << (*it).first << " " << (*it).second.consultar_nom_categoria() << endl;
    }

}

void ConjuntTornejos::borrar_jugador(string nom_jugador) {
    map<string, Torneig>::iterator it;

    for (it = tornejos.begin(); it != tornejos.end(); ++it) {
        (*it).second.borrar_jugador(nom_jugador);
    }
}