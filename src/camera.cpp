#include "Raycast/raycast.hpp"

Camera::Camera(int number_of_lines, Map &map, Player *player, sf::RenderWindow *screen) {
    set_number_of_lines(number_of_lines);
    d_ = (std::sin(M_PI - viewing_angle / 2) * screen->getSize().x / 2) / std::sin(viewing_angle / 2);
    width_line = screen->getSize().x / (double)number_of_lines;

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
    return *objs;
}

Player *Camera::get_player() {
    return player;
}

void Camera::draw() {
    if (objs->empty())
        return;

    points_player[0] = player->get_position();

    for (int i = 0; i < number_of_lines; i++) {
        angle_player_line = player->get_angle() - viewing_angle / 2 + i * deviation;

        points_player[1] = {
            points_player[0].x + std::sin(-angle_player_line) * length,
            points_player[0].y + std::cos(-angle_player_line) * length
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

        lines.clear();

        for (auto &obj : *objs) {
            inter = get_intersection(obj);
            if (inter.distance >= 0) {
                double b_ = d_ / inter.distance * obj.get_height();
                line.setSize(sf::Vector2f(width_line, b_));
                line.setPosition(width_line * i, ((double)screen->getSize().y - b_) / 2);
                line.setFillColor(obj.get_colot());
                line.setTexture(obj.get_texture());
                if (obj.get_texture()) {
                    double len_of_edge = std::sqrt((inter.edge[0].x - inter.edge[1].x) * (inter.edge[0].x - inter.edge[1].x) + (inter.edge[0].y - inter.edge[1].y) * (inter.edge[0].y - inter.edge[1].y));
                    double p1_to_inter = std::sqrt((inter.edge[0].x - inter.inter.x) * (inter.edge[0].x - inter.inter.x) + (inter.edge[0].y - inter.inter.y) * (inter.edge[0].y - inter.inter.y));
                    int j = p1_to_inter * (obj.get_texture()->getSize().x / 1.5) / len_of_edge;
                    line.setTextureRect(sf::IntRect(j, 0, j + width_line, obj.get_texture()->getSize().y));
                }
                lines.push_back(line);
            }
        }

        std::sort(lines.begin(), lines.end(), [this](const sf::RectangleShape &a, const sf::RectangleShape &b) {
            return a.getSize().y < b.getSize().y;
        });

        for (auto &l : lines)
            screen->draw(l);
    }
}

Camera::Intersection Camera::get_intersection(Object &obj) {
    // get all point of object
    std::vector<Point2> points_obj = obj.get_points();

    double len = this->length;
    bool flag = false;
    Point2 p1, p2, last_p1, last_p2, inter;
    double dx_obj, k_obj, b_obj, x, y;

    for (int i = 0; i < points_obj.size(); i++) {
        p1 = { points_obj[i].x, points_obj[i].y };
        if (i + 1 == points_obj.size())
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
            double new_len = std::sqrt((std::max(x, points_player[0].x) - std::min(x, points_player[0].x)) * (std::max(x, points_player[0].x) - std::min(x, points_player[0].x)) +
                                       (std::max(y, points_player[0].y) - std::min(y, points_player[0].y)) * (std::max(y, points_player[0].y) - std::min(y, points_player[0].y)));
            if (new_len < len) {
                len = new_len;
                inter = { x, y };
                last_p1 = p1;
                last_p2 = p2;
            }
        }
    }
    if (!flag)
        return { -2 };

    return { len, inter, last_p1, last_p2 };
}

double Camera::get_distance(Object &obj) {
    Point2 p0 = obj.get_points()[0];
    double res = std::sqrt((points_player[0].x - p0.x) * (points_player[0].x - p0.x) +
                           (points_player[0].y - p0.y) * (points_player[0].y - p0.y));

    for (auto &point : obj.get_points()) {
        res = std::min(
            res,
            std::sqrt((points_player[0].x - point.x) * (points_player[0].x - point.x) +
                      (points_player[0].y - point.y) * (points_player[0].y - point.y)));
    }

    return res;
}
