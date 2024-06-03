#pragma once

#include "Raycast/raycast.hpp"

class Window {
public:
    Window(int w, int h, const std::string &t);

    Point2 get_size();
    std::string get_title();

private:
    int WIDTH;
    int HEIGHT;
    std::string TITLE;
};
