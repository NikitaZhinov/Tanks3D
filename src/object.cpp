#include "object.hpp"

#include <SFML/Graphics/Color.hpp>

Object::Object(std::vector<Point2> points) {
    this->share.setPointCount(points.size());
    for (int i = 0; i < points.size(); i++) {
        this->points.push_back(points[i]);
        this->share.setPoint(i, sf::Vector2f(points[i].x, points[i].y));
    }
}

sf::ConvexShape Object::get_share() { return this->share; }

std::vector<Point2> Object::get_points() { return this->points; }

int Object::get_height() { return this->height; }

void Object::set_color(unsigned char r, unsigned char g, unsigned char b) {
    this->share.setFillColor(sf::Color(r, g, b));
}

void Object::set_height(int h) { this->height = h; }