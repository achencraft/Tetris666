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
        Piece(std::vector<Boxi> motif, int color, int largeur);
        std::vector<Boxi> *get_boxies();
        bool chuter(int hauteur, std::vector<Boxi> grille);
        void gauche(int largeur, std::vector<Boxi> grille);
        void droite(int largeur, std::vector<Boxi> grille);
        void rotation(int largeur, int hauteur, std::vector<Boxi> grille);
        void remonter(int largeur, std::vector<Boxi> grille);
        void poser();
        // verif
        bool isPieceOnTheBorderLeft(int largeur);
        bool isPieceOnTheBorderRight(int largeur);
        bool isPieceOnTheBorderY(int hauteur);
        bool isPieceOnTheGrilleLeft(std::vector<Boxi> grille);
        bool isPieceOnTheGrilleRight(std::vector<Boxi> grille);
        bool isPieceOnTheGrilleY(std::vector<Boxi> grille);
        bool isRotaValid(int largeur, int hauteur, std::vector<Boxi> grille);
        void get_piece_dim(int *h, int *w, int *x, int *y);

    protected:

        bool estPose;
        std::vector<int> color;
        std::vector<Boxi> boxies;

        // methode
        


        
};


#endif
