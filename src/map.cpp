#include "map.hpp"

std::vector<Object> Map::get_objects() { return this->objs; }

void Map::set_objects(std::vector<Object> objs) {
    this->objs.clear();
    for (int i = 0; i < objs.size(); i++) add_object(objs[i]);
}

void Map::add_object(Object obj) { this->objs.push_back(obj); }

void Map::draw(sf::RenderWindow* screen) {
    for (int i = 0; i < this->objs.size(); i++)
        (*screen).draw(this->objs[i].get_share());
}