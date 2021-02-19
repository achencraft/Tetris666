#ifndef _GAME_H_
#define _GAME_H_

#include "WindowSurface.h"
#include "Boxies.h"
#include <iostream>
#include <vector>
#include <map>

class Game
{
    
    private:
        WindowSurface* win;
        int score;
        int largeur_grille;
        int hauteur_grille;
        std::vector<std::vector<Boxies>> matrice_jeu;

        // methodes
        void verificationLignes();
        bool verificationFinJeu();



    public:
        inline Game():
            win(nullptr) {};
        void init();
        void draw();
        void keyboard(const Uint8* keys);
        void loop();

};


#endif