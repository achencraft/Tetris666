#include "WindowSurface.h"


WindowSurface::WindowSurface() {}
WindowSurface::WindowSurface(std::string name, int hauteur, int largeur) :
    name(name), hauteur(hauteur), largeur(largeur)
{
    window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, hauteur, largeur, SDL_WINDOW_SHOWN);
    if(!window)
    {
        std::cout << "erreur create window\n";
        exit(1);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(!renderer)
    {
        std::cout << "erreur create renderer\n";
        exit(1);
    }


    plancheSprites = SDL_LoadBMP("./sprites.bmp");
    if(!plancheSprites)
    {
        std::cout << "erreur loadbmp\n";
        exit(1);
    }

    pTexture = SDL_CreateTextureFromSurface(renderer,plancheSprites);
    if(!pTexture)
    {
        std::cout << "erreur texture\n";
        exit(1);
    }

    font = TTF_OpenFont("arial.ttf", 25);
}

void WindowSurface::get_dimension(int *hauteur, int *largeur)
{
    SDL_GetWindowSize(window,largeur,hauteur);
}

void WindowSurface::ajouter_sprite(std::string key, Sprite sprite)
{
    sprites.insert(std::make_pair(key, sprite));
}
