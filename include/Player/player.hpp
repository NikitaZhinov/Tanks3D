#pragma once

#include "Raycast/raycast.hpp"

class Player {
public:
    Player(int x, int y, int r, double angle);

    Point2 get_position();
    float get_radius();
    sf::ConvexShape get_shape();
    double get_angle();

    void set_position(int x, int y);
    void set_radius(float radius);
    void set_rotation(double anlge);

    void move(int framerate_limit, sf::RenderWindow &screen);

private:
    Point2 position;
    float radius;
    sf::ConvexShape shape;
    sf::Texture texture;
    double angle;
    double speed = 50;
    double speed_rotation = M_PI / 50;

    void init();
};
