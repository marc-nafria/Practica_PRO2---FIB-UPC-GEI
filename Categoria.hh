/** @file Categoria.hh
 * @brief Especificació de l'estructura categoria.
 */

#ifndef _CATEGORIA_HH_
#define _CATEGORIA_HH_

#ifndef NO_DIAGRAM  
#include <vector>
#include <string>
#endif

using namespace std;

/** @struct Categoria.
 * @brief Representa una categoria del circuit.
 * 
 * Està formada principalment 
 * per un string (nom) i un conjunt de K enters (nombre de nivells del circuit) tal 
 * que l'enter punts_per_nivell[i] especifica el nombre de punts que es guanyen
 * per a un cert nivell i.
 */
struct Categoria {
	string nom;
	vector<int> punts_per_nivell;
};
#endif