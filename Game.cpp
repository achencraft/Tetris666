#include "Game.h"


void Game::init()
{
  win = new WindowSurface("Tetris666",400,500);
  win->ajouter_sprite("fond",Sprite({0,0,299,499}));
  win->ajouter_sprite("boxi",Sprite({299,0,40,40}));
  piece_courante = nullptr;
}

void Game::keyboard(const Uint8* keys)
{
  // if (keys[SDL_SCANCODE_RETURN])
  //   std::cout<< "<RETURN> is pressed."<< std::endl;
}

void Game::draw()
{
  // récupération sprite fond
  SDL_Rect dest = { 299,0,0,0 };
  SDL_Rect *srcFond = win->sprites.at("fond").get();
  SDL_BlitSurface(win->plancheSprites, srcFond, win->win_surf, &dest);

  //placer les boxies
  for (size_t i = 0; i < this->grille.size(); i++) {
    SDL_Rect destBoxie = { int(this->grille[i].get_x()), int(this->grille[i].get_y()), 0, 0 };
    SDL_Rect *srcBoxie= win->sprites.at(this->grille[i].get_sprite()).get();
    SDL_BlitSurface(win->plancheSprites, srcBoxie, win->win_surf, &destBoxie);
  }

  if(piece_courante != nullptr) {
    std::vector<Boxies> piece = piece_courante->get_boxies();
    for (size_t i = 0; i < piece.size(); i++) {
      SDL_Rect destBoxie = { int(piece[i].get_x()), int(piece[i].get_y()), 0, 0 };
      SDL_Rect *srcBoxie= win->sprites.at(piece[i].get_sprite()).get();
      SDL_BlitSurface(win->plancheSprites, srcBoxie, win->win_surf, &destBoxie);
    }
  }

}

void Game::loop()
{

  bool quit = false;
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
            nouvelle_piece = true;
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
      this->piece_courante = &p;
      // this->grille.insert(this->grille.end(),p);
        //la liste des boxies de la piece);
    }

    //actualise la position des boxies


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
