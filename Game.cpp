#include "Game.h"


void Game::init(int largeur_grille, int hauteur_grille)
{
  win = new WindowSurface("Tetris666",1400,1000);
  win->ajouter_sprite("fond",Sprite({0,0,10,10}));
  win->ajouter_sprite("deco",Sprite({0,0,1056,287}));
  win->ajouter_sprite("pattern",Sprite({0,288,320,423}));
  win->ajouter_sprite("boxi",Sprite({299,0,40,40}));
  creer_pieces();
  score = 0;
  yatilUnePieceDansLavion = false;
  ZePartiiii = false;
  yatilUnePieceEnTrainDeTomber = false;
  yatilUnePieceSauvee = false;
  left_marge = 200;

  this->hauteur_grille = hauteur_grille;
  this->largeur_grille = largeur_grille;
}

Piece Game::nouvelle_piece()
{
    int piece_id = rand() % 7; //entre 0 et 6 inclus
    Piece p = Piece(this->liste_pieces.at(piece_id),0,largeur_grille);
    return p;
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

  // on regarde chaque ligne
  for (size_t i = 0; i < this->hauteur_grille; i++) {
    // si y a autant de boxi que y a de place
    if(fautTilDetruireLeMur[i] == this->largeur_grille) {
      this->score += 100;
      std::cout << "Score = " << this->score << "\n";
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



void Game::draw(int largeur, int hauteur)
{
  int i, j, taille_boxi;
  taille_boxi = hauteur/hauteur_grille;

  //on efface la fenêtre
  SDL_SetRenderDrawColor(win->renderer,0,0,0,255);
  SDL_RenderClear(win->renderer);



  // Fond sombre
  SDL_Rect *srcBackground = win->sprites.at("fond").get();
  for(i = 0; i < 1400; i+=10)
  {
    for(j = 0; j < 1000 ; j+=10 ) {
      SDL_Rect dest = {i,j,srcBackground->w,srcBackground->h};
      SDL_RenderCopy(win->renderer,win->pTexture,srcBackground,&dest);
    }
  }
  // Déco blocs
  SDL_Rect *srcTetris = win->sprites.at("deco").get();
  for(i = 0; i < 1400; i+=1056)
  {
    // for(j = 0; j < 1000 ; j+=300 ) {
      int j = 1000-287;
      SDL_Rect dest = {i,j,srcTetris->w,srcTetris->h};
      SDL_RenderCopy(win->renderer,win->pTexture,srcTetris,&dest);
    // }
  }
  // Bordure fenêtre de jeu
  // SDL_SetRenderDrawColor(win->renderer,209,141,127,255);
  // SDL_Rect rightcol = { largeur-200, 0, 200, hauteur};
  // SDL_RenderFillRect(win->renderer,&rightcol);
  // récupération sprite fond
  SDL_Rect *srcFond = win->sprites.at("pattern").get();
  int depart = (largeur - 300)/2;
  // std::cout << depart << "\n";
  for(i = depart; i < depart+this->largeur_grille; i+=srcFond->w)
  {
    for(j = 0; j < hauteur; j+=srcFond->h)
    {
        SDL_Rect dest = {i,j,srcFond->w,srcFond->h};
        SDL_RenderCopy(win->renderer,win->pTexture,srcFond,&dest);
    }
  }

  //placer les boxies placés
  for (size_t i = 0; i < this->grille.size(); i++) {
    Boxi boxi = this->grille[i];
    draw_boxi(boxi.get_x(), boxi.get_y(), taille_boxi);
  }

  //placer la pièce qui tombe
  if(yatilUnePieceEnTrainDeTomber) {
    std::vector<Boxi> *piece = piece_courante.get_boxies();
    for (size_t i = 0; i < piece->size(); i++) {
      Boxi boxi = piece->at(i);
      draw_boxi(piece->at(i).get_x(), piece->at(i).get_y(), taille_boxi);
    }
  }

  //placer colonne droite
  SDL_SetRenderDrawColor(win->renderer,209,141,127,255);
  SDL_Rect rightcol = { largeur-200, 0, 200, hauteur};
  SDL_RenderFillRect(win->renderer,&rightcol);

  //Affichage titre
  SDL_Color color = { 255, 255, 255 };
  SDL_Surface *surface = TTF_RenderText_Solid(win->font,"Tetris666", color);
  SDL_Texture *texture = SDL_CreateTextureFromSurface(win->renderer, surface);
  SDL_Rect dstrect = { largeur-190, 10, 180, 100 };
  SDL_RenderCopy(win->renderer, texture, NULL, &dstrect);


  //Affichage score
  surface = TTF_RenderText_Solid(win->font,"score :", color);
  texture = SDL_CreateTextureFromSurface(win->renderer, surface);
  dstrect = { largeur-190, 150, 50, 40 };
  SDL_RenderCopy(win->renderer, texture, NULL, &dstrect);
  std::string s = std::to_string(score);
  surface = TTF_RenderText_Solid(win->font,s.c_str(), color);
  texture = SDL_CreateTextureFromSurface(win->renderer, surface);
  dstrect = { largeur-190, 200, 60, 50 };
  SDL_RenderCopy(win->renderer, texture, NULL, &dstrect);

  //Affichage pièce suivante
  surface = TTF_RenderText_Solid(win->font,"piece suivante :", color);
  texture = SDL_CreateTextureFromSurface(win->renderer, surface);
  dstrect = { largeur-190, 300, 150, 40 };
  SDL_RenderCopy(win->renderer, texture, NULL, &dstrect);
  SDL_SetRenderDrawColor(win->renderer,0,0,0,255);
  rightcol = { largeur-190, 350, 180, 180};
  SDL_RenderFillRect(win->renderer,&rightcol);

  //placer la prochaine pièce
  std::vector<Boxi> *piece = piece_suivante.get_boxies();
  for (size_t i = 0; i < piece->size(); i++) {
    Boxi boxi = piece->at(i);
    draw_boxi_right(largeur-210, 410,piece->at(i).get_x(), piece->at(i).get_y(), 15);
  }


  //Affichage pièce sauvegardée
  surface = TTF_RenderText_Solid(win->font,"piece sauvegarde :", color);
  texture = SDL_CreateTextureFromSurface(win->renderer, surface);
  dstrect = { largeur-190, 600, 150, 40 };
  SDL_RenderCopy(win->renderer, texture, NULL, &dstrect);
  SDL_SetRenderDrawColor(win->renderer,0,0,0,255);
  rightcol = { largeur-190, 650, 180, 180};
  SDL_RenderFillRect(win->renderer,&rightcol);

  //placer la piece sauvegardee
  if(this->yatilUnePieceSauvee)
  {
    int hauteur_piece,largeur_piece,min_x,min_y;
    std::vector<Boxi> *piece = piece_sauvegarde.get_boxies();
    piece_sauvegarde.get_piece_dim(&hauteur_piece,&largeur_piece,&min_x,&min_y);

    for (size_t i = 0; i < piece->size(); i++) {
      Boxi boxi = piece->at(i);
      draw_boxi_right(largeur-210, 710,piece->at(i).get_x()-min_x+6, piece->at(i).get_y()-min_y+1, 15);
    }
  }


}

void Game::draw_boxi(int x, int y, int taille)
{
    SDL_Rect dest = { left_marge + taille*x, taille*y, taille, taille };
    SDL_SetRenderDrawColor(win->renderer,209,141,127,255);
    SDL_RenderFillRect(win->renderer,&dest);
    SDL_SetRenderDrawColor(win->renderer,209,0,127,255);
    SDL_RenderDrawRect(win->renderer,&dest);
}

void Game::draw_boxi_right(int sx, int sy, int x, int y, int taille)
{
    SDL_Rect dest = { sx+(taille*x), sy+(taille*y), taille, taille };
    SDL_SetRenderDrawColor(win->renderer,209,141,127,255);
    SDL_RenderFillRect(win->renderer,&dest);
    SDL_SetRenderDrawColor(win->renderer,209,0,127,255);
    SDL_RenderDrawRect(win->renderer,&dest);
}

void Game::loop()
{

  bool quit = false;
  int w, h;
  this->win->get_dimension(&h,&w);

  //gestion du temps
  unsigned int lastTime = 0, currentTime, delai_chute = 1000;

  while(!quit)
  {
    currentTime = SDL_GetTicks();

    SDL_Event event;
    while (!quit && SDL_PollEvent(&event))
    {
      switch (event.type)
      {
        case SDL_QUIT:
        quit = true;
        break;
        case SDL_MOUSEBUTTONDOWN:
        printf("mouse click %d\n", event.button.button);
        break;
        case SDL_KEYUP:
          switch (event.key.keysym.sym)
          {
          case SDLK_RETURN:
            if(!this->ZePartiiii) {
              // std::cout << "Début de la partie\n";
              this->yatilUnePieceDansLavion = true;
              this->ZePartiiii = true;
              this->JustSpawned = true;
              this->tour = 0;
            }
            break;
          case SDLK_LEFT:
            if(this->yatilUnePieceEnTrainDeTomber)
              this->piece_courante.gauche(largeur_grille, this->grille);
            break;
          case SDLK_RIGHT:
            if(this->yatilUnePieceEnTrainDeTomber)
              this->piece_courante.droite(largeur_grille, this->grille);
            break;
          case SDLK_DOWN:
            delai_chute = 1000;
            break;
          case SDLK_SPACE:
            if(!JustSpawned && yatilUnePieceEnTrainDeTomber)
              this->piece_courante.rotation(largeur_grille, hauteur_grille, this->grille);
            break;
          case SDLK_RSHIFT:
            if(!JustSpawned && yatilUnePieceEnTrainDeTomber)
              this->sauvegarde_piece();
              this->piece_courante.remonter(largeur_grille, this->grille);
            break;
          default:
            break;
          }

        break;
        case SDL_KEYDOWN:
          switch (event.key.keysym.sym)
          {
          case SDLK_DOWN:
            delai_chute = 50;
            break;
          default:
            break;
          }

        break;
        default: break;
      }
    }
    const Uint8* state = SDL_GetKeyboardState(NULL);
    quit |= (state[SDL_SCANCODE_ESCAPE]!=0);

    //nouvelle pièce si la dernière pièce a été posée
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

    if (currentTime > lastTime + delai_chute) {
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
          quit = this->verificationFinJeu();
        }

        lastTime = currentTime;
    }

    // gestion des bords
    // this->piece_courante->isPieceOnTheGrille(this->grille);

    //génère l'affichage
    this->draw(w,h);

    // affiche la surface
    SDL_RenderPresent(win->renderer);
    //SDL_UpdateWindowSurface(win->window);

  }

  SDL_Quit();
}

int main(int argc, char** argv)
{
  if(SDL_Init(SDL_INIT_VIDEO) != 0 || TTF_Init() != 0)
  {
    return 1;
  }


  Game g;
  g.init(15,25);
  g.loop();
}


void Game::creer_pieces()
{
    std::vector<Boxi> boxi_tab;

    //Pièce Carrée 0
    boxi_tab.insert(boxi_tab.end(),Boxi("boxi",0,0));
    boxi_tab.insert(boxi_tab.end(),Boxi("boxi",0,1));
    boxi_tab.insert(boxi_tab.end(),Boxi("boxi",1,0));
    boxi_tab.insert(boxi_tab.end(),Boxi("boxi",1,1));
    liste_pieces.insert(liste_pieces.end(),boxi_tab);
    boxi_tab.clear();

    //Pièce L 1
    boxi_tab.insert(boxi_tab.end(),Boxi("boxi",0,0));
    boxi_tab.insert(boxi_tab.end(),Boxi("boxi",1,0));
    boxi_tab.insert(boxi_tab.end(),Boxi("boxi",2,0));
    boxi_tab.insert(boxi_tab.end(),Boxi("boxi",2,1));
    liste_pieces.insert(liste_pieces.end(),boxi_tab);
    boxi_tab.clear();

    //Pièce L inversé 2
    boxi_tab.insert(boxi_tab.end(),Boxi("boxi",0,1));
    boxi_tab.insert(boxi_tab.end(),Boxi("boxi",1,1));
    boxi_tab.insert(boxi_tab.end(),Boxi("boxi",2,1));
    boxi_tab.insert(boxi_tab.end(),Boxi("boxi",2,0));
    liste_pieces.insert(liste_pieces.end(),boxi_tab);
    boxi_tab.clear();

    //Pièce S 3
    boxi_tab.insert(boxi_tab.end(),Boxi("boxi",0,1));
    boxi_tab.insert(boxi_tab.end(),Boxi("boxi",0,2));
    boxi_tab.insert(boxi_tab.end(),Boxi("boxi",1,0));
    boxi_tab.insert(boxi_tab.end(),Boxi("boxi",1,1));
    liste_pieces.insert(liste_pieces.end(),boxi_tab);
    boxi_tab.clear();

    //Pièce Z 4
    boxi_tab.insert(boxi_tab.end(),Boxi("boxi",0,0));
    boxi_tab.insert(boxi_tab.end(),Boxi("boxi",0,1));
    boxi_tab.insert(boxi_tab.end(),Boxi("boxi",1,1));
    boxi_tab.insert(boxi_tab.end(),Boxi("boxi",1,2));
    liste_pieces.insert(liste_pieces.end(),boxi_tab);
    boxi_tab.clear();

    //Pièce I 5
    boxi_tab.insert(boxi_tab.end(),Boxi("boxi",0,0));
    boxi_tab.insert(boxi_tab.end(),Boxi("boxi",0,1));
    boxi_tab.insert(boxi_tab.end(),Boxi("boxi",0,2));
    boxi_tab.insert(boxi_tab.end(),Boxi("boxi",0,3));
    liste_pieces.insert(liste_pieces.end(),boxi_tab);
    boxi_tab.clear();

    //Pièce T 6
    boxi_tab.insert(boxi_tab.end(),Boxi("boxi",0,0));
    boxi_tab.insert(boxi_tab.end(),Boxi("boxi",0,1));
    boxi_tab.insert(boxi_tab.end(),Boxi("boxi",0,2));
    boxi_tab.insert(boxi_tab.end(),Boxi("boxi",1,1));
    liste_pieces.insert(liste_pieces.end(),boxi_tab);
}
