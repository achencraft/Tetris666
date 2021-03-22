#include "Boxies.h"

Boxies::Boxies() {}

Boxies::Boxies(std::string s, int xx, int yy) {
    sprite = s;
    x = xx;
    y = yy;
}

int Boxies::get_x() {
  return x;
}

int Boxies::get_y() {
  return y;
}


int Boxies::get_tx() {
  return tmp_x;
}

int Boxies::get_ty() {
  return tmp_y;
}

void Boxies::confirm_tmp_pos() 
{
    x = tmp_x;
    y = tmp_y;
}

void Boxies::set_temp_pos(int xx, int yy)
{
    tmp_x = xx;
    tmp_y = yy;
}

std::string Boxies::get_sprite() {
  return sprite;
}

void Boxies::chuter()
{
    y = y + 1;
}

void Boxies::gauche()
{
  x = x - 1;
  //std::cout << "x = " << this->x << "\n";
}

void Boxies::droite()
{
  x = x + 1;
  //std::cout << "x = " << this->x << "\n";
}
