#ifndef _BOXIES_H_
#define _BOXIES_H_

#include <SDL.h>
#include <string>
#include <iostream>

class Boxies {
    public:
        // constructeur
        Boxies();
        Boxies(std::string s, int x, int y);

        //méthodes
        int get_x();
        int get_y();
        // getter
        std::string get_sprite();
        // déplacement
        void chuter(); //diminue le y de 1
        void gauche();
        void droite();

    protected:
        std::string sprite;
        int x;
        int y;
};


#endif
