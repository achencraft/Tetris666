#ifndef _PIECE_H_
#define _PIECE_H_

#include "Boxies.h"
#include <vector>

class Piece 
{
    public:
        Piece();

    protected:
        bool estPose;
        int orientation;
        std::vector<Boxies> boxies;
        std::vector<int> color;

        // methode
        void changerOrientation(int nouvelle_orientation);
        void poser();
};


#endif