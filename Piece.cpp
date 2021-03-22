#include "Piece.h"

Piece::Piece() {
    this->estPose = false;
    int orientation = 0;

    //on créé un seul boxi pour l'instant
    Boxies b = Boxies("boxi",0,0);
    boxies.insert(boxies.end(),b);
}

/*Piece::Piece(int motif, int color)
{

}*/

void Piece::changerOrientation(int nouvelle_orientation) {
    orientation = nouvelle_orientation;
}

std::vector<Boxies> *Piece::get_boxies() {
  return &boxies;
}

void Piece::poser() {
    estPose = true;
}

void Piece::chuter(int hauteur)
{
  if(this->isPieceOnTheBorderY(hauteur)) {
    std::for_each(boxies.begin(),boxies.end(), std::mem_fun_ref(&Boxies::chuter));
  }
}

void Piece::gauche(int largeur)
{
  if(this->isPieceOnTheBorderX(largeur)) {
    std::for_each(boxies.begin(),boxies.end(), std::mem_fun_ref(&Boxies::gauche));
  }
}

void Piece::droite(int largeur)
{
  if(this->isPieceOnTheBorderX(largeur)) {
    std::for_each(boxies.begin(),boxies.end(), std::mem_fun_ref(&Boxies::droite));
  }
}

bool Piece::isPieceOnTheBorderX(int largeur) {
  // bool isBord = true;
  // bords de l'écran
  for (size_t i = 0; i < this->boxies.size(); i++) {
    if(this->boxies[i].get_x() < 0 || this->boxies[i].get_x()+40 >= largeur) {
      return false;
    }
  }
  return true;
}

bool Piece::isPieceOnTheBorderY(int hauteur) {
  // bool isBord = true;
  // bords de l'écran
  for (size_t i = 0; i < this->boxies.size(); i++) {
    // std::cout << "y = " << this->boxies[i].get_y() << ", hauteur = " << hauteur << "\n";
    if(this->boxies[i].get_y() < 0 || this->boxies[i].get_y()+40 >= hauteur) {
      return false;
    }
  }
  return true;
}

// bool Piece::isPieceOnTheGrilleX()
