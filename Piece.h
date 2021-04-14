#ifndef _PIECE_H_
#define _PIECE_H_

#include "Boxi.h"
#include <vector>
#include <algorithm>
#include <functional>

class Piece
{
    public:
        Piece();
        Piece(std::vector<Boxi> motif, int largeur);
        std::vector<Boxi> *get_boxies();
        bool chuter(int hauteur, std::vector<Boxi> grille);
        void up(std::vector<Boxi> grille);
        void gauche(int largeur, std::vector<Boxi> grille);
        void droite(int largeur, std::vector<Boxi> grille);
        void rotation(int largeur, int hauteur, std::vector<Boxi> grille);
        void remonter(int largeur, std::vector<Boxi> grille);
        void poser();
        SDL_Color get_color();
        // verif
        bool isPieceOnTheBorderLeft(int largeur);
        bool isPieceOnTheBorderRight(int largeur);
        bool isPieceOnTheBorderDown(int hauteur);
        bool isPieceOnTheBorderUp();
        bool isPieceOnTheGrilleLeft(std::vector<Boxi> grille);
        bool isPieceOnTheGrilleRight(std::vector<Boxi> grille);
        bool isPieceOnTheGrilleDown(std::vector<Boxi> grille);
        bool isPieceOnTheGrilleUp(std::vector<Boxi> grille);
        bool isRotaValid(int largeur, int hauteur, std::vector<Boxi> grille);
        void get_piece_dim(int *h, int *w, int *x, int *y);

    protected:

        bool estPose;
        SDL_Color color;
        std::vector<Boxi> boxies;

        // methode
        


        
};


#endif
