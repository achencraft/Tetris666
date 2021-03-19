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
        void chuter(int hauteur);
        void gauche(int largeur);
        void droite(int largeur);
        // bool isPieceOnTheBorder(std::vector<Boxies> grille);
        bool isPieceOnTheBorderX(int largeur);
        bool isPieceOnTheBorderY(int hauteur);

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
