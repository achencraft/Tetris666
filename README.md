# Tetris666

## Présentation du projet

Projet réalisé par Lucas LETT et Morgane SCHIEBER dans le cadre de l'UE de
Programmation Avancée.

Le but du projet était de réaliser un Tetris en C++ à l'aide de la librairie SDL2.
Le projet doit respecter les règles de la version originale avec un gameplay s'en
approche le plus possible.

Il y a le mode marathon classique, mais également 1v1 (pour jouer à deux pour
deux fois plus de fun) ainsi qu'un mode vs IA (nous espérons avoir pu mettre à -
profits nos connaissances acquises en cours d'IA le semestre dernier!) *(c'est pas
vrai, c'est pas une IA très intelligente)* ainsi qu'un mode spécial et secret
accessible à qui se sent d'humeur aventureuse: le mode Carnage.

Bon jeu à vous! N'hésitez pas à nous partager vos high-score pour voir qui est  
destiné à devenir le prochain Grand Maître Tetris.

## Installations

`sudo apt-get install libsdl2-dev libsdl2-ttf-dev`

## Compilation

```bash
$ cmake .
$ make
```

## Lancement du jeu

```bash
$ ./Tetris666
```

## Modes de jeu

### Mode Solo

Le mode solo est ce qui se rapproche d'un tetris habituel, il se joue seul et
le but est de détruire votre record personnel afin de montrer que personne n'est
plus fort que vous. Même pas vous-même.

#### Commandes

* **Flèche du haut:** rotation
* **Flèche de gauche:** aller à gauche
* **Flèche de droite:** aller à droite
* **Flèche du bas:** poser la pièce
* **SHIFT droit:** Sauvegarder la pièce

### Mode 1v1

Mode un contre un local, se joue sur le même ordinateur, chacun d'un côté du
clavier. Celui qui a le plus de points à la fin de la partie a gagné!

Mais attention, quand l'un remplit une ligne, l'autre la reçoit et voit sa zone
de jeu réduite!


#### Commandes

##### Joueur 1 (droite):

* **Flèche du haut:** rotation
* **Flèche de gauche:** aller à gauche
* **Flèche de droite:** aller à droite
* **Flèche du bas:** poser la pièce
* **SHIFT droit:** Sauvegarder la pièce

##### Joueur 2 (gauche):

* **Z:** rotation
* **Q:** aller à gauche
* **D** aller à droite
* **S** poser la pièce
* **SHIFT gauche:** Sauvegarder la pièce

### Mode VS IA

Mode de jeu contre l'ordinateur. Pour le moment il n'y a pas de mode de difficulté,
le seul implémenté est le mode *(très très très)* facile. L'IA n'est pas être
rusée.

De même que pour le mode 1v1, quand l'un des deux joueurs remplit une ligne,
l'autre la reçoit en guise de malus!

#### Commandes

* **Flèche du haut:** rotation
* **Flèche de gauche:** aller à gauche
* **Flèche de droite:** aller à droite
* **Flèche du bas:** poser la pièce
* **SHIFT droit:** Sauvegarder la pièce

### Mode Carnage

    "Vous qui entrez ici, abandonnez toute espérance."

    Dante Alighieri, Enfers, Chant III.


*(À vos risques et périls...)*
