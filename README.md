# Labo 2 — Démineur en C

## Fichiers

- `main.c` : menu principal et lancement des modes.
- `demineur.c` : fonctions du jeu.
- `demineur.h` : constantes et prototypes.
- `Makefile` : compilation avec GCC.

## Compilation avec GCC

```bash
gcc -Wall -Wextra -std=c11 main.c demineur.c -o demineur
```

Puis :

```bash
./demineur
```

Sous Windows :

```text
demineur.exe
```

## Règles implémentées

- Grille 6 × 6.
- `0` = case saine, `1` = bombe.
- `?` = case cachée.
- `-` = case saine découverte.
- Maximum 18 bombes.
- Placement aléatoire sans doublon contre l'ordinateur.
- Placement manuel sans doublon contre un humain.
- Coordonnées limitées à 1–6.
- Une case déjà découverte ne compte pas deux fois.
- Défaite immédiate en cas de bombe.
- Victoire lorsque toutes les cases saines sont découvertes.
- Menu : ordinateur / humain / quitter.
