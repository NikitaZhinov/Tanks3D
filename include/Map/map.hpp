#pragma once

#include "Raycast/raycast.hpp"

class Map {
public:
    std::vector<Object> get_objects();

    void set_objects(const std::vector<Object> &objs);
    void add_object(const Object &obj);

    void draw(sf::RenderWindow *screen);

private:
    std::vector<Object> objs;
};
