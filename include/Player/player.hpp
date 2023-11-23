#pragma once

#include <cmath>
#include <common.hpp>

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

    void move(int framerate_limit);

   private:
    Point2 position;
    float radius;
    sf::ConvexShape shape;
    sf::Texture texture;
    double angle;
    double speed = 0.05;
    double speed_rotation = M_PI / 768;

    void init();
};