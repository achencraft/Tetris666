#include "Game.h"


void Game::init()
{
    win = new WindowSurface("Tetris666",400,500);
    win->ajouter_sprite("fond",Sprite({0,0,299,499}));
}

void Game::keyboard(const Uint8* keys)
{

}

void Game::draw()
{
    // remplit le fond 
	SDL_Rect dest = { 0,0,0,0 };
    // copie depuis la planche de sprite vers la fenetre
    SDL_BlitSurface(win->plancheSprites, win->sprites.at("fond").get(), win->win_surf, &dest);


}

void Game::loop()
{

    bool quit = false;

	while(!quit)
    {
        draw();
		// affiche la surface
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