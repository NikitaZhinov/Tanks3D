#pragma once

#include <common.hpp>
#include <string>

class Window {
   public:
    Window(int w, int h, std::string t);

    Point2 get_size();
    std::string get_title();

   private:
    int WIDTH;
    int HEIGHT;
    std::string TITLE;
};