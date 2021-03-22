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
        //Piece(int motif, int color);
        std::vector<Boxies> *get_boxies();
        bool chuter(int hauteur, std::vector<Boxies> grille);
        void gauche(int largeur, std::vector<Boxies> grille);
        void droite(int largeur, std::vector<Boxies> grille);
        // verif
        bool isPieceOnTheBorderX(int largeur);
        bool isPieceOnTheBorderY(int hauteur);
        bool isPieceOnTheGrilleX(std::vector<Boxies> grille);
        bool isPieceOnTheGrilleY(std::vector<Boxies> grille);

    protected:
        bool estPose;
        int orientation;
        std::vector<int> color;
        std::vector<Boxies> boxies;

        // methode
        void changerOrientation(int nouvelle_orientation);
        void poser();
};


#endif
