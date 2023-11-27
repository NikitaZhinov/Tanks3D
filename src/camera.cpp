#include <camera.hpp>

Camera::Camera(int number_of_lines, Map* map, Player* player,
               sf::RenderWindow* screen) {
    set_number_of_lines(number_of_lines);
    this->d_ =
        (std::sin(M_PI - this->viewing_angle / 2) * (*screen).getSize().x / 2) /
        std::sin(this->viewing_angle / 2);
    this->deviation = this->viewing_angle / this->number_of_lines;

    this->objs = (*map).get_objects();
    this->player = player;
    this->screen = screen;
}

void Camera::set_number_of_lines(int n) {
    this->number_of_lines = n;
    this->deviation = this->viewing_angle / this->number_of_lines;
}

void Camera::set_map(Map* map) { this->objs = (*map).get_objects(); }

void Camera::set_player(Player* player) { this->player = player; }

void Camera::set_viewing_angle(double n) {
    this->viewing_angle = n;
    this->d_ =
        (std::sin(M_PI - this->viewing_angle / 2) * this->number_of_lines / 2) /
        std::sin(this->viewing_angle / 2);
}

int Camera::get_number_of_lines() { return this->number_of_lines; }

std::vector<Object> Camera::get_map() { return this->objs; }

Player* Camera::get_player() { return this->player; }

void Camera::draw() {
    for (int i = 0; i < this->number_of_lines; i++) {
        this->angle_player_line = (*this->player).get_angle() -
                                  this->viewing_angle / 2 + i * this->deviation;

        (this->points_player)[0] = (*this->player).get_position();
        (this->points_player)[1] = {
            (*this->player).get_position().x +
                std::sin(-(this->angle_player_line)) * this->length,
            (*this->player).get_position().y +
                std::cos(-(this->angle_player_line)) * this->length};

        this->dx = (this->points_player)[0].x - (this->points_player)[1].x;
        this->k = ((this->points_player)[0].y - (this->points_player)[1].y) /
                  this->dx;
        this->b =
            (this->points_player)[0].y - this->k * (this->points_player)[0].x;

        // sf::Vertex line[] = {
        //     sf::Vertex(sf::Vector2f((this->points_player)[0].x,
        //     (this->points_player)[0].y)),
        //     sf::Vertex(sf::Vector2f((this->points_player)[1].x,
        //     (this->points_player)[1].y)),
        // };
        // (*screen).draw(line, 2, sf::Lines);

        sort_objs();

        for (int j = 0; j < (this->objs).size(); j++) {
            double d = get_distance(&((this->objs)[j]));
            if (d >= 0) {
                double b_ = this->d_ / d * (this->objs)[j].get_height();
                double len = (*this->screen).getSize().x /
                             (double)(this->number_of_lines);
                (this->line).setSize(sf::Vector2f(len, b_));
                (this->line)
                    .setPosition(
                        len * i,
                        ((double)(*this->screen).getSize().y - b_) / 2);
                int color = 255 - d;
                if (color < 0) color = 0;
                (this->line).setFillColor(sf::Color(0, color, 0));

                (*this->screen).draw((this->line));
            }
        }
    }
}

double Camera::get_distance(Object* obj) {
    // if object is not initialized
    if ((*obj).get_points().empty()) return -1;

    // get all point of object
    int count_points_obj = (*obj).get_points().size();
    Point2 points_obj[count_points_obj];
    for (int i = 0; i < count_points_obj; i++)
        points_obj[i] = (*obj).get_points()[i];

    double len = this->length;
    bool flag = false;
    Point2 p1, p2;
    double dx_obj, k_obj, b_obj, x, y;
    for (int i = 0; i < count_points_obj; i++) {
        p1 = {points_obj[i].x, points_obj[i].y};
        if (i + 1 == count_points_obj)
            p2 = {points_obj[0].x, points_obj[0].y};
        else
            p2 = {points_obj[i + 1].x, points_obj[i + 1].y};

        // get intersection point
        dx_obj = p1.x - p2.x;
        if ((int)dx_obj == 0) {
            if ((int)(this->dx) == 0)
                continue;
            else {
                if (std::min((this->points_player)[0].x,
                             (this->points_player)[1].x) <= p1.x and
                    std::max((this->points_player)[0].x,
                             (this->points_player)[1].x) >= p1.x) {
                    x = p1.x;
                    y = k * x + b;
                } else
                    continue;
            }
        } else {
            k_obj = (p1.y - p2.y) / dx_obj;
            b_obj = p1.y - k_obj * p1.x;
            if ((int)(this->dx) == 0) {
                if (std::min(p1.x, p2.x) <= (this->points_player)[0].x and
                    std::max(p1.x, p2.x) >= (this->points_player)[0].x)
                    x = (this->points_player)[0].x;
                else
                    continue;
            } else
                x = (b_obj - b) / (k - k_obj);
            y = k_obj * x + b_obj;
        }

        // if point belongs to both lines
        if (x >= std::min((this->points_player)[0].x,
                          (this->points_player)[1].x) and
            x <= std::max((this->points_player)[0].x,
                          (this->points_player)[1].x) and
            y >= std::min((this->points_player)[0].y,
                          (this->points_player)[1].y) and
            y <= std::max((this->points_player)[0].y,
                          (this->points_player)[1].y) and
            x >= std::min(p1.x, p2.x) and x <= std::max(p1.x, p2.x) and
            y >= std::min(p1.y, p2.y) and y <= std::max(p1.y, p2.y)) {
            flag = true;
            len = std::min(
                len,
                std::sqrt(std::pow(std::max(x, (this->points_player)[0].x) -
                                       std::min(x, (this->points_player)[0].x),
                                   2) +
                          std::pow(std::max(y, (this->points_player)[0].y) -
                                       std::min(y, (this->points_player)[0].y),
                                   2)));
        }
    }
    if (!flag) return -2;

    return len;
}

double Camera::get_distance_to_obj(Object* obj) {
    return std::sqrt(std::pow(std::max((*obj).get_points()[0].x,
                                       (*this->player).get_position().x) -
                                  std::min((*obj).get_points()[0].x,
                                           (*this->player).get_position().x),
                              2) +
                     std::pow(std::max((*obj).get_points()[0].y,
                                       (*this->player).get_position().y) -
                                  std::min((*obj).get_points()[0].y,
                                           (*this->player).get_position().y),
                              2));
}

void Camera::sort_objs() { sort_objs(0, this->objs.size() - 1); }

void Camera::sort_objs(int start, int end) {
    if (start >= end) return;
    int rightStart = sort_objs_(start, end);
    sort_objs(start, rightStart - 1);
    sort_objs(rightStart, end);
}

int Camera::sort_objs_(int left, int right) {
    double privot = get_distance(&((this->objs)[(left + right) / 2]));
    while (left <= right) {
        while (get_distance(&((this->objs)[left])) > privot) left++;
        while (get_distance(&((this->objs)[right])) < privot) right--;
        if (left <= right) {
            Object temp = (this->objs)[left];
            (this->objs)[left] = (this->objs)[right];
            (this->objs)[right] = temp;
            left++;
            right--;
        }
    }
    return left;
}