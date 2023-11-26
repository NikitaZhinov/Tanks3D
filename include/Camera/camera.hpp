#pragma once

#include <common.hpp>
#include <map.hpp>
#include <player.hpp>

class Camera {
   public:
    Camera(int number_of_lines, Map* map, Player* player,
           sf::RenderWindow* screen);

    void set_number_of_lines(int n);
    void set_map(Map* map);
    void set_player(Player* player);
    void set_viewing_angle(double n);

    int get_number_of_lines();
    std::vector<Object> get_map();
    Player* get_player();

    void draw();

   private:
    double viewing_angle = M_PI / 1.5, length = 300;
    int number_of_lines;
    sf::RectangleShape line;
    double d_, deviation, dx, k, b;
    std::vector<Object> objs;
    sf::RenderWindow* screen;
    Player* player;
    double angle_player_line;
    Point2 points_player[2];
    double floor_height = 1;

    double get_distance(Object* obj);
    double get_distance_to_obj(Object* obj);
    void sort_objs();
    void sort_objs(int start, int end);
    int sort_objs_(int left, int right);
};