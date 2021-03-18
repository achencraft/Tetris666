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

std::string Boxies::get_sprite() {
  return sprite;
}

void Boxies::chuter()
{
    y = y - 1;
}
