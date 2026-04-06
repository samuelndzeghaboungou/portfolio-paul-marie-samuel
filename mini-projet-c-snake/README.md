# Mini-projet C: Snake Stable (Raylib)

Ce mini-projet est pense pour un niveau debutant/intermediaire: code clair, mecaniques de jeu interessantes, et execution stable.

## 1) Objectif

Construire un jeu desktop en C avec Raylib qui respecte les exigences du TP:

- Langage C (C11)
- Application desktop
- Bibliotheque graphique Raylib
- Code structure (fonctions, separation `main.c` / `game.c`)
- Gestion memoire propre (`malloc` + `free`)
- README de compilation/execution

## 2) Fonctionnalites du jeu

- Deplacement au clavier (fleches)
- Collision murs + corps
- Collision obstacles
- Nourriture aleatoire
- Score + meilleur score sauvegarde dans `best_score.txt`
- Vitesse qui augmente progressivement
- Niveaux progressifs (obstacles plus nombreux)
- Menu de demarrage (choix options)
- 3 difficultes (Easy / Normal / Hard)
- Mode challenge 60 secondes (objectif: survivre jusqu'a la fin)
- Pause (`P`)
- Restart propre (`R`)
- Boucle de jeu a tick fixe pour un comportement stable

## 3) Structure du projet

- `src/main.c`: fenetre, boucle principale, interface score
- `src/game.c`: logique Snake (update, collisions, rendu, score, niveaux)
- `include/game.h`: structures et API
- `Makefile`: build simple

## 4) Prerequis

- GCC ou Clang
- Raylib installee
- Windows/Linux/macOS (desktop)

## 5) Compilation (Windows, MinGW)

### Option rapide PowerShell (recommandee sous Windows)

Cette option utilise automatiquement `C:\msys64\ucrt64\bin\gcc.exe`.
Le script copie aussi les DLL runtime necessaires (`libraylib.dll`, `glfw3.dll`, etc.) dans le dossier du projet.
Si MSYS2/Raylib ne sont pas encore installes:

```powershell
C:\msys64\usr\bin\bash.exe -lc "pacman -S --noconfirm --needed mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-raylib"
```

Compiler:

```powershell
powershell -ExecutionPolicy Bypass -File .\build.ps1
```

Compiler + lancer:

```powershell
powershell -ExecutionPolicy Bypass -File .\build.ps1 -Run
```

Compiler avec AddressSanitizer:

```powershell
powershell -ExecutionPolicy Bypass -File .\build.ps1 -Sanitize
```

### Option Makefile

```bash
make
```

Puis execution:

```bash
make run
```

Build avec AddressSanitizer (debug memoire):

```bash
make asan
./snake.exe
```

> Si `-fsanitize=address` n'est pas supporte sur ton compilateur Windows, utilise WSL ou Clang.

## 6) Compilation alternative (commande directe)

```bash
gcc -std=c11 -Wall -Wextra -Wpedantic -Iinclude src/main.c src/game.c -o snake.exe -lraylib -lopengl32 -lgdi32 -lwinmm
```

## 7) Commandes de jeu

- Fleches: bouger
- `ENTREE` (menu): lancer la partie
- `TAB`: retour menu
- `M` (menu): activer/desactiver challenge
- `P`: pause
- `R`: recommencer
- `ESC`: quitter

## 8) Stabilite et memoire

- Allocation dynamique du corps du serpent au demarrage
- Liberation complete en fin d'execution (`game_shutdown`)
- Aucun acces hors limites volontaire
- Update logique base sur un tick fixe (evite les bugs lies au FPS)

## 9) Conseils soutenance

### Video demo (2 a 4 min)

- Intro rapide: objectif + techno (C + Raylib)
- Montrer le gameplay (score, acceleration, game over, restart)
- Montrer un extrait du code (`game_update`, `snake_step`, `game_shutdown`)
- Montrer la compilation avec warnings actives

### Presentation orale courte

- Architecture du code
- Gestion memoire
- Difficultes rencontrees et corrections
- Pistes d'amelioration (obstacles, niveaux, sons)

## 10) Collaboration GitHub (groupe)

1. Un membre cree le repository.
2. Il invite les autres membres comme collaborateurs.
3. Chacun pousse des commits clairs (ex: `feat: collision body`, `fix: pause state`).
4. README + source + fichiers necessaires presents.

## 11) Date limite

- Rendu et soutenance: **06/04/2026**

Bon courage, et surtout: un Snake robuste et bien explique vaut beaucoup plus qu'un projet trop grand instable.
