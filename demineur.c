#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "demineur.h"

/*
 * Initialise la grille avec uniquement des cases saines.
 * 0 = case saine, 1 = bombe.
 */
void initialiserGrille(int grille[TAILLE][TAILLE])
{
    int ligne, colonne;

    for (ligne = 0; ligne < TAILLE; ligne++)
    {
        for (colonne = 0; colonne < TAILLE; colonne++)
        {
            grille[ligne][colonne] = 0;
        }
    }
}

/* Initialise toutes les cases comme non découvertes. */
void initialiserDecouverte(int decouverte[TAILLE][TAILLE])
{
    int ligne, colonne;

    for (ligne = 0; ligne < TAILLE; ligne++)
    {
        for (colonne = 0; colonne < TAILLE; colonne++)
        {
            decouverte[ligne][colonne] = 0;
        }
    }
}

/* Affiche uniquement les cases que le joueur est autorisé à voir. */
void afficherGrille(int grille[TAILLE][TAILLE],
                    int decouverte[TAILLE][TAILLE])
{
    int ligne, colonne;

    printf("\n    1 2 3 4 5 6\n");

    for (ligne = 0; ligne < TAILLE; ligne++)
    {
        printf("%d   ", ligne + 1);

        for (colonne = 0; colonne < TAILLE; colonne++)
        {
            if (decouverte[ligne][colonne] == 1 && grille[ligne][colonne] == 0)
            {
                printf("- ");
            }
            else
            {
                printf("? ");
            }
        }

        printf("\n");
    }

    printf("\n");
}

/* Demande un nombre de bombes compris entre 1 et 18. */
int demanderNombreBombes(void)
{
    int nombreBombes;

    do
    {
        printf("Nombre de bombes (1-%d) : ", MAX_BOMBES);

        if (scanf("%d", &nombreBombes) != 1)
        {
            while (getchar() != '\n')
            {
                /* Vide l'entree invalide. */
            }

            nombreBombes = 0;
            printf("Saisie invalide.\n");
        }
        else if (nombreBombes < 1 || nombreBombes > MAX_BOMBES)
        {
            printf("Le nombre de bombes doit etre compris entre 1 et %d.\n",
                   MAX_BOMBES);
        }

    } while (nombreBombes < 1 || nombreBombes > MAX_BOMBES);

    return nombreBombes;
}

/* Demande une coordonnee comprise entre 1 et 6. */
int demanderCoordonnee(const char *message)
{
    int coordonnee;

    do
    {
        printf("%s", message);

        if (scanf("%d", &coordonnee) != 1)
        {
            while (getchar() != '\n')
            {
                /* Vide l'entree invalide. */
            }

            coordonnee = 0;
            printf("Saisie invalide.\n");
        }
        else if (coordonnee < 1 || coordonnee > TAILLE)
        {
            printf("La coordonnee doit etre comprise entre 1 et %d.\n",
                   TAILLE);
        }

    } while (coordonnee < 1 || coordonnee > TAILLE);

    return coordonnee;
}

/* Place les bombes aleatoirement, sans doublon. */
void placerBombesAleatoirement(int grille[TAILLE][TAILLE], int nombreBombes)
{
    int bombesPlacees = 0;
    int ligne, colonne;

    while (bombesPlacees < nombreBombes)
    {
        ligne = rand() % TAILLE;
        colonne = rand() % TAILLE;

        if (grille[ligne][colonne] == 0)
        {
            grille[ligne][colonne] = 1;
            bombesPlacees++;
        }
    }
}

/* Permet au joueur B de placer les bombes, sans doublon. */
void placerBombesHumain(int grille[TAILLE][TAILLE], int nombreBombes)
{
    int bombesPlacees = 0;
    int ligne, colonne;

    printf("\n--- Placement des bombes par le joueur B ---\n");

    while (bombesPlacees < nombreBombes)
    {
        printf("\nBombe %d sur %d\n", bombesPlacees + 1, nombreBombes);

        ligne = demanderCoordonnee("Ligne (1-6) : ");
        colonne = demanderCoordonnee("Colonne (1-6) : ");

        ligne--;
        colonne--;

        if (grille[ligne][colonne] == 1)
        {
            printf("Cette case contient deja une bombe.\n");
        }
        else
        {
            grille[ligne][colonne] = 1;
            bombesPlacees++;
            printf("Bombe placee.\n");
        }
    }

    printf("\nToutes les bombes ont ete placees.\n");
}

