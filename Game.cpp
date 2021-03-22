#include "Game.h"


void Game::init()
{
  win = new WindowSurface("Tetris666",800,1000);
  win->ajouter_sprite("fond",Sprite({0,0,299,499}));
  win->ajouter_sprite("boxi",Sprite({299,0,40,40}));
  yatilUnePieceDansLavion = false;
}

void Game::keyboard(const Uint8* keys)
{
  // if (keys[SDL_SCANCODE_RETURN])
  //   std::cout<< "<RETURN> is pressed."<< std::endl;
}

void Game::draw()
{
  int hauteur, largeur, i, j;
  win->get_dimension(&hauteur,&largeur);

  // récupération sprite fond
  SDL_Rect *srcFond = win->sprites.at("fond").get();
  for(i = largeur-200-srcFond->w; i > (-1)*srcFond->w; i-=srcFond->w)
  {
    for(j = 0; j < hauteur; j+=srcFond->h)
    {
        SDL_Rect dest = { i,j,0,0 };  
        SDL_BlitSurface(win->plancheSprites, srcFond, win->win_surf, &dest);
    }  
  }
  
  

  //placer les boxies
  
  
  for (size_t i = 0; i < this->grille.size(); i++) {    
    Boxies boxi = this->grille[i];
    SDL_Rect *srcBoxie= win->sprites.at(boxi.get_sprite()).get();

    SDL_Rect destBoxie = { srcBoxie->w*int(boxi.get_x()), srcBoxie->h*int(boxi.get_y()), 0, 0 };
    SDL_BlitSurface(win->plancheSprites, srcBoxie, win->win_surf, &destBoxie);
  }

  if(yatilUnePieceDansLavion) {
    std::vector<Boxies> *piece = piece_courante.get_boxies();
    for (size_t i = 0; i < piece->size(); i++) {
      // int x = int(piece->at(i).get_x());
      // int y = int(piece->at(i).get_y());
      // std::cout << "x = " << x << ", y = " << y << "\n";
      
      Boxies boxi = piece->at(i);
      SDL_Rect *srcBoxie= win->sprites.at("boxi").get();      

      SDL_Rect destBoxie = { int(srcBoxie->w*piece->at(i).get_x()), int(srcBoxie->h*piece->at(i).get_y()), 0, 0 };
      
      SDL_BlitSurface(win->plancheSprites, srcBoxie, win->win_surf, &destBoxie);
    }
  }

}

void Game::loop()
{

  bool quit = false;
  int w, h;
  this->win->get_dimension(&h,&w);


  while(!quit)
  {

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
        case SDL_KEYDOWN:
          switch (event.key.keysym.sym)
          {
          case SDLK_RETURN:
            printf("start\n");
            this->nouvelle_piece = true;
            this->yatilUnePieceDansLavion = true;
            break;
          case SDLK_LEFT:
            this->piece_courante.gauche(w);
            break;
          case SDLK_RIGHT:
            this->piece_courante.droite(w);
            break;
          default:
            break;
          }

        break;
        default: break;
      }
    }
    const Uint8* state = SDL_GetKeyboardState(NULL);
		keyboard(state);
    quit |= (state[SDL_SCANCODE_ESCAPE]!=0);

    //nouvelle pièce
    if(this->nouvelle_piece)
    {
      Piece p = Piece();
      this->piece_courante = p;
      std::cout << "nouvelle pièce!!!\n";
      this->nouvelle_piece = false;
    }

    //actualise la position des boxies
    this->piece_courante.chuter(h);

    // gestion des bords
    // this->piece_courante->isPieceOnTheGrille(this->grille);

    //génère l'affichage
    this->draw();

    // affiche la surface
    SDL_UpdateWindowSurface(win->window);

 
  }

  SDL_Quit();
}

int main(int argc, char** argv)
{
  if(SDL_Init(SDL_INIT_VIDEO) != 0)
  {
    return 1;
  }


  Game g;
  g.init();
  g.loop();
}
