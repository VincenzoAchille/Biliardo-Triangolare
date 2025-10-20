#include "button.hpp"
#include "Methods.cpp"
#include <cmath>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>

button::button(const std::string& buttonText, const sf::Vector2f& position, const sf::Vector2f& size) {
        // Carica il font (assicurati di avere un file font nella directory)
        if (!font.loadFromFile("arial.ttf")) {
            std::cout << "Errore nel caricamento del font!" << std::endl;
        }
        
        // Configura la forma del bottone
        shape.setSize(size);
        shape.setPosition(position);
        
        // Colori
        defaultColor = sf::Color(70, 70, 70);
        hoverColor = sf::Color(100, 100, 100);
        pressedColor = sf::Color(50, 50, 50);
        
        shape.setFillColor(defaultColor);
        shape.setOutlineThickness(2);
        shape.setOutlineColor(sf::Color::White);
        
        // Configura il testo
        text.setFont(font);
        text.setString(buttonText);
        text.setCharacterSize(20);
        text.setFillColor(sf::Color::White);
        
        // Centra il testo nel bottone
        sf::FloatRect textBounds = text.getLocalBounds();
        text.setOrigin(textBounds.left + textBounds.width / 2.0f,
                      textBounds.top + textBounds.height / 2.0f);
        text.setPosition(position.x + size.x / 2.0f, position.y + size.y / 2.0f);
        
        isPressed = false;
        isHovered = false;
    }
    
    void button::draw(sf::RenderWindow& window) {
        window.draw(shape);
        window.draw(text);
    }
    
    void button::update(sf::RenderWindow& window) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::FloatRect buttonBounds = shape.getGlobalBounds();
        
        // Controlla se il mouse è sopra il bottone
        isHovered = buttonBounds.contains(static_cast<sf::Vector2f>(mousePos));
        
        // Cambia colore in base allo stato
        if (isPressed) {
            shape.setFillColor(pressedColor);
        } else if (isHovered) {
            shape.setFillColor(hoverColor);
        } else {
            shape.setFillColor(defaultColor);
        }
    }
    
    bool button::isClicked(sf::Event& event) {
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left && isHovered) {
                isPressed = true;
                return true;
            }
        }
        
        if (event.type == sf::Event::MouseButtonReleased) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                isPressed = false;
            }
        }
        
        return false;
    }
    
/*
Esempio di Utilizzo
cpp
int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Button Example");
    
    // Crea alcuni bottoni
    Button button1("Click Me!", sf::Vector2f(300, 200), sf::Vector2f(200, 50));
    Button button2("Another Button", sf::Vector2f(300, 300), sf::Vector2f(200, 50));
    
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            
            // Controlla i click sui bottoni
            if (button1.isClicked(event)) {
                std::cout << "Bottone 1 cliccato!" << std::endl;
                button1.setText("Clicked!");
            }
            
            if (button2.isClicked(event)) {
                std::cout << "Bottone 2 cliccato!" << std::endl;
                button2.setText("Anche io!");
            }
        }
        
        // Aggiorna gli stati dei bottoni
        button1.update(window);
        button2.update(window);
        
        // Disegna
        window.clear(sf::Color(30, 30, 30));
        button1.draw(window);
        button2.draw(window);
        window.display();
    }
    
    return 0;
}*/
/*Versione più Semplice (Senza Classe)
Se vuoi una versione più semplice senza creare una classe:

cpp
bool button::isButtonClicked(const sf::RectangleShape& button, const sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            sf::FloatRect bounds = button.getGlobalBounds();
            return bounds.contains(event.mouseButton.x, event.mouseButton.y);
        }
    }
    return false;
}

bool button::isMouseOver(const sf::RectangleShape& button, const sf::RenderWindow& window) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    return button.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
}*/



