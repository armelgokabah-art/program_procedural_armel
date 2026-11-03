#include <stdio.h>
#include <stdlib.h>
#include "jeu.h"

static void afficher_menu(void)
{
    printf("\n========== SOMMAIRE ==========\n");
    printf("1) Partie classique\n");
    printf("2) Partie personnalisee\n");
    printf("3) Mode deux joueurs\n");
    printf("4) Quitter\n");
    printf("Votre selection : ");
}

int main(void)
{
    int choix = 0;

    while (choix != 4) {
        afficher_menu();

        if (scanf("%d", &choix) != 1) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {
                /* Vider la saisie incorrecte. */
            }
            choix = 0;
            printf("Entree invalide. Saisissez un nombre entre 1 et 4.\n");
            continue;
        }

        switch (choix) {
            case 1:
                jouer_classique();
                break;
            case 2:
                jouer_personnalise();
                break;
            case 3:
                jouer_deux_joueurs();
                break;
            case 4:
                printf("Au revoir !\n");
                break;
            default:
                printf("Choix invalide. Saisissez un nombre entre 1 et 4.\n");
        }
    }

    return EXIT_SUCCESS;
}
