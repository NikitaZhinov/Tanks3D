#pragma once

#include "Common/common.hpp"
#include "Map/map.hpp"
#include "Object/object.hpp"
#include "Player/player.hpp"

class Camera {
public:
    Camera(int number_of_lines, Map &map, Player *player, sf::RenderWindow *screen);

    void set_number_of_lines(int n);
    void set_map(Map &map);
    void set_player(Player *player);
    void set_viewing_angle(double n);

    int get_number_of_lines();
    std::vector<Object> get_map();
    Player *get_player();

    void draw();

private:
    double viewing_angle = M_PI / 1.5, length = 255;
    int number_of_lines;
    std::vector<sf::RectangleShape> line;
    // sf::RectangleShape line;
    double d_, deviation, dx, k, b;
    std::vector<Object> objs;
    sf::RenderWindow *screen;
    Player *player;
    double angle_player_line;
    Point2 points_player[2];
    double floor_height = 1;

    double get_distance(Object &obj);
};
