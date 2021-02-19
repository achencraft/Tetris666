#include "Game.h"


void Game::init()
{
  win = new WindowSurface("Tetris666",400,500);
  win->ajouter_sprite("fond",Sprite({0,0,299,499}));
}

void Game::keyboard(const Uint8* keys)
{
  // if (keys[SDL_SCANCODE_RETURN])
  //   std::cout<< "<RETURN> is pressed."<< std::endl;
}

void Game::draw()
{
  // remplit le fond
  SDL_Rect dest = { 0,0,0,0 };
  // SDL_Rect srcFond = {0,0,299,499};
  SDL_Rect *srcFond = win->sprites.at("fond").get();
  // copie depuis la planche de sprite vers la fenetre
  SDL_BlitSurface(win->plancheSprites, srcFond, win->win_surf, &dest);


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
        default: break;
      }
    }
    const Uint8* state = SDL_GetKeyboardState(NULL);
		keyboard(state);
    quit |= (state[SDL_SCANCODE_ESCAPE]!=0);

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
