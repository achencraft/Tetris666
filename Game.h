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
        
        Piece piece_courante;
        Piece piece_suivante;
        Piece piece_sauvegarde;
        bool yatilUnePieceSauvee;
        bool ZePartiiii;
        bool JustSpawned;
        bool yatilUnePieceDansLavion;
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
        Game();
        void init(int largeur_grille, int hauteur_grille);
        void check_nouvelle_piece();
        bool actualiser_chute();
        void debuter_partie();
        void droite();
        void gauche();
        void rotation();
        void sauvegarde();
        std::vector<Boxi> get_grille();
        Piece get_piece_courante();
        bool yatilUnePieceEnTrainDeTomber;



};


#endif
