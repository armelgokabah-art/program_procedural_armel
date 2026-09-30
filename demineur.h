#ifndef DEMINEUR_H
#define DEMINEUR_H

#define TAILLE 6
#define MAX_BOMBES 18

void initialiserGrille(int grille[TAILLE][TAILLE]);
void initialiserDecouverte(int decouverte[TAILLE][TAILLE]);
void afficherGrille(int grille[TAILLE][TAILLE],
                    int decouverte[TAILLE][TAILLE]);
int demanderNombreBombes(void);
int demanderCoordonnee(const char *message);
void placerBombesAleatoirement(int grille[TAILLE][TAILLE], int nombreBombes);
void placerBombesHumain(int grille[TAILLE][TAILLE], int nombreBombes);
int caseDejaDecouverte(int decouverte[TAILLE][TAILLE], int ligne, int colonne);
int compterCasesSaines(int grille[TAILLE][TAILLE]);
int compterCasesSainesDecouvertes(int grille[TAILLE][TAILLE],
                                  int decouverte[TAILLE][TAILLE]);
void afficherVictoire(void);
void afficherDefaite(void);
void jouerPartie(int grille[TAILLE][TAILLE], int decouverte[TAILLE][TAILLE],
                 int nombreBombes);
void jouerContreOrdinateur(void);
void jouerContreHumain(void);

#endif
