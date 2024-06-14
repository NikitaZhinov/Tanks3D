#pragma once

#include "Raycast/raycast.hpp"

class Sprite : public Object {
public:
    Sprite(Point2 pos, int width, int height, sf::Texture *texture);

private:
    int width = 0, height = 0;
};
