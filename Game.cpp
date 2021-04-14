#include "Game.h"

Game::Game(){}

void Game::init(int largeur_grille, int hauteur_grille, int player)
{
  creer_pieces();
  score = 0;
  yatilUnePieceDansLavion = false;
  ZePartiiii = false;
  yatilUnePieceEnTrainDeTomber = false;
  yatilUnePieceSauvee = false;
  quiSuisJe = player;


  this->hauteur_grille = hauteur_grille;
  this->largeur_grille = largeur_grille;

}

Piece Game::nouvelle_piece()
{
    struct timeval timer;
    gettimeofday(&timer, NULL);
    srand(timer.tv_usec);
    int piece_id = rand() % 7; //entre 0 et 6 inclus
    Piece p = Piece(this->liste_pieces.at(piece_id),largeur_grille);
    return p;
}

void Game::check_nouvelle_piece()
{
  if(this->yatilUnePieceDansLavion)
    {
      if(this->tour == 0)
      {
        this->piece_courante = this->nouvelle_piece();
        this->piece_suivante = this->nouvelle_piece();
      }
      else
      {
        this->piece_courante = this->piece_suivante;
        this->piece_suivante = this->nouvelle_piece();
      }
      // std::cout << "Création d'une pièce\n";
      this->yatilUnePieceDansLavion = false;
      this->yatilUnePieceEnTrainDeTomber = true;
      this->JustSpawned = true;
      tour = tour + 1;
    }
}

bool Game::actualiser_chute()
{
  JustSpawned = false;
  //actualise la position des boxies
  bool puisJeTomber = this->piece_courante.chuter(hauteur_grille,this->grille);
  // si on a pas le droit de tomber
  if(!puisJeTomber) {
    // on ajoute la pièce courante au mur
    this->addPieceToTheGrille();
    // on dit que y a plus de pièce du coup
    this->yatilUnePieceDansLavion = true;
    this->yatilUnePieceEnTrainDeTomber = false;
    this->verificationLignes();
    return this->verificationFinJeu();
  }
  return false;
}

void Game::debuter_partie()
{
  if(!this->ZePartiiii) {
      // std::cout << "Début de la partie\n";
      this->yatilUnePieceDansLavion = true;
      this->ZePartiiii = true;
      this->JustSpawned = true;
      this->tour = 0;
    }
}

void Game::droite()
{
  if(this->yatilUnePieceEnTrainDeTomber)
    this->piece_courante.droite(this->largeur_grille, this->grille);
}

void Game::gauche()
{
  if(this->yatilUnePieceEnTrainDeTomber)
    this->piece_courante.gauche(this->largeur_grille, this->grille);
}

void Game::rotation()
{
  if(!this->JustSpawned && this->yatilUnePieceEnTrainDeTomber)
    this->piece_courante.rotation(this->largeur_grille, this->hauteur_grille, this->grille);
}

void Game::sauvegarde()
{
  if(!this->JustSpawned && this->yatilUnePieceEnTrainDeTomber)
    this->sauvegarde_piece();
    this->piece_courante.remonter(this->largeur_grille, this->grille);
}

void Game::sauvegarde_piece()
{
    int hauteur_piece,largeur_piece,min_x,min_y;
    if(!this->yatilUnePieceSauvee)
    {
      this->piece_sauvegarde = this->piece_courante;
      this->yatilUnePieceDansLavion = true;
      this->yatilUnePieceEnTrainDeTomber = false;
      this->yatilUnePieceSauvee = true;
    }
    else
    {
      Piece tmp = this->piece_courante;
      this->piece_courante = this->piece_sauvegarde;
      this->piece_sauvegarde = tmp;
    }




}

void Game::addPieceToTheGrille() {
  this->piece_courante.poser();
  std::vector<Boxi> *piece = this->piece_courante.get_boxies();
  for (size_t i = 0; i < piece->size(); i++) {
    this->grille.insert(this->grille.end(),piece->at(i));
  }
}

void Game::verificationLignes() {
  // tableau qui pour chaque ligne dit combien y a de boxies
  int fautTilDetruireLeMur[this->hauteur_grille];
  for (size_t i = 0; i < this->hauteur_grille; i++) {
    fautTilDetruireLeMur[i] = 0;
  }
  // on remplit le tableau du coup
  for (size_t i = 0; i < this->grille.size(); i++) {
    Boxi boxi = this->grille[i];
    fautTilDetruireLeMur[boxi.get_y()]++;
  }

  int counter = 0;
  // on regarde chaque ligne
  for (size_t i = 0; i < this->hauteur_grille; i++) {
    // si y a autant de boxi que y a de place
    if(fautTilDetruireLeMur[i] == this->largeur_grille) {
      counter += 1;

      // ON DETRUIT
      int tailleMur = this->grille.size();
      int idx = 0;
      while(idx < tailleMur) {
        if(this->grille[idx].get_y() == i) {
          this->grille.erase(this->grille.begin()+idx);
          tailleMur = this->grille.size();
        }
        else {
          idx++;
        }
      }
      // ET ON DESCEND TOUT LE RESTE DU MUR!!!
      for (size_t b = 0; b < this->grille.size(); b++) {
        if(this->grille[b].get_y() < i) {
          this->grille[b].chuter();
        }
      }
    }
  }

  this->score += (counter*100)*counter;
  std::cout << "Score = " << this->score << "\n";
}

