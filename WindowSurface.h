#ifndef _WINDOW_SURFACE_
#define _WINDOW_SURFACE_

#include <SDL.h>


class WindowSurface
{
    public:

        SDL_Surface* win_surf;
        SQL_Window* window;
        std::string name;
        int hauteur;
        int largeur;


        WindowSurface();
        WindowSurface(std::string name, int hauteur, int largeur);

        void get_dimension(int *hauteur, int *largeur);
};


#endif