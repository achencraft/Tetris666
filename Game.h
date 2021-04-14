#ifndef _GAME_H_
#define _GAME_H_

#include "WindowSurface.h"
#include "Boxi.h"
#include "Piece.h"
#include <iostream>
#include <vector>
#include <sys/time.h>
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
        bool yatilUnePieceEnTrainDeTomber;
        int tour;
        int score;
        int quiSuisJe;

        int largeur_grille;
        int hauteur_grille;
        std::vector<Boxi> grille;
        std::vector<std::vector<Boxi>> liste_pieces;

        // methodes
        void addPieceToTheGrille();
        int verificationLignes();
        Piece nouvelle_piece();
        void creer_pieces();
        void sauvegarde_piece();




    public:
        Game();
        void init(int largeur_grille, int hauteur_grille, int player);
        void check_nouvelle_piece();
        int actualiser_chute();
        void debuter_partie();
        void droite();
        void gauche();
        void rotation();
        void sauvegarde();
        void ajouter_ligne(int nbr);
        std::vector<Boxi> get_grille();
        Piece get_piece_courante();
        Piece get_piece_suivante();
        Piece get_piece_sauvegarde();
        bool get_yatilUnePieceEnTrainDeTomber();
        bool get_yatilUnePieceSauvee();
        int get_score();
        int getPlayer();
        bool EstCeFini();




};


#endif
