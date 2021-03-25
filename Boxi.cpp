#include "Boxi.h"

Boxi::Boxi() {}

Boxi::Boxi(std::string s, int xx, int yy) {
    sprite = s;
    x = xx;
    y = yy;
}

int Boxi::get_x() {
  return x;
}

int Boxi::get_y() {
  return y;
}


int Boxi::get_tx() {
  return tmp_x;
}

int Boxi::get_ty() {
  return tmp_y;
}

void Boxi::confirm_tmp_pos() 
{
    x = tmp_x;
    y = tmp_y;
}

void Boxi::set_temp_pos(int xx, int yy)
{
    tmp_x = xx;
    tmp_y = yy;
}

std::string Boxi::get_sprite() {
  return sprite;
}

void Boxi::chuter()
{
    y = y + 1;
}

void Boxi::gauche()
{
  x = x - 1;
  //std::cout << "x = " << this->x << "\n";
}

void Boxi::droite()
{
  x = x + 1;
  //std::cout << "x = " << this->x << "\n";
}

void Boxi::set_pos_x(int xx)
{
    x = x + xx;
}