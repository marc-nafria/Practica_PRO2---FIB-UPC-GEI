
#include <string>/** @file CircuitIO.hh
 * @brief Conté funcions bàsiques d'entrada i sortida de les diferents
 * classes.
 */

#ifndef _CIRUCUITIO_HH_
#define _CIRUCUITIO_HH_

#include "ConjuntJugadors.hh"

#include "ConjuntTornejos.hh"

#ifndef NO_DIAGRAM  
#include "Torneig.hh"
#include "Jugador.hh"
#include "Categoria.hh"

#include <vector>
#endif

/** @brief Modifica un vector<Categoria> llegint-lo
 * de l'entrada.
 * \pre Un vector<Categoria> i dos enters C i K (nombre de categories) (nivells per categoria).
 * \post Mofica el vector categories.
 */
void llegir_conjunt_categories(vector<Categoria> &categories, int C, int K);

/** @brief Modifica un Conjunt de Tornejos llegint-lo
 * de l'entrada.
 * \pre Un Conjunt_Tornejos, un enter T (nombre tornejos) i un vector amb les
 * categories del circuit.
 * \post Afegeix al conjunt de tornejos els tornejos que es llegeixen de la entrada.
 */
void llegir_conjunt_tornejos(ConjuntTornejos &tornejos, int T, const vector<Categoria> &categories);

/** @brief Modifica un Conjunt de Jugadors llegint-lo
 * de l'entrada.
 * \pre Un Conjunt de Jugadors i un enter (nombre de jugadors).
 * \post S'afegeixen el jugadors llegits de l'entrada al conjunt.
 */
void llegir_conjunt_jugadors(ConjuntJugadors &jugadors, int T);

/** @brief Llista un vector de categories a la 
 * sortida.
 * \pre Un vector<Categoria>.
 * \post Es llista a la sortida.
 */
void llistar_conjunt_categories(const vector<Categoria> &categories, int C, int K);

#endif
