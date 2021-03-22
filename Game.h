#ifndef _GAME_H_
#define _GAME_H_

#include "WindowSurface.h"
#include "Boxies.h"
#include "Piece.h"
#include <iostream>
#include <vector>
#include <map>
#include <thread>
#include <chrono>

class Game
{

    private:
        WindowSurface* win;
        Piece piece_courante;
        bool yatilUnePieceDansLavion;
        bool yatilUnePieceEnTrainDeTomber;
        bool ZePartiiii;
        bool JustSpawned;
        int score;
        int largeur_grille;
        int hauteur_grille;
        std::vector<Boxies> grille;

        // methodes
        void addPieceToTheGrille();
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
