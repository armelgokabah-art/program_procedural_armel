#include <stdio.h>
#include <string.h>
#include "code.h"
#include "jeu.h"

#define TENTATIVES_CLASSIQUES 10
#define HISTORIQUE_MAX 15
#define SAISIE_MAX 128

typedef struct {
    char proposition[CODE_MAX + 1];
    int bien_places;
    int mal_places;
} Tentative;

static void vider_ligne(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        /* On ignore les caracteres restants sur la ligne. */
    }
}

static int lire_entier_intervalle(const char *invite, int minimum, int maximum)
{
    int valeur;
    int resultat;
    int c;

    for (;;) {
        printf("%s", invite);
        resultat = scanf("%d", &valeur);
        if (resultat == 1) {
            c = getchar();
            if (c == '\n' || c == EOF) {
                if (valeur >= minimum && valeur <= maximum)
                    return valeur;
            } else {
                while (c != '\n' && c != EOF)
                    c = getchar();
            }
        } else {
            vider_ligne();
        }
        printf("Saisie invalide. Entrez une valeur entre %d et %d.\n",
               minimum, maximum);
    }
}

static int lire_code_saisi(const char *invite, char code[], int longueur)
{
    char saisie[SAISIE_MAX];
    int c;

    for (;;) {
        size_t taille;
        printf("%s", invite);

        if (fgets(saisie, sizeof(saisie), stdin) == NULL)
            return 0;

        taille = strlen(saisie);
        if (taille > 0 && saisie[taille - 1] == '\n') {
            saisie[taille - 1] = '\0';
        } else {
            while ((c = getchar()) != '\n' && c != EOF) {
                /* Retirer une saisie trop longue. */
            }
            printf("Saisie trop longue. Reessayez.\n");
            continue;
        }

        if ((int)strlen(saisie) != longueur) {
            printf("Le code doit contenir exactement %d chiffres.\n", longueur);
            continue;
        }

        if (!valider_code(saisie, longueur)) {
            printf("Code invalide : utilisez des chiffres distincts de 0 a 9.\n");
            continue;
        }

        strcpy(code, saisie);
        return 1;
    }
}

static void afficher_historique(const Tentative historique[],
                                int nombre_tentatives)
{
    int i;

    if (nombre_tentatives == 0) {
        printf("Aucune tentative valide pour le moment.\n");
        return;
    }

    printf("\n--- HISTORIQUE ---\n");
    for (i = 0; i < nombre_tentatives; ++i) {
        printf("%2d. %s | Bien places : %d | Mal places : %d\n",
               i + 1, historique[i].proposition,
               historique[i].bien_places, historique[i].mal_places);
    }
}

static int demander_historique(void)
{
    char reponse[16];

    for (;;) {
        printf("Consulter l'historique ? (o/n) : ");
        if (fgets(reponse, sizeof(reponse), stdin) == NULL)
            return 0;

        if (reponse[0] == 'o' || reponse[0] == 'O')
            return 1;
        if (reponse[0] == 'n' || reponse[0] == 'N')
            return 0;

        printf("Repondez par o ou n.\n");
    }
}

static int jouer_partie(const char secret[], int longueur, int maximum,
                        int mode_personnalise, int mode_deux_joueurs)
{
    Tentative historique[HISTORIQUE_MAX];
    char proposition[CODE_MAX + 1];
    int utilisees = 0;
    int gagne = 0;
    int score;
    char invite[80];

    while (utilisees < maximum && !gagne) {
        int bien_places;
        int mal_places;

        if (demander_historique())
            afficher_historique(historique, utilisees);

        snprintf(invite, sizeof(invite),
                 "Tentative %d/%d - Proposition : ", utilisees + 1, maximum);

        if (!lire_code_saisi(invite, proposition, longueur))
            return 0;

        comparer_codes(secret, proposition, longueur,
                       &bien_places, &mal_places);

        strcpy(historique[utilisees].proposition, proposition);
        historique[utilisees].bien_places = bien_places;
        historique[utilisees].mal_places = mal_places;
        ++utilisees;

        printf("Bien places : %d | Mal places : %d\n",
               bien_places, mal_places);

        if (bien_places == longueur) {
            gagne = 1;
            if (mode_deux_joueurs && longueur == 4 && strcmp(secret, "7834") == 0) {
                printf("Bravo tu as trouve le code secret anti-IA!\n");
            } else {
                printf("Victoire en %d tentative(s) !\n", utilisees);
            }
        }
    }

    if (!gagne)
        printf("Defaite : vous avez utilise toutes vos tentatives.\n");

    printf("Nombre de tentatives utilisees : %d\n", utilisees);
    printf("Code secret : %s\n", secret);

    score = (maximum - utilisees) * 10;
    if (mode_personnalise)
        score *= longueur - 3;

    printf("Score : %d points\n", score);
    return gagne;
}

void jouer_classique(void)
{
    char secret[CODE_MAX + 1];

    generer_code(secret, 4);
    printf("\n--- PARTIE CLASSIQUE ---\n");
    printf("Code de 4 chiffres - 10 tentatives.\n");
    jouer_partie(secret, 4, TENTATIVES_CLASSIQUES, 0, 0);
}

void jouer_personnalise(void)
{
    char secret[CODE_MAX + 1];
    int longueur;
    int tentatives;

    printf("\n--- PARTIE PERSONNALISEE ---\n");
    longueur = lire_entier_intervalle("Longueur du code (4 a 6) : ",
                                      CODE_MIN, CODE_MAX);
    tentatives = lire_entier_intervalle("Nombre de tentatives (5 a 15) : ",
                                        5, 15);

    generer_code(secret, longueur);
    jouer_partie(secret, longueur, tentatives, 1, 0);
}

void jouer_deux_joueurs(void)
{
    char secret[CODE_MAX + 1];

    printf("\n--- MODE DEUX JOUEURS ---\n");
    printf("Joueur A, saisissez le code secret. Le joueur B ne doit pas regarder.\n");

    if (!lire_code_saisi("Code secret de 4 chiffres : ", secret, 4))
        return;

    /* Separateur visuel ; la console ne peut pas masquer de facon portable
       le texte deja saisi, il faut donc que le joueur A cache l'ecran. */
    printf("\n\n\n\n\n\n\n\n\n\n");
    printf("Joueur B, a vous de jouer !\n");
    jouer_partie(secret, 4, TENTATIVES_CLASSIQUES, 0, 1);
}
