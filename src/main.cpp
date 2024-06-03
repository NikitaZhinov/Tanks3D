#include "Raycast/raycast.hpp"

int main() {
    const int MAX_FPS = 1000;

    Window window(800, 600, "Tanks3D");
    Player player(10, 110, 10, M_PI);
    std::vector<Point2> points1 = {
        {   0,   0 },
        { 100,   0 },
        { 100, 100 },
        {   0, 100 }
    };

    std::vector<Point2> points2 = {
        { 200, 200 },
        { 100, 300 },
        { 200, 300 }
    };

    Object obj1(points1, "../textures/wall.jpg");
    obj1.set_color(0, 0, 200);
    Object obj2(points2);
    obj2.set_color(0, 0, 200);
    Map map;
    map.add_object(obj1);
    map.add_object(obj2);

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow screen(
        sf::VideoMode(window.get_size().x, window.get_size().y),
        window.get_title().c_str(),
        sf::Style::Default,
        settings);
    screen.setFramerateLimit(MAX_FPS);

    Camera camera(window.get_size().x, map, &player, &screen);

    while (screen.isOpen()) {
        sf::Event event;
        while (screen.pollEvent(event))
            if (event.type == sf::Event::Closed)
                screen.close();

        Time::update();
        int fps = 1.0 / Time::deltaTime();
        std::string title = std::to_string(fps) + " FPS";
        screen.setTitle(title);

        screen.clear();

        camera.draw();

        map.draw(&screen);

        screen.draw(player.get_shape());
        player.move(fps);

        screen.display();
    }

    return 0;
}