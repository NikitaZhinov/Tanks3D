#include "Raycast/raycast.hpp"
#include <SFML/Window/Keyboard.hpp>

int main() {
    const int MAX_FPS = 60;

    Player player(80, 300, 10, M_PI);
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

    Point2 pos3 = { 100, 300 };
    double radius = 20;
    std::vector<Point2> points3(19);
    for (int i = 0; i < points3.size(); i++) {
        points3[i] = { std::cos(2. * M_PI / (double)points3.size() * (double)i) * radius + pos3.x, std::sin(2. * M_PI / (double)points3.size() * (double)i) * radius + pos3.y };
    }

    sf::Texture wall_texture, wall2_texture, player_texture;
    wall_texture.loadFromFile("../textures/wall.jpg");
    wall2_texture.loadFromFile("../textures/wall2.jpg");
    player_texture.loadFromFile("../textures/player.png");

    Object obj1(points1, &wall_texture);
    obj1.set_color(0, 0, 200);
    Object obj2(points2, &wall2_texture);
    obj2.set_color(0, 0, 200);
    Object obj3(points3, &wall2_texture);
    obj3.set_color(0, 0, 200);
    Map map;
    map.add_object(obj1);
    map.add_object(obj2);
    map.add_object(obj3);

    sf::ContextSettings settings;
    settings.antialiasingLevel = 1;

    sf::RenderWindow screen(
        sf::VideoMode(800, 600),
        "Tanks3D",
        sf::Style::Default,
        settings);
    screen.setFramerateLimit(MAX_FPS);
    screen.setMouseCursorVisible(false);

    Camera camera(screen.getSize().x, map, &player, &screen);

    sf::RectangleShape floor(sf::Vector2f(screen.getSize().x, screen.getSize().y / 2.));
    floor.setPosition(sf::Vector2f(0, screen.getSize().y / 2.));
    floor.setFillColor(sf::Color(150, 150, 150));

    sf::RectangleShape sky(sf::Vector2f(screen.getSize().x, screen.getSize().y / 2.));
    sky.setPosition(sf::Vector2f(0, 0));
    sky.setFillColor(sf::Color(130, 195, 255));

    while (screen.isOpen()) {
        sf::Event event;
        while (screen.pollEvent(event))
            if (event.type == sf::Event::Closed or sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                screen.close();

        Time::update();
        int fps = 1. / Time::deltaTime();
        std::string title = std::to_string(fps) + " FPS";
        screen.setTitle(title);

        screen.clear();

        screen.draw(floor);
        screen.draw(sky);

        camera.draw();

        map.draw(&screen);

        screen.draw(player.get_shape());
        player.move(fps, screen);

        screen.display();
    }

    return 0;
}