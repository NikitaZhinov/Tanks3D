#include "Raycast/raycast.hpp"

namespace Time {
    double time() {
        return _time;
    }

    double deltaTime() {
        return _deltaTime;
    }

    void update() {
        std::chrono::duration<double> t =
            std::chrono::system_clock::now().time_since_epoch();
        _deltaTime = t.count() - _time;
        _time = t.count();
    }
} // namespace Time