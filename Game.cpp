#include "Game.h"

void Game::init()
{
    
}

void Game::keyboard()
{

}

void Game::draw()
{

}

void Game::loop()
{

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