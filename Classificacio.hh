/** @file Classificació.hh
 * @brief Especificació de la classe Classificació i de l'estructura
 * Resultat
 */

#ifndef _CLASSIFICACIO_HH_
#define _CLASSIFICACIO_HH_

#ifndef NO_DIAGRAM  
#include <vector>
#include <map>
#include <string>
#endif

using namespace std;

/** @struct Resultat: Conté un resum de les estadístiques d'un Jugador en un torneig.
 */
struct Resultat {
  int punts = 0;
  int jocs_favor = 0, jocs_contra = 0;
  int sets_favor = 0, sets_contra = 0;
  int partits_favor = 0, partits_contra = 0;
};

/** @class Classificacio.
 * @brief Representa el resum d'un torneig, es a dir, 
 * es un conjunt dels resultats de tots els jugadors.
 */
class Classificacio {

  public:

  	/** @brief Afegeix un nou partir a la classificacio
      * d'un jugador, modificant el seu resultat en el diccionari
      * jugadors.
  	* \pre Un string, 4 enters d'estadistiques, més un enter que determina
      * si ha guanyat(1) o ha perdut(-1).
  	* \post S'afegeix aquest partit al resultat del jugador.
  	*/
  	void afegir_partit(string nom_jugador, int jocs_favor, int jocs_contra,
      int sets_favor, int sets_contra,
      int resultat_partit);
      
    /** @brief Determina els punts que guanya el jugador en el
     * torneig, afegint-los al seu resultat en el diccionari jugadors.
     * També retorna si s'han afegit amb exit, ja que potser hem afegit menys
     * punts dels que tocavem perquè ens trobem en un nivell inferior
     * al que ha quedat el jugador.
     * \pre Un string (nom del jugador) i els respectius punts.
     * \post Es guarden els punts al resultat del jugador.
     */
    void establir_punts(string nom_jugador, int punts);
    
    /** @brief Borra el jugador de la classificacio.
     * \pre Un string (nom del jugador).
     * \post S'esborra el jugador.
     */
    void borrar_jugador(string nom_jugador);
    
    /** @brief Modifica el parametre implícit com una copia de
    * una altra classficacio.
    * \pre Una classificacio a copiar
    * \post this->jugadors = copia.jugadors
    */
    void copiar_classificacio(const Classificacio &copia);

    /**@brief Esborra tots els resultats de la classificacio.
     * \pre Cert.
     * \post S'esborra la classificacio.
     */
    void borrar_classificacio();
    
  	/** @brief Retorna una copia del diccionari 'jugadors', per a 
  	 * modificar els jugadors desde el programa principal.
  	 * \pre Cert.
  	 * \post Una copia de la classificacio.
  	 */
  	map<string, Resultat> consultar_classificacio() const;

  private:
		
	 map<string, Resultat> jugadors;

};

#endif
