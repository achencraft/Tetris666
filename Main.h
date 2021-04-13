#ifndef _MAIN_H_
#define _MAIN_H_

#include "WindowSurface.h"
#include "Game.h"
#include "Boxi.h"
#include "Piece.h"
#include <iostream>
#include <vector>
#include <map>
#include <thread>
#include <chrono>
#include <string>
#include <cstring>


class Main
{
    private:
        WindowSurface* win;
        int largeur_grille;
        int hauteur_grille;
        int mode;
        Game game1;
        Game game2;
        int left_marge1;
        int left_marge2;

    public:
        inline Main():
            win(nullptr) {};
        void init(int mode, int largeur_grille, int hauteur_grille, int tailleZoneJeuX, int tailleZoneJeuY);
        void draw(int largeur, int hauteur);
        void draw_boxi(int x, int y, int taille, SDL_Color color, int left_marge);
        void draw_boxi_right(int sx, int sy, int x, int y, int taille,SDL_Color color, int left_marge);
        void loop();

};


#endif
