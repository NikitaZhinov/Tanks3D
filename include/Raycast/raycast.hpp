#pragma once

#include <SFML/Graphics.hpp>
#include <chrono>
#include <cmath>
#include <string>
#include <vector>

typedef struct {
    double x;
    double y;
} Point2;

class Camera;
class Map;
class Object;
class Player;

#include "Camera/camera.hpp"
#include "Map/map.hpp"
#include "Object/object.hpp"
#include "Player/player.hpp"
#include "Time/time.hpp"
#include "Sprite/sprite.hpp"
