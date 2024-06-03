#pragma once

#include "Raycast/raycast.hpp"

namespace Time {
    namespace {
        double _time;
        double _deltaTime;
    } // namespace

    double time();
    double deltaTime();
    void update();
} // namespace Time
