#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#define DIMENSIUNE 9

#ifndef sudoku

typedef struct celula {
  int linie;
  int coloana;
  struct celula* urm;
}TCelula, *TLista;

typedef struct coada {
  TLista inc, sf;
}TCoada;

TCoada* InitQ ();
void IntrQ(TCoada *c, int linie, int coloana);
void ExtrQ(TCoada *c, int *linie, int *coloana);
void DistrQ(TCoada **c);

int **bord();
char *aloca_string();
void elibereaza_bord(int **sudoku);

bool verificare_linie(int **sudoku, int linie, int valoare);
bool verificare_coloana(int **sudoku, int coloana, int valoare);
bool verificare_bloc(int **sudoku, int linie_inceput, int coloana_inceput, int valoare);
bool verificare_validare(int **sudoku, int linie, int coloana, int valoare);

void amesteca_permutare(int *permutare, int n);
void initializare_bord(int** sudoku);
bool rezolva_sudoku(int **sudoku);
void afisare_sudoku(int **sudoku);
void umple_matricea(int **matrice);
void start_joc();

#endif