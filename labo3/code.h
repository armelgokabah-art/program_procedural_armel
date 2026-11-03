#ifndef CODE_H
#define CODE_H

#define CODE_MAX 6
#define CODE_MIN 4

/* Genere un code compose de chiffres distincts. */
void generer_code(char code[], int longueur);

/* Verifie qu'une proposition contient exactement longueur chiffres distincts. */
int valider_code(const char proposition[], int longueur);

/* Compare deux codes et met a jour les deux resultats via des pointeurs. */
void comparer_codes(const char secret[], const char proposition[],
                    int longueur, int *bien_places, int *mal_places);

#endif
