#pragma once

#include "Raycast/raycast.hpp"

class Sprite {
public:
    Sprite(int width, int height, sf::Texture *texture);

private:
    int width = 0, height = 0;
    sf::Texture *texture = nullptr;
};
