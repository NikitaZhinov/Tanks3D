#include "Raycast/raycast.hpp"

Window::Window(int w, int h, const std::string &t) {
    WIDTH = w;
    HEIGHT = h;
    TITLE = t;
}

Point2 Window::get_size() {
    return { (double)WIDTH, (double)HEIGHT };
}

std::string Window::get_title() {
    return TITLE;
}
