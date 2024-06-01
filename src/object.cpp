#include "Object/object.hpp"

#include <SFML/Graphics/Color.hpp>

Object::Object(const std::vector<Point2> &points) {
    share.setPointCount(points.size());
    for (int i = 0; i < points.size(); i++) {
        this->points.push_back(points[i]);
        share.setPoint(i, sf::Vector2f(points[i].x, points[i].y));
    }
}

sf::ConvexShape Object::get_share() {
    return share;
}

std::vector<Point2> Object::get_points() {
    return points;
}

int Object::get_height() {
    return height;
}

void Object::set_color(unsigned char r, unsigned char g, unsigned char b) {
    share.setFillColor(sf::Color(r, g, b));
}

void Object::set_height(int h) {
    height = h;
}
