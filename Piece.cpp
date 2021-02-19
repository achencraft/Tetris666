#include "Piece.h"

Piece::Piece() {}

void Piece::changerOrientation(int nouvelle_orientation) {
    orientation = nouvelle_orientation;
}

void Piece::poser() {
    estPose = true;
}