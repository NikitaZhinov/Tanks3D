#include "Raycast/raycast.hpp"

#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Mouse.hpp>

Player::Player(int x, int y, int r, double angle) {
    set_radius(r);
    set_rotation(angle);
    init();
    set_position(x, y);
}

void Player::init() {
    texture.loadFromFile("../textures/player.png");

    shape.setPointCount(102);
    shape.setPoint(0, sf::Vector2f(position.x, position.y));
    for (int i = 1; i <= 101; i++) {
        shape.setPoint(i, sf::Vector2f(std::sin(-angle) * radius, std::cos(-angle) * radius));
        angle += 2 * M_PI / 100;
    }
    angle -= 2 * M_PI / 100;
    texture.setSmooth(true);
    shape.setFillColor(sf::Color(255, 0, 0));
    shape.setTexture(&texture);
}

Point2 Player::get_position() {
    return position;
}

double Player::get_angle() {
    return angle;
}

void Player::set_position(int x, int y) {
    position.x = x;
    position.y = y;
}

float Player::get_radius() {
    return radius;
}

void Player::set_radius(float radius) {
    this->radius = radius;
}

sf::ConvexShape Player::get_shape() {
    return shape;
}

void Player::move(int framerate_limit, sf::RenderWindow &screen) {
    // move
    if (framerate_limit != 0) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            position.x += std::sin(-angle) * speed / framerate_limit;
            position.y += std::cos(-angle) * speed / framerate_limit;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            position.x -= std::sin(-angle) * speed / framerate_limit;
            position.y -= std::cos(-angle) * speed / framerate_limit;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            position.x += std::sin(-angle + M_PI / 2) * speed / framerate_limit;
            position.y += std::cos(-angle + M_PI / 2) * speed / framerate_limit;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            position.x += std::sin(-angle - M_PI / 2) * speed / framerate_limit;
            position.y += std::cos(-angle - M_PI / 2) * speed / framerate_limit;
        }
    }
    shape.setPosition(position.x, position.y);

    // rotate
    sf::Vector2i localPosition = sf::Mouse::getPosition(screen);
    sf::Mouse::setPosition(sf::Vector2i(screen.getSize().x / 2, screen.getSize().y / 2), screen);
    angle += speed_rotation * static_cast<double>(static_cast<int>(localPosition.x) - static_cast<int>(screen.getSize().x / 2.));
    shape.setRotation(angle * 180 / M_PI - 180);
}

void Player::set_rotation(double anlge) {
    this->angle = anlge;
}
