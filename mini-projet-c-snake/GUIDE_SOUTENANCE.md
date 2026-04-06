# Guide soutenance (1 page) - Mini-projet C Snake

## 1) Pitch (30 secondes)

Bonjour, notre mini-projet est un jeu Snake desktop developpe en C11 avec Raylib.
L'objectif etait de produire une application stable, claire et demonstrable.
Le jeu inclut un menu, plusieurs difficultes, un mode challenge 60 secondes,
un systeme de niveaux avec obstacles, un score et un meilleur score sauvegarde.

## 2) Ce que je montre en video (2 a 4 minutes)

1. Compilation et lancement
- Je lance le script run.ps1 depuis le terminal.
- J'explique que le script compile puis lance automatiquement le jeu.

2. Menu principal
- Je montre le choix de difficulte (Easy, Normal, Hard).
- Je montre l'activation du mode challenge 60 secondes.

3. Gameplay
- Deplacement avec les fleches.
- Collision mur/corps/obstacle.
- Augmentation de la vitesse.
- Progression des niveaux et apparition d'obstacles.

4. Fin de partie
- Ecran GAME OVER en cas de collision.
- Ecran VICTOIRE si challenge termine.
- Restart avec R.

5. Persistance
- Je montre que le best score est conserve entre les sessions.

## 3) Plan oral (3 a 5 minutes)

1. Architecture
- main.c: fenetre, boucle principale, affichage UI.
- game.c: logique du jeu (deplacement, collisions, niveaux, challenge).
- game.h: structures et API.

2. Gestion memoire
- Le serpent est alloue dynamiquement au demarrage.
- Liberation propre en fin avec game_shutdown.
- Pas de fuite memoire volontaire.

3. Stabilite technique
- Tick fixe pour la logique de jeu (comportement stable quel que soit le FPS).
- Verification build avec drapeaux de warnings.
- Runtime fiabilise sous Windows avec copie des DLL necessaires.

4. Choix de conception
- Projet volontairement scope pour rester robuste.
- Features progressives pour garder le code comprehensible.

## 4) Questions probables et reponses courtes

Q: Pourquoi C et pas un autre langage ?
R: Pour travailler la memoire manuelle, la performance et les structures de donnees.

Q: Comment vous evitez les crashs ?
R: Validation des etats, collisions explicites, boucle a tick fixe et checks de build.

Q: Ou est la gestion memoire ?
R: Allocation dans game_init, liberation dans game_shutdown.

Q: Quelle est la partie la plus importante du code ?
R: snake_step et game_update, car elles controlent la logique centrale du jeu.

## 5) Script de demo conseille (a lire)

- Je compile et je lance le jeu.
- Je choisis la difficulte Normal puis je lance une partie.
- Je montre une collision, puis un restart.
- J'active le mode challenge et je montre le timer.
- Je conclus avec l'architecture du code et la gestion memoire.

## 6) Checklist avant soutenance

- Le jeu se lance sans erreur.
- Le son et la fenetre fonctionnent (si actifs).
- Le best score se sauvegarde.
- Le README est a jour.
- Le depot GitHub contient des commits clairs et reguliers.
- Chaque membre du groupe peut expliquer une partie du code.
