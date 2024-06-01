#pragma once

#include "Common/common.hpp"

#include <vector>

class Object {
public:
    Object(const std::vector<Point2> &points);

    sf::ConvexShape get_share();
    std::vector<Point2> get_points();
    int get_height();

    void set_color(unsigned char r, unsigned char g, unsigned char b);
    void set_height(int h);

private:
    std::vector<Point2> points = {};
    sf::ConvexShape share;
    int height = 40;
};