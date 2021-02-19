#include "Piece.h"

Piece::Piece() {}

Piece::changerOrientation(int nouvelle_orientation) {
    this.orientation = nouvelle_orientation;
}

Piece::poser() {
    this.estPose = true;
}