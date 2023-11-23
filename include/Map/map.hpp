#pragma once

#include <common.hpp>
#include <object.hpp>

class Map {
   public:
    std::vector<Object> get_objects();

    void set_objects(std::vector<Object> objs);
    void add_object(Object obj);

    void draw(sf::RenderWindow* screen);

   private:
    std::vector<Object> objs;
};