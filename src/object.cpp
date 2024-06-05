#include "Raycast/raycast.hpp"

Object::Object(const std::vector<Point2> &points) {
    share.setPointCount(points.size());
    for (int i = 0; i < points.size(); i++) {
        this->points.push_back(points[i]);
        share.setPoint(i, sf::Vector2f(points[i].x, points[i].y));
    }
}

Object::Object(const std::vector<Point2> &points, sf::Texture *texture) :
    Object(points) {
    this->texture = texture;
    number_of_points_per_face.resize(points.size());

    for (int i = 0; i < points.size(); i++) {
        Point2 p1 = points[i];
        Point2 p2 = points[(i + 1 == points.size()) ? 0 : i + 1];

        double len = std::sqrt(std::pow(p1.x - p2.x, 2) + std::pow(p1.y - p2.y, 2));
        int number_of_points = len / texture->getSize().x;
        number_of_points_per_face[i] = number_of_points;
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

sf::Texture *Object::get_texture() {
    return texture;
}

std::vector<int> &Object::get_number_of_points_per_face() {
    return number_of_points_per_face;
}

void Object::set_color(unsigned char r, unsigned char g, unsigned char b) {
    share.setFillColor(sf::Color(r, g, b));
}

void Object::set_height(int h) {
    height = h;
}
