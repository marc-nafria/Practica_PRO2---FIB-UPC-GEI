/** @file Torneig.hh
 * @brief Especificació de la classe Torneig.aaaa
 */

#ifndef _TORNEIG_HH_
#define _TORNEIG_HH_

#include "Categoria.hh"
#include "Classificacio.hh"

#ifndef NO_DIAGRAM 
#include "BinTree.hh"

#include <iostream>
#include <string>
#endif

/** @class Torneig
 * @brief Representa un torneig del circuit.
 * 
 * Aquest consta de dues funcions
 * principals, la d'inici i la de final. La de final resumeix la tasca del
 * torneig, retornar un Classificacio que resumeixi que ha passat.
 * A més, un torneig sempre guarda la classificació de la última edició, perque 
 * farà falta treure punts a certs jugadors, ja sigui quan es borrir el torneig
 * o s'en faci una nova edició.
 * També es contempla que, en esborrar un jugador del circuit, s'ha de borrar
 * aquest de la darrera classificació en cas de que hi sigui, ja que hi poden 
 * haver futurs jugadors amb el mateix nom.
 */
class Torneig {

	public:

		Torneig() {};
		
		/** @brief Construeix un Torneig en funció
		 * d'una categoria. La categoria s'emmagatzema per a saber
		 * quants punts corresponen a cada jugador en acabar el torneig.
		 * \pre Un string (nom del torneig) i una categoria.
		 * \post Es crea un torneig amb el nom i la categoria corresponents.
		 */
		Torneig(Categoria categoria_torneig);

		/** @brief Inicia el torneig, es a dir, llegeix les 
		 * inscripcions, es confecciona i imprimeix l'arbre d'emparellaments.
		 * \pre El ranking en el moment de començar el torneig.
		 * El torneig no està començat (cert), i a l'entrada es troba un 
		 * enter n, seguit de n strings (noms de jugadors) i n enters (posicions ranking).
		 * \post Es llegeixen les inscripcions i es confecciona i imprimeix el
		 * quadre d'emparellaments
		 */
		void iniciar_torneig(const vector<pair<string, int> > &ranking);

		/** @brief Es llegeixen els resultats del torneix 
		 * i es retorna una classificacio, que indica quants punts ha guanyat
		 * cada jugador i quines estadísitques ha sumat. 
		 * A més, el torneig guarda una copia de la classificació, que servirà
		 * per a la seguent edició o per a quan s'elimini el torneig.
		 * \pre El torneig s'ha iniciat. Tots els resultats es trobem a la entrada
		 * amb alguns a 0 marcant així les fulles.
		 * \post Es llegeixen els resultats del torneig i es retorna i guarda
		 * la classificació.
		 */
		Classificacio finalitzar_torneig();

		/** @brief Borra un jugador de la darrera classificació del torneig
		 * \pre Un string (nom del jugador a borrar).
		 * \post Es borra el jugador de la darrera classificació del torneig.
		 */
		void borrar_jugador(string nom_jugador);

		/** @brief Retorna la Classificacio de la
		 * útlima edició del torneig.
		 * \pre Cert.
		 * \post Una copia de la darrera classificacio.
		 */
		Classificacio consultar_darrera_classificacio() const;
		
		/** @brief Retorna un string amb el nom de la
		 * categoria.
		 * \pre Cert.
		 * \post Nom de la categoria.
		 */
		string consultar_nom_categoria() const;

	private:
        
		/** @brief Contrueix un primer arbre d'emparellaments, amb alguns valors auxiliars
		 *  que ja seran modificats en un futur. També imprimeix la sortida de 
		 *  "iniciar_torneig".
		 * \pre: Un arbre binari i tres enters
		 * \post: Construiex un primer arbre d'emparellaments, fent crides resucrsives
		 * a si mateixa.
		 */
        void construir_arbre_emparellaments(BinTree<int> &a, int i, int k, int k_max);

        /** @brief Modifica l'arbre d'emparellaments amb els guanaydors definitius de cada 
         * enfrontament, també reparteix els punts corresponents a cada jugador 
         * \pre Una abre binari d'enter representant l'arbre d'emparellaments, un 
         * altre arbre que representi els resultats de cada enfrontalment, i un enter per 
         * saber a quin nivell estem.
         * \post Es modifica l'arbre d'emparellaments i s'afegeixen els punts de cada jugador.
         */
        void modificar_arbre_emparellaments(BinTree<int> &a, const BinTree<string> &b, int nivell);

        /** @brief Llegeix els resultats de cada partit del torneig i els guarda a un arbre.
         * \pre Un arbre binari de strings.
         * \post S'actualitza l'arbre amb els resultats.
         */
		void llegir_arbre_resultat(BinTree<string> &a);

        /** @brieg Escriu els resultats de l'arbre final recorrent els dos simultaneament.
         * \pre Dos arbres binaris, un representant els enfrentaments i l'altre els resultats.
         * \post Escriu l'output de finalizar_torneo.
         */
        void escriure_arbres(const BinTree<int> &a, const BinTree<string> &b);
		
		/** @brief Afegeix el resultat del partit(resultat) i afegeix les estadístiques
		 * als jugadors(j1, j2).
		 * \pre Dos enters (posicions del jugadors al ranking local del torneig) i un 
		 * string que conté el resultat del torneig.
		 * \post S'afegeixen les estadístiques obtingudes en el torneig als jugados, i 
		 * es retorna la posició del ranking del guanyador.
		 */
		int llegir_partit(int j1, int j2, string resultat);

		/** @brief Escriu els punts de cada jugador en ordre del ranking al iniciar
		 * el torneig.
		 * \pre Cert.
		 * \post S'acaba de escriure el output de finalizar_torneo.
		 */
		void escriure_ranking();

		vector<string> ranking; /**< Conté els noms del jugadors del torneig, 
		en l'ordre del ranking en el moment que va iniciar el torneig */
		vector<int> ranking_punts; /**< Conté els punts obtinguts en el torneig
		per els jugadors en el mateix ordre que el ranking */

		BinTree<int> arbre_emparellaments; /**< Arbre binari d'enters on cada 
		arrel reprenta un enforntament del fills esquerre i dret de l'arbre */
		BinTree<string> arbre_resultat; /**< Arbre de strings, que conté el 
		resultat de cada enfrontament */

		Categoria categoria; /**< Categoria del torneig */
		Classificacio darrera_classificacio; /**< Darrera Classificació del torneig */
		Classificacio nova_classificacio; /**< Nova classificació del torneig */

};

#endif