/* Retourne 1 si la case a deja ete decouverte, sinon 0. */
int caseDejaDecouverte(int decouverte[TAILLE][TAILLE],
                       int ligne, int colonne)
{
    return decouverte[ligne][colonne] == 1;
}

/* Compte toutes les cases saines de la grille. */
int compterCasesSaines(int grille[TAILLE][TAILLE])
{
    int ligne, colonne;
    int total = 0;

    for (ligne = 0; ligne < TAILLE; ligne++)
    {
        for (colonne = 0; colonne < TAILLE; colonne++)
        {
            if (grille[ligne][colonne] == 0)
            {
                total++;
            }
        }
    }

    return total;
}

/* Compte uniquement les cases saines qui ont ete decouvertes. */
int compterCasesSainesDecouvertes(int grille[TAILLE][TAILLE],
                                  int decouverte[TAILLE][TAILLE])
{
    int ligne, colonne;
    int total = 0;

    for (ligne = 0; ligne < TAILLE; ligne++)
    {
        for (colonne = 0; colonne < TAILLE; colonne++)
        {
            if (grille[ligne][colonne] == 0 &&
                decouverte[ligne][colonne] == 1)
            {
                total++;
            }
        }
    }

    return total;
}

void afficherVictoire(void)
{
    printf("\n============================\n");
    printf("          VICTOIRE !\n");
    printf("============================\n");
    printf("Toutes les cases saines ont ete decouvertes.\n");
}

void afficherDefaite(void)
{
    printf("\n============================\n");
    printf("          DEFAITE !\n");
    printf("============================\n");
    printf("Vous avez touche une bombe.\n");
}

/*
 * Boucle commune aux deux modes.
 * Le placement des bombes est deja effectue avant son appel.
 */
void jouerPartie(int grille[TAILLE][TAILLE],
                 int decouverte[TAILLE][TAILLE],
                 int nombreBombes)
{
    int ligne, colonne;
    int casesSaines;
    int casesSainesDecouvertes;

    casesSaines = 36 - nombreBombes;

    while (1)
    {
        afficherGrille(grille, decouverte);

        ligne = demanderCoordonnee("Choisissez une ligne (1-6) : ");
        colonne = demanderCoordonnee("Choisissez une colonne (1-6) : ");

        ligne--;
        colonne--;

        if (caseDejaDecouverte(decouverte, ligne, colonne))
        {
            printf("Cette case a deja ete decouverte. "
                   "Choisissez une autre case.\n");
            continue;
        }

        if (grille[ligne][colonne] == 1)
        {
            afficherDefaite();
            break;
        }

        decouverte[ligne][colonne] = 1;

        casesSainesDecouvertes =
            compterCasesSainesDecouvertes(grille, decouverte);

        if (casesSainesDecouvertes == casesSaines)
        {
            afficherGrille(grille, decouverte);
            afficherVictoire();
            break;
        }
    }
}

/* Mode joueur contre ordinateur. */
void jouerContreOrdinateur(void)
{
    int grille[TAILLE][TAILLE];
    int decouverte[TAILLE][TAILLE];
    int nombreBombes;

    initialiserGrille(grille);
    initialiserDecouverte(decouverte);

    nombreBombes = demanderNombreBombes();

    placerBombesAleatoirement(grille, nombreBombes);

    printf("\nLa partie commence !\n");

    jouerPartie(grille, decouverte, nombreBombes);
}

/* Mode joueur contre joueur. */
void jouerContreHumain(void)
{
    int grille[TAILLE][TAILLE];
    int decouverte[TAILLE][TAILLE];
    int nombreBombes;

    initialiserGrille(grille);
    initialiserDecouverte(decouverte);

    nombreBombes = demanderNombreBombes();

    placerBombesHumain(grille, nombreBombes);

    printf("\nJoueur A, la grille est maintenant cachee.\n");
    printf("A vous de jouer !\n");

    jouerPartie(grille, decouverte, nombreBombes);
}
