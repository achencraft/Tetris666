#include "Piece.h"

Piece::Piece() {
    this->estPose = false;
    int orientation = 0;

    //on créé un seul boxi pour l'instant
    Boxies b = Boxies("boxi",5,5);
    boxies.insert(boxies.end(),b);
}

/*Piece::Piece(int motif, int color)
{

}*/


void Piece::changerOrientation(int nouvelle_orientation) {
    orientation = nouvelle_orientation;
}

void Piece::poser() {
    estPose = true;
}

void Piece::chuter()
{
    //appelle la méthode chuter sur chaque boxies de la liste
    std::for_each(boxies.begin(),boxies.end(), std::mem_fun_ref(&Boxies::chuter));
}

std::vector<Boxies> Piece::get_boxies() {
  return boxies;
}
