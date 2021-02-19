#ifndef _GAME_H_
#define _GAME_H_

#include "WindowSurface.h"

class Game
{
    
    private:
        int score;
        int largeur_grille;
        int hauteur_grille;
        std::vector<std::vector<Boxies>> matrice_jeu;

        // methodes
        void verificationLignes();
        bool verificationFinJeu();



    public:
        Game();
        void init();
        void draw();
        void keyboard();
        void loop();

};


#endif