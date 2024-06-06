#pragma once

#include "Raycast/raycast.hpp"

class Object {
public:
    Object(const std::vector<Point2> &points);
    Object(const std::vector<Point2> &points, unsigned char r, unsigned char g, unsigned char b);
    Object(const std::vector<Point2> &points, sf::Texture *texture);
    Object(const std::vector<Point2> &points, unsigned char r, unsigned char g, unsigned char b, sf::Texture *texture);

    sf::ConvexShape get_share();
    std::vector<Point2> get_points();
    int get_height();
    sf::Texture *get_texture();
    sf::Color get_colot();

    void set_color(unsigned char r, unsigned char g, unsigned char b);
    void set_height(int h);

private:
    std::vector<Point2> points = {};
    sf::ConvexShape share;
    sf::Texture *texture = nullptr;
    unsigned char r = 255, g = 255, b = 255;
    int height = 40;
};
