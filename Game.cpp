#include "Game.h"


void Game::init(int largeur_grille, int hauteur_grille)
{
  win = new WindowSurface("Tetris666",800,1000);
  win->ajouter_sprite("fond",Sprite({0,0,299,499}));
  win->ajouter_sprite("boxi",Sprite({299,0,40,40}));
  creer_pieces();
  score = 0;
  yatilUnePieceDansLavion = false;
  ZePartiiii = false;
  yatilUnePieceEnTrainDeTomber = false;

  this->hauteur_grille = hauteur_grille;
  this->largeur_grille = largeur_grille;
}

Piece Game::nouvelle_piece()
{
    int piece_id = rand() % 7; //entre 0 et 6 inclus  
    Piece p = Piece(this->liste_pieces.at(piece_id),0,largeur_grille);
    return p;
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
  

  // récupération sprite fond
  SDL_Rect *srcFond = win->sprites.at("fond").get();
  for(i = largeur-200-srcFond->w; i > (-1)*srcFond->w; i-=srcFond->w)
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

  /*SDL_Color color = { 255, 255, 255 };
  SDL_Surface * surface = TTF_RenderText_Solid(win->font,"Tetris666", color);
  SDL_Texture * texture = SDL_CreateTextureFromSurface(win->renderer, surface);
  SDL_Rect dstrect = { 0, 0, 10, 10 };
  SDL_RenderCopy(win->renderer, texture, NULL, &dstrect);
  */


}

void Game::draw_boxi(int x, int y, int taille)
{
    SDL_Rect dest = { taille*x, taille*y, taille, taille };
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
            if(!JustSpawned)
              this->piece_courante.rotation(largeur_grille, hauteur_grille, this->grille);
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
      Piece p = this->nouvelle_piece();
      this->piece_courante = p;
      // std::cout << "Création d'une pièce\n";
      this->yatilUnePieceDansLavion = false;
      this->yatilUnePieceEnTrainDeTomber = true;
      this->JustSpawned = true;
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