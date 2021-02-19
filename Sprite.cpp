#include "Sprite.h"

Sprite::Sprite(){}

Sprite::Sprite(SDL_Rect src) :
    src(src)
{}

SDL_Rect* Sprite::get()
{
    return &src;
}