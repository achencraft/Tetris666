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

bool Piece::chuter(int hauteur, std::vector<Boxies> grille)
{
  if(this->isPieceOnTheBorderY(hauteur) && this->isPieceOnTheGrilleY(grille)) {
    std::for_each(boxies.begin(),boxies.end(), std::mem_fun_ref(&Boxies::chuter));
    return true;
  }
  return false;
}

void Piece::gauche(int largeur, std::vector<Boxies> grille)
{
  if(this->isPieceOnTheBorderLeft(largeur) && this->isPieceOnTheGrilleX(grille)) {
    std::for_each(boxies.begin(),boxies.end(), std::mem_fun_ref(&Boxies::gauche));
  }
}

void Piece::droite(int largeur, std::vector<Boxies> grille)
{
  if(this->isPieceOnTheBorderRight(largeur) && this->isPieceOnTheGrilleX(grille)) {
    std::for_each(boxies.begin(),boxies.end(), std::mem_fun_ref(&Boxies::droite));
  }
}

bool Piece::isPieceOnTheBorderLeft(int largeur) {
  // bool isBord = true;
  // bords de l'écran
  for (size_t i = 0; i < this->boxies.size(); i++) {
    if(this->boxies[i].get_x() <= 0) {
      return false;
    }
  }
  return true;
}

bool Piece::isPieceOnTheBorderRight(int largeur) {
  // bool isBord = true;
  // bords de l'écran
  
  for (size_t i = 0; i < this->boxies.size(); i++) {
    if(this->boxies[i].get_x()+1 >= largeur) {
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
    if(this->boxies[i].get_y() < 0 || this->boxies[i].get_y()+1 >= hauteur) {
      return false;
    }
  }
  return true;
}

bool Piece::isPieceOnTheGrilleX(std::vector<Boxies> grille) {
  for (size_t i = 0; i < this->boxies.size(); i++) {
    for (size_t j = 0; j < grille.size(); j++) {
      // on est sur la même ligne qu'une autre pièce
      if(this->boxies[i].get_y() == grille[j].get_y()) {
        std::cout << "jsuis sur la même ligne moi\n";
        // y a une pièce à gauche
        if(this->boxies[i].get_x() == grille[j].get_x()+1) {
          return false;
        }
        // y a une pièce à droite
        if(this->boxies[i].get_x()+1 == grille[j].get_x()) {
          return false;
        }
      }
    }
  }
  return true;
}

bool Piece::isPieceOnTheGrilleY(std::vector<Boxies> grille) {
  for (size_t i = 0; i < this->boxies.size(); i++) {
    for (size_t j = 0; j < grille.size(); j++) {
      // ils sont sur la même colonne
      if(this->boxies[i].get_x() == grille[i].get_x()) {
        if(this->boxies[i].get_y()+1 == grille[j].get_y()) {
          return false;
        }
      }
    }
  }
  return true;
}
