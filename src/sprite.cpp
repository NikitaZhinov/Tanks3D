#include "Raycast/raycast.hpp"

Sprite::Sprite(Point2 pos, int width, int height, sf::Texture *texture) :
    Object({pos}) {
    this->width = width;
    this->height = height;
}
