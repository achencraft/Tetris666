#ifndef _PIECE_H_
#define _PIECE_H_

#include "Boxies.h"
#include <vector>
#include <algorithm>
#include <functional>

class Piece
{
    public:
        Piece();
        Piece(std::vector<Boxies> motif, int color, int largeur);
        std::vector<Boxies> *get_boxies();
        bool chuter(int hauteur, std::vector<Boxies> grille);
        void gauche(int largeur, std::vector<Boxies> grille);
        void droite(int largeur, std::vector<Boxies> grille);
        void rotation(int largeur, int hauteur, std::vector<Boxies> grille);
        void poser();
        // verif
        bool isPieceOnTheBorderLeft(int largeur);
        bool isPieceOnTheBorderRight(int largeur);
        bool isPieceOnTheBorderY(int hauteur);
        bool isPieceOnTheGrilleLeft(std::vector<Boxies> grille);
        bool isPieceOnTheGrilleRight(std::vector<Boxies> grille);
        bool isPieceOnTheGrilleY(std::vector<Boxies> grille);
        bool isRotaValid(int largeur, int hauteur, std::vector<Boxies> grille);

    protected:

        bool estPose;
        std::vector<int> color;
        std::vector<Boxies> boxies;

        // methode
        void get_piece_dim(int *h, int *w, int *x, int *y);


        
};


#endif
