#include "header.h"

char *aloca_string() {
    char *string = (char*)malloc(sizeof(char) * 10);
    if(string == NULL) {
        printf("\nNu s-a putut aloca memorie\n");
        return NULL;
    }
    return string;
}

int** bord() {
    int **sudoku = (int**)malloc(sizeof(int*) * 9);
    if(sudoku ==  NULL) {
        printf("Nu s-a putut aloca matricea");
        return NULL;
    }
    for(int i = 0; i < DIMENSIUNE; i++) {
        *(sudoku + i) = (int *)malloc(sizeof(int) * 9);
        if(*(sudoku + i) == NULL) {
            printf("Nu s-a putut aloca matricea");
            return NULL;
        }
    }
    return sudoku;
}

void elibereaza_bord(int **sudoku) {
    for(int i = 0; i < DIMENSIUNE; i++) {
        free(*(sudoku + i));
    }
    free(sudoku);
}

void amesteca_permutare(int *permutare, int n) {
    for (int i = DIMENSIUNE - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        permutare[i] ^= permutare[j];
        permutare[j] ^= permutare[i];
        permutare[i] ^= permutare[j];
    }
}

void umple_matricea(int **sudoku) {
    int linie, coloana;
    int numar_elemente = (rand() % 6) + 50;
    int celule_umplute = 0;

    while (celule_umplute < numar_elemente) {
        linie = rand() % DIMENSIUNE;
        coloana = rand() % DIMENSIUNE;

        if (*(*(sudoku + linie) + coloana) != 0) {
            *(*(sudoku + linie) + coloana) &= 0;
            celule_umplute++;
        }
    }
}

void start_joc() {
    char *string1 = aloca_string(), *string2 = aloca_string(),
    *string3 = aloca_string(), *comanda = aloca_string();
    TCoada *coada = NULL; 
    coada = InitQ();
    int **sudoku = bord(), ok = 0, ok2 = 0, ok3 = 0, scor = 10000;
    srand(time(NULL));
    time_t start_time = time(NULL);
    double seconds = 0;

    printf("\nPentru a incepe jocul introduceti comanda start\n");

    while(ok == 0) {
        
        ok2 = 0;
        for(int i = 0; i < 9; i++)
            for(int j = 0; j < 9; j++)
                if(*(*(sudoku + i) + j) == 0)
                    ok2 = 1;
        if(ok2 == 0) {
        time_t end_time = time(NULL);
        seconds = difftime(end_time, start_time);
        scor = scor - (int)seconds * 20; 
        if(ok3 == 0)
            printf("\n!!!FELICITARI AI CASTIGAT!!!\n");
        else 
            printf("\nYou are done. Fired. Do not show your face at the laundry again.\n");
        printf("\nScorul tau este de %d\n", scor);
        free(string1);
        free(string2);
        free(string3);
        free(comanda);
        DistrQ(&coada);
        elibereaza_bord(sudoku);
        return;
        }

    if(scanf("%s", comanda) != 1)
        ok = 1;

    if(strcmp(comanda, "start") != 0 && strcmp(comanda, "refresh") != 0 && strcmp(comanda, "exit") != 0
       && strcmp(comanda, "ajutor") != 0 && strcmp(comanda, "introduce") != 0 && strcmp(comanda, "undo") != 0
       && strcmp(comanda, "triseaza") != 0) {
        printf("\nComanda invalida!\n");
        continue;
    }

    if(strcmp(comanda, "triseaza") == 0) {
        initializare_bord(sudoku);
        rezolva_sudoku(sudoku);
        ok3 = 1;
    }

    if(strcmp(comanda, "ajutor") == 0) {
            printf("\nRegulile de baza sunt urmatoarele:\n");
            printf("undo - sterge ultima decizie\n");
            printf("exit - iese din joc\n");
            printf("refresh - genereaza un nou joc\n");
            printf("ajutor - afiseaza regulile jocului\n");
            printf("introduce - scrie la linia si coloana respectiva numarul dorit\n");
    }

    if(strcmp(comanda, "start") == 0) {
        if(rezolva_sudoku(sudoku)) {
            umple_matricea(sudoku);
            printf("\nSalutare! Bun venit la jocul Sudoku!\n");
            printf("Regulile de baza sunt urmatoarele:\n");
            printf("\nundo - sterge ultima decizie\n");
            printf("exit - iese din joc\n");
            printf("refresh - genereaza un nou joc\n");
            printf("ajutor - afiseaza regulile jocului\n");
            printf("introduce - scrie la linia si coloana respectiva numarul dorit\n");
            afisare_sudoku(sudoku);
    } else {
        printf("\nNu s-a putut rezolva sudoku\n");
        ok = 1;
    }
    }

    if(strcmp(comanda, "refresh") == 0) {
        initializare_bord(sudoku);
        if(rezolva_sudoku(sudoku)) {
            printf("\nNoul bord este:\n");
            umple_matricea(sudoku);
            afisare_sudoku(sudoku);
    }
    }

    if(strcmp(comanda, "exit") == 0) {
        printf("\nJocul s-a terminat!\n");
        ok = 1;
    }

    if(strcmp(comanda, "introduce") == 0) {
        int linie, coloana, numar;
        printf("\nIntroduceti linia, coloana si numarul dorit:\n");
        printf("Daca doriti sa anulati comanda introduceti -1 si terminati citirea.\n");

        if(scanf("%d %d %d", &linie, &coloana, &numar) != 3) {
            if(scanf("%s %s %s", string1, string2, string3) == 3) 
            printf("\nComanda invalida\n");
            scor = scor - 100;
            continue;
        }

        if(linie == -1) {
            printf("\nAti anulat comanda\n");
            continue;
        }

        if(linie < 1 || linie > 9 || coloana < 1 || coloana > 9 || numar < 1 || numar > 9) {
            printf("\nIntrodu numere corecte\n");
            scor = scor - 100;
            continue;
        }

        if(*(*(sudoku + linie - 1) + coloana - 1) != 0) {
            printf("\nNu poti modifica aceasta celula\n");
            scor = scor - 10;
            continue;
        }

        if(verificare_validare(sudoku, linie - 1, coloana - 1, numar) == 0) {
            printf("\nMatricea Sudoku nu respecta regulile jocului. Introduceti o valoare valida.\n");
            scor = scor - 50;
            *(*(sudoku + linie - 1) + coloana - 1) = 0;
            continue;
        }

        IntrQ(coada, linie - 1, coloana - 1);
        *(*(sudoku + linie - 1) + coloana - 1) = numar;
        afisare_sudoku(sudoku);
    }

    if(strcmp(comanda, "undo") == 0) {
        if(coada->inc == NULL) {
            printf("\nNu mai exista mutari anterioare\n");
            continue;
        }
        int linie, coloana;
        ExtrQ(coada, &linie, &coloana);
        *(*(sudoku + linie) + coloana) = 0;
        afisare_sudoku(sudoku);
    }
    }

    free(string1);
    free(string2);
    free(string3);
    free(comanda);
    DistrQ(&coada);
    elibereaza_bord(sudoku);
}