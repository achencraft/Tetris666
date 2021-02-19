#include "WindowSurface.h";

WindowSurface::WindowSurface() {}
WindowSurface::WindowSurface(std::string name, int hauteur, int largeur) :
    name(name), hauteur(hauteur), largeur(largeur)
{
    window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, hauteur, largeur, SDL_WINDOW_SHOWN);
    win_surf = SDL_GetWindowSurface(window);
}

void WindowSurface::get_dimension(int *hauteur, int *largeur)
{
    SDL_GetWindowSize(window,largeur,hauteur);
}