#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>

class button{
    public:
    button(const std::string& buttonText, const sf::Vector2f& position, const sf::Vector2f& size);
    void draw(sf::RenderWindow& window);
    void update(sf::RenderWindow& window);
    bool isClicked(sf::Event& event);

    private:
    sf::RectangleShape shape;
    sf::Text text;
    sf::Font font;
    sf::RenderWindow window;
    
    sf::Color defaultColor;
    sf::Color hoverColor;
    sf::Color pressedColor;
    
    bool isPressed;
    bool isHovered;
};

#endif