bool Game::verificationFinJeu() {
  // on parcourt les picèes en partant de la fin
  // on trouvera plus vite si la dernière posée est perdante ou pas
  // à terme on pourrait juste checker le nombre max de bloc que peut faire une pièce
  int i = this->grille.size()-1;
  while(i >= 0) {
    if(this->grille[i].get_y() == 0) {
      return true;
    }
    i--;
  }
  return false;
}


std::vector<Boxi> Game::get_grille()
{
  return this->grille;
}

Piece Game::get_piece_courante()
{
  return this->piece_courante;
}

Piece Game::get_piece_suivante()
{
  return this->piece_suivante;
}

Piece Game::get_piece_sauvegarde()
{
  return this->piece_sauvegarde;
}

int Game::get_score()
{
  return this->score;
}

bool Game::get_yatilUnePieceEnTrainDeTomber()
{
  return this->yatilUnePieceEnTrainDeTomber;
}

bool Game::get_yatilUnePieceSauvee()
{
  return this->yatilUnePieceSauvee;
}

int Game::getPlayer() {
  return this->quiSuisJe;
}

void Game::creer_pieces()
{
    std::vector<Boxi> boxi_tab;

    //Pièce Carrée 0
    SDL_Color color = {169,59,58,255};
    boxi_tab.insert(boxi_tab.end(),Boxi("boxi",0,0,color));
    boxi_tab.insert(boxi_tab.end(),Boxi("boxi",0,1,color));
    boxi_tab.insert(boxi_tab.end(),Boxi("boxi",1,0,color));
    boxi_tab.insert(boxi_tab.end(),Boxi("boxi",1,1,color));
    liste_pieces.insert(liste_pieces.end(),boxi_tab);
    boxi_tab.clear();

    //Pièce L 1
    color = {244,126,28,255};
    boxi_tab.insert(boxi_tab.end(),Boxi("boxi",0,0,color));
    boxi_tab.insert(boxi_tab.end(),Boxi("boxi",1,0,color));
    boxi_tab.insert(boxi_tab.end(),Boxi("boxi",2,0,color));
    boxi_tab.insert(boxi_tab.end(),Boxi("boxi",2,1,color));
    liste_pieces.insert(liste_pieces.end(),boxi_tab);
    boxi_tab.clear();

    //Pièce L inversé 2
    color = {57,70,122,255};
    boxi_tab.insert(boxi_tab.end(),Boxi("boxi",0,1,color));
    boxi_tab.insert(boxi_tab.end(),Boxi("boxi",1,1,color));
    boxi_tab.insert(boxi_tab.end(),Boxi("boxi",2,1,color));
    boxi_tab.insert(boxi_tab.end(),Boxi("boxi",2,0,color));
    liste_pieces.insert(liste_pieces.end(),boxi_tab);
    boxi_tab.clear();

    //Pièce S 3
    color = {142,71,141,255};
    boxi_tab.insert(boxi_tab.end(),Boxi("boxi",0,1,color));
    boxi_tab.insert(boxi_tab.end(),Boxi("boxi",0,2,color));
    boxi_tab.insert(boxi_tab.end(),Boxi("boxi",1,0,color));
    boxi_tab.insert(boxi_tab.end(),Boxi("boxi",1,1,color));
    liste_pieces.insert(liste_pieces.end(),boxi_tab);
    boxi_tab.clear();

    //Pièce Z 4
    color = {95,128,144,255};
    boxi_tab.insert(boxi_tab.end(),Boxi("boxi",0,0,color));
    boxi_tab.insert(boxi_tab.end(),Boxi("boxi",0,1,color));
    boxi_tab.insert(boxi_tab.end(),Boxi("boxi",1,1,color));
    boxi_tab.insert(boxi_tab.end(),Boxi("boxi",1,2,color));
    liste_pieces.insert(liste_pieces.end(),boxi_tab);
    boxi_tab.clear();

    //Pièce I 5
    color = {115,169,57,255};
    boxi_tab.insert(boxi_tab.end(),Boxi("boxi",0,0,color));
    boxi_tab.insert(boxi_tab.end(),Boxi("boxi",0,1,color));
    boxi_tab.insert(boxi_tab.end(),Boxi("boxi",0,2,color));
    boxi_tab.insert(boxi_tab.end(),Boxi("boxi",0,3,color));
    liste_pieces.insert(liste_pieces.end(),boxi_tab);
    boxi_tab.clear();

    //Pièce T 6
    color = {244,180,31,255};
    boxi_tab.insert(boxi_tab.end(),Boxi("boxi",0,0,color));
    boxi_tab.insert(boxi_tab.end(),Boxi("boxi",0,1,color));
    boxi_tab.insert(boxi_tab.end(),Boxi("boxi",0,2,color));
    boxi_tab.insert(boxi_tab.end(),Boxi("boxi",1,1,color));
    liste_pieces.insert(liste_pieces.end(),boxi_tab);
}
