#include "header.h"

void initializare_bord(int** sudoku) {
    for(int i = 0; i < DIMENSIUNE; i++) 
        for(int j = 0; j < DIMENSIUNE; j++)
            *(*(sudoku + i) + j) &= 0;
}

bool verificare_linie(int **sudoku, int linie, int valoare) {
    for (int coloana = 0; coloana < DIMENSIUNE; coloana++) {
        if (*(*(sudoku + linie) + coloana) == valoare) {
            return false;
        }
    }
    return true;
}

bool verificare_coloana(int **sudoku, int coloana, int valoare) {
    for (int linie = 0; linie < DIMENSIUNE; linie++) {
        if (*(*(sudoku + linie) + coloana) == valoare) {
            return false;
        }
    }
    return true;
}

bool verificare_bloc(int **sudoku, int linie_inceput, int coloana_inceput, int valoare) {
    for (int linie = 0; linie < 3; linie++) {
        for (int coloana = 0; coloana < 3; coloana++) {
            if (*(*(sudoku + linie_inceput + linie) +
                + coloana_inceput + coloana) == valoare) {
                return false;
            }
        }
    }
    return true;
}

bool verificare_validare(int **sudoku, int linie, int coloana, int valoare) {
    return verificare_linie(sudoku, linie, valoare) &&
           verificare_coloana(sudoku, coloana, valoare) &&
           verificare_bloc(sudoku, linie - linie % 3, coloana - coloana % 3, valoare);
}

void afisare_sudoku(int **sudoku) {
    printf("-------------------\n");
    for (int linie = 0; linie < DIMENSIUNE; linie++) {
        for (int coloana = 0; coloana < DIMENSIUNE; coloana++) {
            if(coloana == 0)
                printf("|");
            if(coloana != 8 && coloana != 2 && coloana != 5) {
                if(*(*(sudoku + linie) + coloana) != 0)
                    printf("%d ", *(*(sudoku + linie) + coloana));
                else
                    printf("* ");
            }   else {
                    if(*(*(sudoku + linie) + coloana) != 0)
                        printf("%d", *(*(sudoku + linie) + coloana));
                    else
                        printf("*");
                }
            if(coloana == 2 || coloana == 5 || coloana == 8)
                printf("|");
        }
        if(linie == 2 || linie == 5 || linie == 8)
            printf("\n-------------------");
        printf("\n");
    }
}

bool rezolva_sudoku(int **sudoku) {
    int linie = 0, coloana = 0, valoare = 0, celule_goale = 0;

    for (linie = 0; linie < DIMENSIUNE; linie++) {
        for (coloana = 0; coloana < DIMENSIUNE; coloana++) {
            if (*(*(sudoku + linie) + coloana) == 0) {
                celule_goale++; 

                int permutare[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
                amesteca_permutare(permutare, DIMENSIUNE);

                for (int i = 0; i < DIMENSIUNE; i++) {
                    valoare = *(permutare + i);
                    if (verificare_validare(sudoku, linie, coloana, valoare)) {
                        *(*(sudoku + linie) + coloana) = valoare;

                        if (rezolva_sudoku(sudoku)) {
                            return true;
                        }

                        *(*(sudoku + linie) + coloana) &= 0;
                    }
                }
                return false;
            }
        }
    }

    if (celule_goale == 0) {
        return true; 
    }
    return false; 
}
