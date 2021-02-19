#ifndef _BOXIES_H_
#define _BOXIES_H_

#include <SDL.h>

class Boxies {
    public:
        // constructeur
        Boxies();
        Boxies(SDL_Rect s, int x, int y);

    protected:
        SDL_Rect src;
        int x;
        int y;
}


#endif