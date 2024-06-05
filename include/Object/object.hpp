#pragma once

#include "Raycast/raycast.hpp"
class Object {
public:
    Object(const std::vector<Point2> &points);
    Object(const std::vector<Point2> &points, sf::Texture *texture);

    sf::ConvexShape get_share();
    std::vector<Point2> get_points();
    int get_height();
    sf::Texture *get_texture();
    std::vector<int> &get_number_of_points_per_face();

    void set_color(unsigned char r, unsigned char g, unsigned char b);
    void set_height(int h);

private:
    std::vector<Point2> points = {};
    sf::ConvexShape share;
    sf::Texture *texture = nullptr;
    std::vector<int> number_of_points_per_face;
    int height = 40;
};
