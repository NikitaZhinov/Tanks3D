#include "Raycast/raycast.hpp"

Object::Object(const std::vector<Point2> &points) {
    share.setPointCount(points.size());
    for (int i = 0; i < points.size(); i++) {
        this->points.push_back(points[i]);
        share.setPoint(i, sf::Vector2f(points[i].x, points[i].y));
    }
}

Object::Object(const std::vector<Point2> &points, unsigned char r, unsigned char g, unsigned char b) :
    Object(points) {
    this->r = r;
    this->g = g;
    this->b = b;
}

Object::Object(const std::vector<Point2> &points, sf::Texture *texture) :
    Object(points) {
    this->texture = texture;
}

Object::Object(const std::vector<Point2> &points, unsigned char r, unsigned char g, unsigned char b, sf::Texture *texture) :
    Object(points, texture) {
    this->r = r;
    this->g = g;
    this->b = b;
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

sf::Texture *Object::get_texture() {
    return texture;
}

sf::Color Object::get_colot() {
    sf::Color c(r, g, b);
    return c;
}

void Object::set_color(unsigned char r, unsigned char g, unsigned char b) {
    share.setFillColor(sf::Color(r, g, b));
}

void Object::set_height(int h) {
    height = h;
}
