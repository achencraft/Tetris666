#include "Piece.h"

Piece::Piece() {
    this->estPose = false;
    
    //on créé un seul boxi pour l'instant
    Boxies b = Boxies("boxi",0,0);
    Boxies b1 = Boxies("boxi",1,0);
    Boxies b2 = Boxies("boxi",2,0);
    //Boxies b3 = Boxies("boxi",3,0);
    boxies.insert(boxies.end(),b);
    boxies.insert(boxies.end(),b1);
    boxies.insert(boxies.end(),b2);
    //boxies.insert(boxies.end(),b3);

}

/*Piece::Piece(int motif, int color)
{

}*/


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
  if(this->isPieceOnTheBorderLeft(largeur) && this->isPieceOnTheGrilleLeft(grille)) {
    std::for_each(boxies.begin(),boxies.end(), std::mem_fun_ref(&Boxies::gauche));
  }
}

void Piece::droite(int largeur, std::vector<Boxies> grille)
{
  if(this->isPieceOnTheBorderRight(largeur) && this->isPieceOnTheGrilleRight(grille)) {
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

bool Piece::isPieceOnTheGrilleLeft(std::vector<Boxies> grille) {
  for (size_t i = 0; i < this->boxies.size(); i++) {
    for (size_t j = 0; j < grille.size(); j++) {
      // on est sur la même ligne qu'une autre pièce
      if(this->boxies[i].get_y() == grille[j].get_y()) {
        // y a une pièce à gauche
        if(this->boxies[i].get_x() == grille[j].get_x()+1) {
          return false;
        }
      }
    }
  }
  return true;
}

bool Piece::isPieceOnTheGrilleRight(std::vector<Boxies> grille) {
  for (size_t i = 0; i < this->boxies.size(); i++) {
    for (size_t j = 0; j < grille.size(); j++) {
      // on est sur la même ligne qu'une autre pièce
      if(this->boxies[i].get_y() == grille[j].get_y()) {
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
      if(this->boxies[i].get_x() == grille[j].get_x()) {
        if(this->boxies[i].get_y()+1 == grille[j].get_y()) {
          return false;
        }
      }
    }
  }
  return true;
}

void Piece::get_piece_dim(int *h, int *w, int *x, int *y)
{
    int max_y = 0, max_x = 0;
    int min_y = this->boxies.at(0).get_y(), min_x = this->boxies.at(0).get_x();
    for (size_t i = 0; i < this->boxies.size(); i++) {
        if(this->boxies.at(i).get_y() > max_y)
            max_y = this->boxies.at(i).get_y();
        if(this->boxies.at(i).get_x() > max_x)
            max_x = this->boxies.at(i).get_x();
        if(this->boxies.at(i).get_y() < min_y)
            min_y = this->boxies.at(i).get_y();
        if(this->boxies.at(i).get_x() < min_x)
            min_x = this->boxies.at(i).get_x();
    }

    *h = max_y - min_y + 1;
    *w = max_x - min_x + 1;
    *x = min_x;
    *y = min_y;
}


void Piece::rotation(int largeur, int hauteur,  std::vector<Boxies> grille)
{

  if(!this->estPose)
  {
    int largeur_piece, hauteur_piece, local_zero_x, local_zero_y, milieu_x, milieu_y, new_x, new_y;
    this->get_piece_dim(&hauteur_piece,&largeur_piece,&local_zero_x,&local_zero_y);

    if(largeur_piece % 2 == 0)
        largeur_piece--;
    if(hauteur_piece%2 == 0)
        hauteur_piece--;

    milieu_x = (local_zero_x + (largeur_piece/2));
    milieu_y = (local_zero_y + (hauteur_piece/2));

    //définition de la nouvelle position des boxies
    for (size_t i = 0; i < this->boxies.size(); i++) { 
        new_x = milieu_x + (milieu_y - this->boxies.at(i).get_y());
        new_y = milieu_y - (milieu_x - this->boxies.at(i).get_x());
        this->boxies.at(i).set_temp_pos(new_x, new_y);
    }

    //vérification si nouvelle position possible
    if(isRotaValid(largeur, hauteur, grille))
    {
        for (size_t i = 0; i < this->boxies.size(); i++) { 
                this->boxies.at(i).confirm_tmp_pos();
        }
    }


  }
}

bool Piece::isRotaValid(int largeur, int hauteur, std::vector<Boxies> grille)
{

    for (size_t i = 0; i < this->boxies.size(); i++) {

        //check murs
        if(this->boxies[i].get_tx() < 0  || this->boxies[i].get_tx() >= largeur || this->boxies[i].get_ty() >= hauteur) {
            return false;
        }

        //check places dispo
        for (size_t j = 0; j < grille.size(); j++) {
            // on est sur la même ligne qu'une autre pièce
            if(this->boxies[i].get_ty() == grille[j].get_y()) {
                // y a une pièce au même endroit
                if(this->boxies[i].get_tx() == grille[j].get_x()) {
                return false;
                }
            }
        }
    }
    return true;
    

}