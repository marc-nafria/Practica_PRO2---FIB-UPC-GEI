/** @file Resultat.hh
 * @brief Especificació de la estructura Resultat.
 */

#ifndef _RESULTAT_HH_
#define _RESULTAT_HH_

/** @struct Resultat: Conté un resum de les estadístiques d'un Jugador en un torneig.
 */
struct Resultat {
	int punts = 0;
	int jocs_favor = 0, jocs_contra = 0;
	int sets_favor = 0, sets_contra = 0;
	int partits_favor = 0, partits_contra = 0;
};

#endif