#include "Raycast/raycast.hpp"

Camera::Camera(int number_of_lines, Map &map, Player *player, sf::RenderWindow *screen) {
    set_number_of_lines(number_of_lines);
    d_ = (std::sin(M_PI - viewing_angle / 2) * screen->getSize().x / 2) / std::sin(viewing_angle / 2);

    objs = map.get_objects();
    this->player = player;
    this->screen = screen;
}

void Camera::set_number_of_lines(int n) {
    number_of_lines = n;
    deviation = viewing_angle / number_of_lines;
}

void Camera::set_map(Map &map) {
    objs = map.get_objects();
}

void Camera::set_player(Player *player) {
    this->player = player;
}

void Camera::set_viewing_angle(double n) {
    viewing_angle = n;
    d_ = (std::sin(M_PI - viewing_angle / 2) * number_of_lines / 2) / std::sin(viewing_angle / 2);
}

int Camera::get_number_of_lines() {
    return number_of_lines;
}

std::vector<Object> Camera::get_map() {
    return objs;
}

Player *Camera::get_player() {
    return player;
}

void Camera::draw() {
    for (int i = 0; i < number_of_lines; i++) {
        angle_player_line = player->get_angle() - viewing_angle / 2 + i * deviation;

        points_player[0] = player->get_position();
        points_player[1] = {
            player->get_position().x + std::sin(-(angle_player_line)) * length,
            player->get_position().y + std::cos(-(angle_player_line)) * length
        };

        dx = points_player[0].x - points_player[1].x;
        k = (points_player[0].y - points_player[1].y) / dx;
        b = points_player[0].y - k * points_player[0].x;

        // sf::Vertex l[] = {
        //     sf::Vertex(sf::Vector2f((points_player)[0].x,
        //     (points_player)[0].y)),
        //     sf::Vertex(sf::Vector2f((points_player)[1].x,
        //     (points_player)[1].y)),
        // };
        // screen->draw(l, 2, sf::Lines);

        std::sort(objs.begin(), objs.end(), [this](Object &a, Object &b) {
            return get_distance(a).distance > get_distance(b).distance;
        });

        for (auto &obj : objs) {
            Intersection inter = get_distance(obj);
            if (inter.distance >= 0) {
                double b_ = d_ / inter.distance * obj.get_height();
                double len = screen->getSize().x / (double)number_of_lines;
                line.setSize(sf::Vector2f(len, b_));
                line.setPosition(len * i, ((double)screen->getSize().y - b_) / 2);
                int color = 255 - inter.distance / (length / 255.);
                if (color < 0)
                    color = 0;
                line.setFillColor(sf::Color(color, color, color));
                line.setTexture(obj.get_texture());
                if (obj.get_texture()) {
                    double len_of_edge = std::sqrt(std::pow(inter.edge[0].x - inter.edge[1].x, 2) + std::pow(inter.edge[0].y - inter.edge[1].y, 2));
                    double p1_to_inter = std::sqrt(std::pow(inter.edge[0].x - inter.inter.x, 2) + std::pow(inter.edge[0].y - inter.inter.y, 2));
                    int j = p1_to_inter * (obj.get_texture()->getSize().x / 1.5) / len_of_edge;
                    line.setTextureRect(sf::IntRect(j, 0, j + len, obj.get_texture()->getSize().y));
                }
                screen->draw(line);
            }
        }
    }
}

Camera::Intersection Camera::get_distance(Object &obj) {
    // if object is not initialized
    if (obj.get_points().empty())
        return {-1};

    // get all point of object
    int count_points_obj = obj.get_points().size();
    Point2 points_obj[count_points_obj];
    for (int i = 0; i < count_points_obj; i++)
        points_obj[i] = obj.get_points()[i];

    double len = this->length;
    bool flag = false;
    Point2 p1, p2, last_p1, last_p2, inter;
    double dx_obj, k_obj, b_obj, x, y;
    for (int i = 0; i < count_points_obj; i++) {
        p1 = { points_obj[i].x, points_obj[i].y };
        if (i + 1 == count_points_obj)
            p2 = { points_obj[0].x, points_obj[0].y };
        else
            p2 = { points_obj[i + 1].x, points_obj[i + 1].y };

        // get intersection point
        dx_obj = p1.x - p2.x;
        if ((int)dx_obj == 0) {
            if ((int)dx == 0)
                continue;
            else {
                if (std::min(points_player[0].x, points_player[1].x) <= p1.x and
                    std::max(points_player[0].x, points_player[1].x) >= p1.x) {
                    x = p1.x;
                    y = k * x + b;
                } else
                    continue;
            }
        } else {
            k_obj = (p1.y - p2.y) / dx_obj;
            b_obj = p1.y - k_obj * p1.x;
            if ((int)dx == 0) {
                if (std::min(p1.x, p2.x) <= points_player[0].x and
                    std::max(p1.x, p2.x) >= points_player[0].x)
                    x = points_player[0].x;
                else
                    continue;
            } else
                x = (b_obj - b) / (k - k_obj);
            y = k_obj * x + b_obj;
        }

        // if point belongs to both lines
        if (x >= std::min(points_player[0].x, points_player[1].x) and x <= std::max(points_player[0].x, points_player[1].x) and
            y >= std::min(points_player[0].y, points_player[1].y) and y <= std::max(points_player[0].y, points_player[1].y) and
            x >= std::min(p1.x, p2.x) and x <= std::max(p1.x, p2.x) and
            y >= std::min(p1.y, p2.y) and y <= std::max(p1.y, p2.y)) {
            flag = true;
            int old_len = len;
            len = std::min(len,
                           std::sqrt(std::pow(std::max(x, points_player[0].x) - std::min(x, points_player[0].x), 2) +
                                     std::pow(std::max(y, points_player[0].y) - std::min(y, points_player[0].y), 2)));
            if (len < old_len) {
                inter = {x, y};
                last_p1 = p1;
                last_p2 = p2;
            }
        }
    }
    if (!flag)
        return {-2};

    return {len, inter, last_p1, last_p2};
}
