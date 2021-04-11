#ifndef _GAME_H_
#define _GAME_H_

#include "WindowSurface.h"
#include "Boxi.h"
#include "Piece.h"
#include <iostream>
#include <vector>
#include <map>
#include <thread>
#include <chrono>
#include <string>

class Game
{

    private:
        WindowSurface* win;
        Piece piece_courante;
        Piece piece_suivante;
        Piece piece_sauvegarde;
        bool yatilUnePieceSauvee;
        bool yatilUnePieceDansLavion;
        bool yatilUnePieceEnTrainDeTomber;
        bool ZePartiiii;
        bool JustSpawned;
        int tour;
        int score;
        int largeur_grille;
        int hauteur_grille;
        std::vector<Boxi> grille;
        std::vector<std::vector<Boxi>> liste_pieces;

        // methodes
        void addPieceToTheGrille();
        void verificationLignes();
        bool verificationFinJeu();
        Piece nouvelle_piece();
        void creer_pieces();
        void sauvegarde_piece();



    public:
        inline Game():
            win(nullptr) {};
        void init(int largeur_grille, int hauteur_grille);
        void draw(int largeur, int hauteur);
        void draw_boxi(int x, int y, int taille);
        void draw_boxi_right(int sx, int sy, int x, int y, int taille);
        void loop();

};


#endif
