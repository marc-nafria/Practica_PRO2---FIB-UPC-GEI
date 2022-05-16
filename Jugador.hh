/** @file Jugador.hh
 *  @brief Especificació de la classe Jugador.
 */

#ifndef _JUGADOR_HH_
#define _JUGADOR_HH_

#include "Resultat.hh"

#ifndef NO_DIAGRAM  
#include <iostream>
#include <string>
#endif

using namespace std;

/** @class Jugador.
 *  @brief Representa a un jugador.
 * 
 * Emmagatzema el seu nom, 
 * la seva posició en el ranking, els seus punts 
 * i les estadístiques d'aquest. Conté funcions 
 * de consulta necessaries, i també dues per actualitzar-lo en base a un 
 * resultat que hagi obtingut en un torneig.
 */
class Jugador {
	
	public:

		Jugador() {};

		/** @brief Inicialitza un Jugador amb nom i posició en el ranking,
		 * inicialitzant les estadístiques a zero.
		 * \pre Un string no nul (nom del jugador)
		 * \post Un jugador amb nom i ranking,
		 * i les estadístiques inicialitzades a zero.
		 */
		Jugador(string nom, int ranking);
		
		/** @brief Inicialitza un Jugador igual a un altre.
		 * \pre Un jugador.
		 * \post Es copia el jugador.
		 */
		Jugador(const Jugador &j);

		/** @brief Actualitza els punts i les estadístiques del jugador 
		 * respecte el resultat obtigut en un torneig.
		 * \pre Un resultat.
		 * \post S'actualitzen les estadistiques de, jugador en base a les del resultat.
		 */
		void afegir_resultat(const Resultat &r);

		/** @brief Es retiren punts al jugador en funció a un resultat 
		 * d'un torneig.
		 * \pre Un resultat.
		 * \post Es retiren els punts obtinguts en el resultat.
		 */
		void retirar_resultat(const Resultat &r);
        
        /** @brief Modifica la posició del ranking del jugador.
         * \pre Un enter >= 1
         * \post S'actualitza this->ranking
         */
        void actualitzar_ranking(int r);

		/** @brief Escriu les principals estadístiques del jugador a la sortida.
		 * \pre Cert.
		 * \post Les estadístiques a la sortida.
		 */
		void escriure_estadistiques() const;
        
		/** @brief Retorna els punts actuals del jugador.
		 * \pre Cert.
		 * \post Els punts del jugadors.
		 */
		int consultar_punts() const;

		/** @brief Retorna la posició al ranking
		 * \pre: Cert.
		 * \post: La posicició al ranking
		 */
		int consultar_ranking() const;

	private:
		
		int punts;
		int ranking;

		int jocs_favor, jocs_contra;
		int sets_favor, sets_contra;
		int partits_favor, partits_contra;
		int tornejos_disputats;

		string nom;

};

#endif
