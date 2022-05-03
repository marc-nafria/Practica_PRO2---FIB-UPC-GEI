# Pràctica Pro2

#### Índex:

```textile
1. Descripció de la pràctica

   1.1 Jugador

   1.2 Torneig i categories

2. Diseny modular

3. Funcions importants
```

---

#### 1. Descripció de la pràctica

La pràctica tracta de la gestió d'unn circuit de tennis. En un **circuit**, existeixen **jugadors**, que participen en **tornejos**. Per a emmagatzemmar l'estat del circuit, aquest consta d'un **ranquing**, on trobem els punts que cada jugador a guanyat a base de participar en tornejos.

###### 1.1 Jugadors

Un **jugador**, a part dels punts, també te certes estadístiques que el torneig ha de tenir en compte:

+ Partits jugats

+ Sets a favor i en contra

+ Jocs a favor i en contra

+ Partits a favor i en contra

Els jugadors es poden donar d'alta i de baixa en un circuit, però mai n'hi pot haver dos amb el mateix nom.

###### 1.2 Tornejos

Una **categoria** és una caracteristica del torneig, i és la que determina quants punts es guanyen en funció de la posició obtinguda en un torneig.

Un **torneig** consta de dues fases:

+ Fase **d'incripció**: Els jugadors s'apunten al torneig i és determina un quadre d'enfrontamentsl en funció de les respectives posicions al ranquing.

+ Fase **final**: Es publiquen els resultats dels enfrontaments i es repartixen els punts obtinguts per cada jugador.

---

#### 2. Diseny modular

Per al diseny de la solució de la pràctica he decidit definir **classes** per a representar:

+ **Jugador**

+ **Torneig**

+ **Classificació**

+ **Conjunt de jugadors**: Per a gestionar els jugadors d'un circuit

+ **Conjunt de Tornejos**: per a gestionar els tornejos d'un circuit

També, es representa, mitjançant **estructures**:

+ **Categoria**: emmagatzema els punts que s'obtenen en funció de la posició en un torneig

+ **Resultat**: resum de la participació d'un jugador en un torneig

---

#### 3. Funcions importants

3.1 Torneig::construir_arbre(BinTree &a, int i, int k, int k_max)

```cpp
void Torneig::construir_arbre(BinTree<int> &a, int i, int k, int k_max)
{
    // cas base k - i > k_max

    if (k - i + 1 > k_max) {
        a = BinTree<int>(i);
        cout << a.value() << "."  << ranking[a.value() - 1];
        return;
    }

    BinTree<int> left = BinTree<int>();
    BinTree<int> right = BinTree<int>();

    cout << "(";
    construir_arbre(left, i, k * 2, k_max);
    cout << " ";
    construir_arbre(right, k - i + 1, k * 2, k_max);
    cout << ")";

    a = BinTree<int>(i, left, right);
}
```


