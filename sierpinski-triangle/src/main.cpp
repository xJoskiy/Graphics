#include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm>
#include <thread>
#include <chrono>
#include <iostream>

using namespace std::chrono_literals;

sf::Vector2f generate_pos(const std::vector<sf::Vector2f>& base_points, const sf::Vector2f& point) {
    int ind = std::rand() % 3;
    float x_new = (point.x + base_points[ind].x) / 2;
    float y_new = (point.y + base_points[ind].y) / 2;
    return {x_new, y_new};
}

sf::CircleShape generate_point(const std::vector<sf::Vector2f>& base_pos, const sf::Vector2f& pos) {
    sf::Vector2f new_pos = generate_pos(base_pos, pos);
    auto point = sf::CircleShape(1.5f);
    point.setFillColor(sf::Color::White);
    point.setPosition(new_pos);
    return point;
}

int main() {
    std::srand(time(NULL));
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Leavy Curve", 7u, settings);
    std::vector<sf::Vector2f> base_pos = {{430, 180}, {1490, 180}, {960, 900}};
    std::vector<sf::CircleShape> points;
    points.reserve(10000);

    for (auto pos: base_pos) {
        auto new_point = sf::CircleShape(1.5f);
        new_point.setPosition(pos);
        new_point.setFillColor(sf::Color::White);
        points.push_back(new_point);
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        sf::CircleShape new_point = generate_point(base_pos, points.back().getPosition());
        points.push_back(new_point);

        window.clear(sf::Color::Black);
        for (const auto& point: points) window.draw(point);
        window.display();
    }
}
