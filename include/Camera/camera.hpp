#pragma once

#include "Raycast/raycast.hpp"

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
    struct Intersection {
        double distance;
        Point2 inter;
        Point2 edge[2];
    };

    Intersection inter;
    double viewing_angle = M_PI / 1.5, length = 255;
    int number_of_lines;
    // std::vector<sf::RectangleShape> line;
    sf::RectangleShape line;
    std::vector<sf::RectangleShape> lines;
    double width_line;
    double d_, deviation, dx, k, b;
    std::vector<Object> *objs = nullptr;
    sf::RenderWindow *screen;
    Player *player;
    double angle_player_line;
    Point2 points_player[2];
    double floor_height = 1;

    Intersection get_intersection(Object &obj);
    double get_distance(Object &obj);
};
