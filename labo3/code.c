#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "code.h"

void generer_code(char code[], int longueur)
{
    int utilises[10] = {0};
    int i;

    /* Le germe est initialise une seule fois par le programme. */
    static int graine_initialisee = 0;
    if (!graine_initialisee) {
        srand((unsigned int) time(NULL));
        graine_initialisee = 1;
    }

    for (i = 0; i < longueur; ++i) {
        int chiffre;
        do {
            chiffre = rand() % 10;
        } while (utilises[chiffre]);

        utilises[chiffre] = 1;
        code[i] = (char)('0' + chiffre);
    }
    code[longueur] = '\0';
}

int valider_code(const char proposition[], int longueur)
{
    int vus[10] = {0};
    int i;

    if (proposition == NULL || longueur < CODE_MIN || longueur > CODE_MAX)
        return 0;

    for (i = 0; i < longueur; ++i) {
        unsigned char caractere = (unsigned char) proposition[i];
        if (caractere < '0' || caractere > '9')
            return 0;

        if (vus[caractere - '0'])
            return 0;

        vus[caractere - '0'] = 1;
    }

    return proposition[longueur] == '\0';
}

void comparer_codes(const char secret[], const char proposition[],
                    int longueur, int *bien_places, int *mal_places)
{
    int secret_vus[10] = {0};
    int proposition_vus[10] = {0};
    int i;

    *bien_places = 0;
    *mal_places = 0;

    for (i = 0; i < longueur; ++i) {
        if (secret[i] == proposition[i]) {
            ++(*bien_places);
        } else {
            secret_vus[secret[i] - '0'] = 1;
            proposition_vus[proposition[i] - '0'] = 1;
        }
    }

    for (i = 0; i < 10; ++i) {
        if (secret_vus[i] && proposition_vus[i])
            ++(*mal_places);
    }
}
