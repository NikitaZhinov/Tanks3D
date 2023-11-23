#include "player.hpp"

#include <iostream>

Player::Player(int x, int y, int r, double angle) {
    set_radius(r);
    set_rotation(angle);
    init();
    set_position(x, y);
}

void Player::init() {
    this->texture.loadFromFile("../textures/player.png");

    this->shape.setPointCount(102);
    this->shape.setPoint(0, sf::Vector2f(this->position.x, this->position.y));
    for (int i = 1; i <= 101; i++) {
        this->shape.setPoint(
            i, sf::Vector2f(std::sin(-this->angle) * this->radius,
                            std::cos(-this->angle) * this->radius));
        this->angle += 2 * M_PI / 100;
    }
    this->angle -= 2 * M_PI / 100;
    this->texture.setSmooth(true);
    this->shape.setFillColor(sf::Color(255, 0, 0));
    this->shape.setTexture(&texture);
}

Point2 Player::get_position() { return this->position; }

double Player::get_angle() { return this->angle; }

void Player::set_position(int x, int y) {
    this->position.x = x;
    this->position.y = y;
}

float Player::get_radius() { return this->radius; }

void Player::set_radius(float radius) { this->radius = radius; }

sf::ConvexShape Player::get_shape() { return this->shape; }

void Player::move(int framerate_limit) {
    // move
    int k = 1000;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        this->position.x +=
            std::sin(-this->angle) * this->speed / framerate_limit * k;
        this->position.y +=
            std::cos(-this->angle) * this->speed / framerate_limit * k;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        this->position.x -=
            std::sin(-this->angle) * this->speed / framerate_limit * k;
        this->position.y -=
            std::cos(-this->angle) * this->speed / framerate_limit * k;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        this->position.x += std::sin(-this->angle + M_PI / 2) * this->speed /
                            framerate_limit * k;
        this->position.y += std::cos(-this->angle + M_PI / 2) * this->speed /
                            framerate_limit * k;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        this->position.x += std::sin(-this->angle - M_PI / 2) * this->speed /
                            framerate_limit * k;
        this->position.y += std::cos(-this->angle - M_PI / 2) * this->speed /
                            framerate_limit * k;
    }
    this->shape.setPosition(this->position.x, this->position.y);

    // rotate
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        this->angle -= this->speed_rotation / framerate_limit * k;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        this->angle += this->speed_rotation / framerate_limit * k;
    }
    this->shape.setRotation(this->angle * 180 / M_PI - 180);
}

void Player::set_rotation(double anlge) { this->angle = anlge; }