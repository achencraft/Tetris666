#ifndef _SPRITE_H_
#define _SPRITE_H_

#include <SDL.h>


class Sprite
{ 

private:
    SDL_Rect src;
public:
    Sprite();
    Sprite(SDL_Rect src);
    SDL_Rect* get();
};
#endif