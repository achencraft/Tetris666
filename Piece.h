#ifndef _PIECE_H_
#define _PIECE_H_

#include "Boxies.h";

class Piece {
    public:
        Piece();

    protected:
        bool estPose:
        int orientiation;
        std::vector<Boxies> boxies;
        std::vector<int> color;

        // methode
        void changerOrientation(int nouvelle_orientation);
        void poser();
}


#endif