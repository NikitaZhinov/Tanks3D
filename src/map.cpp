#include "Map/map.hpp"

std::vector<Object> Map::get_objects() {
    return this->objs;
}

void Map::set_objects(const std::vector<Object> &objs) {
    this->objs = objs;
}

void Map::add_object(const Object &obj) {
    objs.push_back(obj);
}

void Map::draw(sf::RenderWindow *screen) {
    for (int i = 0; i < objs.size(); i++)
        screen->draw(objs[i].get_share());
}
