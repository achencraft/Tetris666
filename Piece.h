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

    protected:
        bool estPose;
        int orientation;
        std::vector<int> color;
        std::vector<Boxies> boxies;

        // methode
        void changerOrientation(int nouvelle_orientation);
        void poser();
        void chuter();
};


#endif
