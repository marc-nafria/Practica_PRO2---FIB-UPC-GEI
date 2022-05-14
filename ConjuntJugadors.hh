/** @file ConjuntJugadors.hh 
 * @brief Especificació de la classe ConjuntJugadors. 
 */

#ifndef _ConjuntTornejos_HH_
#define _ConjuntTornejos_HH_

#include "Jugador.hh"
#include "Classificacio.hh"

#ifndef NO_DIAGRAM  
#include <vector>
#include <algorithm>
#include <map>
#endif

using namespace std;

/** @class ConjuntJugadors.
 *  @brief Representa un conjunt de jugadors.
 * 
 * Consta principalment d'un diccionari on 
 * s'emmagatzemen els jugadors. També conté funcions per afegir-ne, esborrar-ne, 
 * modificar-ne en funció dé la classificacio d'n torneig, i algunes basiques de sortida.
 */
class ConjuntJugadors {

	public:
		
		/** @brief Iniciatilza un conjunt de jugadors buit.
		 * \pre Cert.
		 * \post Un conjunt de jugadors buit.
		 */
		ConjuntJugadors() {};

		/** @brief Afegeix un jugador al conjunt.
		 * \pre Un string no buit.
		 * \post True: s'ha afegit el jugador amb una puntuacio de zero.
		 * 		False: no s'ha afegit perque ja existia.
		 */
		bool afegir_jugador(string nom_jugador);

		/** @brief Borra un jugador en funció d'un identificador.
		 * \pre string (nom del jugador).
		 * \post True: s'ha trobat el jugador i s'ha esborrat.
		 * 		False: no existeix el jugador.
		 */
		bool borrar_jugador(string nom_jugador);

		/** @brief Afegeix els punts i estadistiques obtingudes en un torneig 
		 * per als jugadors que hi han participat.
		 * \pre Una classifició d'un torneig (c).
		 * \post S'afegeix els resultats de la classificació del torneig als 
		 * jugadors corresponents.
		 */
		void afegir_classificacio(Classificacio &c);

		/** @brief Retira els punts obtinguts en un torneig als jugadors corresponents.
		 * \pre Una classificació d'un torneig (c).
		 * \post Es retira els resultats d'aqeusta classificació al jugadors corresponents.
		 */
		void retirar_classificacio(Classificacio &c);
		
		/** @brief Retorna el ranking.
		 * \pre Cert.
		 * \post Retorna el ranking actual.
		 */
		vector<pair<string, int> > consultar_ranking() const;

		/** @brief Escriure Ranking: Escriu el ranking del circuit al canal de sortida.
		 * \pre Cert.
		 * \post El ranking escrit.
		 */
		void escriure_ranking() const;

		/** @brief Llista els jugadors al canal de sortida.
		 * \pre Cert.
		 * \post Els jugadors al canal de sortida, ordenats alfabèticament.
		 */
		void escriure_jugadors() const;

		/** @brief Escriu les estadistiques d'un jugador al canal de sortida.
		 * \pre Un string (nom del jugador).
		 * \post True : Escriu les estadistiques del jugador al canal de sortida.
		 * 		False: No existeix el jugador.
		 */
		bool escriure_jugador(string nom_jugador) const;

		/** @brief Actualitza el ranking i l'ordena
		 * \pre: True
		 * \post: Actualitza i ordena el ranking
		 */
    	void actualitzar_ranking();

    private:

    	/* Pre: cert */
    	/* Post: el vector ranking esta ordenat representant un ranking */
    	void ordenar_ranking();

        /* Pre: cert */
        /* Post: informa del ranking als jugador, es a dir 
        quina es la seva posició actual */
        void informar_ranking();

        map<string, Jugador> jugadors;
        vector<pair<string, int> > ranking;
};

#endif
