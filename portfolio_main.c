
#include <stdio.h>
#include <stdlib.h>

/* =========================
   PROGRAMME : MON PROFIL
   DE DEVELOPPEUR
   ========================= */

void afficherProfil()
{
    printf("\n");
    printf("============================================\n");
    printf("              MON PROFIL\n");
    printf("============================================\n");

    printf("\nNom et prenom : GOK ABAH ARMEL RODRIGUE\n");
    printf("Formation     : Bachelier en Informatique de Gestion\n");
    printf("Etablissement : ITLG - Liege, Belgique\n");

    printf("\nPresentation :\n");
    printf("Je suis GOK ABAH Armel Rodrigue,\n");
    printf("futur bachelier en Informatique de Gestion.\n");
    printf("Je suis interesse par l'ingenierie logicielle,\n");
    printf("les bases de donnees, les reseaux et le design UI/UX.\n");

    printf("\nGitHub : github.com/armelgokabah-art\n");

    printf("\n============================================\n");
}


void afficherCompetences()
{
    printf("\n");
    printf("============================================\n");
    printf("           MES COMPETENCES\n");
    printf("============================================\n");

    printf("\n1. Java\n");
    printf("   Niveau : 4/5\n");

    printf("\n2. SQL\n");
    printf("   Niveau : 4/5\n");

    printf("\n3. Modelisation UML\n");
    printf("   Niveau : 4/5\n");

    printf("\n4. Reseaux informatiques\n");
    printf("   Niveau : 4/5\n");

    printf("\n5. Protocoles OSI / TCP-IP\n");
    printf("   Niveau : 4/5\n");

    printf("\n6. Gestion Agile\n");
    printf("   Niveau : 3/5\n");

    printf("\n7. UI/UX\n");
    printf("   Niveau : 3/5\n");

    printf("\n============================================\n");
}


void afficherProjets()
{
    printf("\n");
    printf("============================================\n");
    printf("              MES PROJETS\n");
    printf("============================================\n");

    printf("\nProjet 1\n");
    printf("Nom        : Projet Java\n");
    printf("Technologie: Java\n");
    printf("Statut     : Finalise\n");

    printf("\nProjet 2\n");
    printf("Nom        : Base de donnees\n");
    printf("Technologie: SQL / UML\n");
    printf("Statut     : Finalise\n");

    printf("\nProjet 3\n");
    printf("Nom        : Projet reseau\n");
    printf("Technologie: Reseaux informatiques\n");
    printf("Statut     : Finalise\n");

    printf("\n============================================\n");
}


void afficherStatistiques()
{
    int nombreTechnologies = 7;
    int nombreProjets = 3;
    int projetsTermines = 3;

    float pourcentageTermines;

    pourcentageTermines =
        ((float)projetsTermines / nombreProjets) * 100;

    printf("\n");
    printf("============================================\n");
    printf("            MES STATISTIQUES\n");
    printf("============================================\n");

    printf("\nNombre de technologies connues : %d\n",
           nombreTechnologies);

    printf("Nombre total de projets        : %d\n",
           nombreProjets);

    printf("Projets termines               : %d\n",
           projetsTermines);

    printf("Pourcentage de projets termines: %.0f%%\n",
           pourcentageTermines);

    printf("Niveau moyen declare           : 3.7/5\n");

    printf("\nTechnologies principales :\n");
    printf("- Java\n");
    printf("- SQL\n");
    printf("- UML\n");

    printf("\n============================================\n");
}


int main()
{
    int choix;

    do
    {
        printf("\n\n");
        printf("============================================\n");
        printf("       MON PROFIL DE DEVELOPPEUR\n");
        printf("============================================\n");

        printf("\n");
        printf("1. Afficher mon profil\n");
        printf("2. Afficher mes competences\n");
        printf("3. Afficher mes projets\n");
        printf("4. Afficher mes statistiques\n");
        printf("0. Quitter\n");

        printf("\nVotre choix : ");
        scanf("%d", &choix);

        switch (choix)
        {
            case 1:
                afficherProfil();
                break;

            case 2:
                afficherCompetences();
                break;

            case 3:
                afficherProjets();
                break;

            case 4:
                afficherStatistiques();
                break;

            case 0:
                printf("\nMerci d'avoir consulte mon profil !\n");
                printf("Au revoir !\n");
                break;

            default:
                printf("\nChoix invalide !\n");
                printf("Veuillez choisir entre 0 et 4.\n");
        }

    } while (choix != 0);

    return 0;
}