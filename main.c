#include <stdio.h>
#include "demineur.h"

int main(void)
{
    int choix;

    srand((unsigned int)time(NULL));

    do
    {
        printf("\n============================\n");
        printf("          DEMINEUR\n");
        printf("============================\n");
        printf("1. Jouer contre l'ordinateur\n");
        printf("2. Jouer contre un humain\n");
        printf("0. Quitter\n");

        printf("Votre choix : ");

        if (scanf("%d", &choix) != 1)
        {
            while (getchar() != '\n')
            {
                /* Vide l'entree invalide. */
            }

            choix = -1;
            printf("Saisie invalide.\n");
            continue;
        }

        switch (choix)
        {
            case 1:
                jouerContreOrdinateur();
                break;

            case 2:
                jouerContreHumain();
                break;

            case 0:
                printf("\nAu revoir !\n");
                break;

            default:
                printf("Choix invalide. Veuillez choisir 0, 1 ou 2.\n");
        }

    } while (choix != 0);

    return 0;
}
