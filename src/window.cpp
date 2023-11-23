#include "window.hpp"

Window::Window(int w, int h, std::string t) {
    this->WIDTH = w;
    this->HEIGHT = h;
    this->TITLE = t.c_str();
}

Point2 Window::get_size() {
    Point2 size = {(double)this->WIDTH, (double)this->HEIGHT};
    return size;
}

std::string Window::get_title() { return this->TITLE; }
