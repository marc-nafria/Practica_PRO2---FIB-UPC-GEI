/** @file ConjuntTornejos.hh
 * @brief Especificació de la classe ConjuntTornejos.
 */

#ifndef _CONJUNTTORNEJOS_HH_
#define _CONJUNTTORNEJOS_HH_

#include "Torneig.hh"


#ifndef NO_DIAGRAM  
#include "Categoria.hh"
#include "Classificacio.hh"

#include <map>
#endif

/** @class ConjuntTornejos
 * @brief Representa a un conjunt de tornejos d'un circuit.
 * 
 * Conté funcions bàsiques per a afegir, borrar, iniciar, finalitzar els 
 * tornejos que conté. Els emmagatzema en un diccionari, ja que no
 * es poden repertir noms de tornejos i serà més ràpid buscar-los.
 * L'identificador del diccionari es el nom del torneig.
 */
class ConjuntTornejos {

	public:

		/** @brief Contructora defecte: Iniciatilza un conjunt de tornejos buit.
		 * \pre Cert.
		 * \post Un conjunt de tornejos buit.
		 */
		ConjuntTornejos(); 

		/** @brief Afegir torneig: Afegeix un torneig al conjunt
		 * en funció d'un nom i una categoria.
		 * \pre Un string (nom torneig) i una categoria.
		 * \post True: S'ha afegit el torneig. False: no s'ha afegit
		 * perque ja existia.
		 */
		bool afegir_torneig(string nom_torneig, Categoria categoria_torneig);

		/** @brief Borrar Torneig: Borra un torneg del conjunt i retorna la 
		 * seva classificació en l'última edició, per a que es puguin retirar
		 * els punts des del programa principal.
		 * \pre Un string (nom del torneig).
		 * \post True: S'ha borrat el torneig i es retorna la seva classicifació.
		 * False: No s'ha trobat el torneig.
		 */
		bool borrar_torneig(string nom_torneig, Classificacio &darrera_classificacio);

		/** @brief Iniciar Torneig: Inicia un torneig del conjunt en funció
		 * del seu nom.
		 * \pre Un string (nom del torneig), i existeig un torneig amb aquest nom. També
		 * el ranking actual del circuit.
		 * \post S'inicia el torneig.
		 */
		void iniciar_torneig(string nom_torneig, const vector<pair<string, int> > &ranking);

		/** @brief Finalitzar torneig: Finalitza un torneig i retorna 
		 * la seva classificació.
		 * \pre Un string (nom torneig), existeix un torneig amb aquest nom.
		 * \post Es finalitza el torneig i es retorna la seva cassificació.
		 */
		Classificacio finalitzar_torneig(string nom_torneig, Classificacio &darrera_classificacio);
		
		/** @brief Escriure Tornejos: LLista els torneijos a la sortida.
		 * \pre Cert.
		 * \post Els tornejos a la sortida.
		 */
		void escriure_tornejos();
		
		void borrar_jugador(string nom_jugador);
	private:

		map<string, Torneig> tornejos;
};

#endif
