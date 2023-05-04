#include <SFML/Graphics.hpp>

#include <iostream>
#include <math.h>
#include <vector>
#include <map>
#include <string>
#include <random>
#include <memory>
#include <chrono>

#include <SFML/Graphics.hpp>

class DragShape {
public:
    DragShape(sf::Shape* shape) {
        m_shape = shape;
        m_isDragging = false;
    }

    void handleInput(sf::RenderWindow& window) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Vector2f mousePosFloat = static_cast<sf::Vector2f>(mousePos);

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            if (m_shape->getGlobalBounds().contains(mousePosFloat)) {
                m_isDragging = true;
                m_offset = mousePosFloat - m_shape->getPosition();
            }
        }
        else {
            m_isDragging = false;
        }
    }

    void update(sf::RenderWindow& window) {
        if (m_isDragging) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            sf::Vector2f mousePosFloat = static_cast<sf::Vector2f>(mousePos);

            m_shape->setPosition(mousePosFloat - m_offset);
        }
    }

private:
    sf::Shape* m_shape;
    bool m_isDragging;
    sf::Vector2f m_offset;
};

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Drag Shape Example");

    // Create a circle shape
    sf::CircleShape circle(50.f);
    circle.setFillColor(sf::Color::Red);
    circle.setPosition(100.f, 100.f);

    // Create a rectangle shape
    sf::RectangleShape rectangle(sf::Vector2f(100.f, 50.f));
    rectangle.setFillColor(sf::Color::Green);
    rectangle.setPosition(300.f, 200.f);

    // Create DragShape objects for the circle and rectangle
    DragShape dragCircle(&circle);
    DragShape dragRectangle(&rectangle);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Handle input for the drag objects
        dragCircle.handleInput(window);
        dragRectangle.handleInput(window);

        // Update the drag objects
        dragCircle.update(window);
        dragRectangle.update(window);

        window.clear();

        // Draw the circle and rectangle
        window.draw(circle);
        window.draw(rectangle);

        window.display();
    }

    return 0;
}