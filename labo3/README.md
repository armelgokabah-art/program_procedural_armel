# Labo 3 — Codebreaker en C

## Contenu
- `main.c` : lancement du programme et menu principal.
- `code.c` / `code.h` : génération, validation et comparaison des codes.
- `jeu.c` / `jeu.h` : déroulement des parties, historique et score.
- `Makefile` : compilation avec `make` et nettoyage avec `make clean`.
- `Codebreaker.cbp` : projet Code::Blocks.

## Compilation avec Code::Blocks
1. Ouvrir `Codebreaker.cbp`.
2. Choisir **Build** puis **Build and Run** (ou appuyer sur F9).
3. Le projet utilise le compilateur C configuré dans Code::Blocks.

Les fichiers `main.c`, `code.c` et `jeu.c` doivent rester ajoutés au projet.

## Compilation en terminal
Avec GCC et Make installés, depuis ce dossier :

```sh
make
./codebreaker
```

Pour supprimer les fichiers générés :

```sh
make clean
```

## Règles implémentées
- Mode classique : code de 4 chiffres distincts, 10 tentatives.
- Mode personnalisé : longueur de 4 à 6 chiffres, de 5 à 15 tentatives.
- Mode deux joueurs : le joueur A choisit un code de 4 chiffres, le joueur B dispose de 10 tentatives.
- Une saisie invalide est refusée et ne consomme pas de tentative.
- L'historique garde les propositions valides et leurs deux indices.
- La comparaison utilise des paramètres pointeurs pour retourner les résultats.

## Formule du score
Le score est calculé avec les tentatives restantes : `(tentatives_max - tentatives_utilisees) * 10`.
En mode personnalisé, ce résultat est multiplié par `(longueur_du_code - 3)`. Ainsi, un code plus long donne un coefficient plus élevé. Une partie gagnée à la dernière tentative rapporte zéro point, car il ne reste aucune tentative.

## À savoir
La console standard ne permet pas de masquer de façon portable les caractères saisis pour le code secret du joueur A. En mode deux joueurs, le programme affiche plusieurs lignes vides après la saisie ; le joueur A doit aussi cacher l'écran pendant cette étape.
