#ifndef _BOXI_H_
#define _BOXI_H_

#include <SDL.h>
#include <string>
#include <iostream>

class Boxi {
    public:
        // constructeur
        Boxi();
        Boxi(std::string s, int x, int y, SDL_Color color);
        Boxi(std::string s, int x, int y, SDL_Color color, bool final);

        // destructeur
        // ~Boxi();

        //méthodes
        int get_x();
        int get_y();
        int get_tx();
        int get_ty();
        bool get_final();
        void confirm_tmp_pos();
        void set_temp_pos(int x, int y);
        void set_pos_x(int x);
        void reset(int xx, int min_x, int min_y);
        SDL_Color get_color();
        // getter
        std::string get_sprite();
        // déplacement
        void chuter(); //diminue le y de 1
        void up();
        void gauche();
        void droite();

    protected:
        std::string sprite;
        int x;
        int y;
        int tmp_x;
        int tmp_y;
        bool final;

    private:
        SDL_Color color;
};


#endif
