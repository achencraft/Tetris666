#ifndef _WINDOW_SURFACE_
#define _WINDOW_SURFACE_

#include <SDL.h>
#include <map>
#include <string>
#include "Sprite.h"



class WindowSurface
{
    public:

        std::map<std::string, Sprite> sprites;
        SDL_Surface* win_surf;
        SDL_Surface* plancheSprites;
        SDL_Window* window;
        std::string name;
        int hauteur;
        int largeur;


        WindowSurface();
        WindowSurface(std::string name, int hauteur, int largeur);
        void ajouter_sprite(std::string key, Sprite sprite);
        void get_dimension(int *hauteur, int *largeur);
};


#endif