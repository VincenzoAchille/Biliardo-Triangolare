#include <SFML/Graphics.hpp>
#include <iostream>
#include "button.hpp"
#include <string>

int main() {
    //prima config
    sf::RenderWindow window(sf::VideoMode(1600, 900), "biliardo");
    sf::Font font;
    if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf")) {
        std::cout << "Errore caricamento font!" << std::endl;
        return -1;
    }
    
    // Elementi UI
    //struttura
    sf::RectangleShape rectangle1(sf::Vector2f(500, 40));
    rectangle1.setPosition(0,0);
    rectangle1.setFillColor(sf::Color(150, 150, 150));
    rectangle1.setOutlineColor(sf::Color::Black);
    rectangle1.setOutlineThickness(0);
    sf::RectangleShape rectangle2(sf::Vector2f(500, 40));
    rectangle2.setPosition(0,195);
    rectangle2.setFillColor(sf::Color(150, 150, 150));
    rectangle2.setOutlineColor(sf::Color::Black);
    rectangle2.setOutlineThickness(0);
    sf::RectangleShape rectangleTry(sf::Vector2f(1100, 600));
    rectangleTry.setPosition(500,0);
    rectangleTry.setFillColor(sf::Color::Black);
    rectangleTry.setOutlineColor(sf::Color::Black);
    rectangleTry.setOutlineThickness(0);
    //l
    sf::Text outputTextl("l: ", font, 30);
    outputTextl.setPosition(15, 55);
    outputTextl.setFillColor(sf::Color::Black);
    sf::RectangleShape inputBoxl(sf::Vector2f(100, 30));
    inputBoxl.setPosition(75, 60);
    inputBoxl.setFillColor(sf::Color(180, 180, 180));
    inputBoxl.setOutlineColor(sf::Color::Black);
    inputBoxl.setOutlineThickness(2);
    sf::Text inputTextl("", font, 20);
    inputTextl.setPosition(0, 60);
    inputTextl.setFillColor(sf::Color::Black);
    sf::RectangleShape buttonl(sf::Vector2f(80, 30));
    buttonl.setPosition(190, 60);
    buttonl.setFillColor(sf::Color(180, 180, 180));
    buttonl.setOutlineColor(sf::Color::Black);
    buttonl.setOutlineThickness(2);
    sf::Text buttonTextl("applica", font, 18);
    buttonTextl.setPosition(198, 62);
    buttonTextl.setFillColor(sf::Color::Black);
    //r1
    sf::Text outputTextR1("r1: ", font, 30);
    outputTextR1.setPosition(15, 100);
    outputTextR1.setFillColor(sf::Color::Black);
    sf::RectangleShape inputBoxR1(sf::Vector2f(100, 30));
    inputBoxR1.setPosition(75, 105);
    inputBoxR1.setFillColor(sf::Color(180, 180, 180));
    inputBoxR1.setOutlineColor(sf::Color::Black);
    inputBoxR1.setOutlineThickness(2);
    sf::Text inputTextR1("", font, 20);
    inputTextR1.setPosition(0, 105);
    inputTextR1.setFillColor(sf::Color::Black);
    sf::RectangleShape buttonR1(sf::Vector2f(80, 30));
    buttonR1.setPosition(190, 105);
    buttonR1.setFillColor(sf::Color(180, 180, 180));
    buttonR1.setOutlineColor(sf::Color::Black);
    buttonR1.setOutlineThickness(2);
    sf::Text buttonTextR1("applica", font, 18);
    buttonTextR1.setPosition(198, 107);
    buttonTextR1.setFillColor(sf::Color::Black);
    //r2
    sf::Text outputTextR2("r2: ", font, 30);
    outputTextR2.setPosition(15, 145);
    outputTextR2.setFillColor(sf::Color::Black);
    sf::RectangleShape inputBoxR2(sf::Vector2f(100, 30));
    inputBoxR2.setPosition(75, 150);
    inputBoxR2.setFillColor(sf::Color(180, 180, 180));
    inputBoxR2.setOutlineColor(sf::Color::Black);
    inputBoxR2.setOutlineThickness(2);
    sf::Text inputTextR2("", font, 20);
    inputTextR2.setPosition(0, 150);
    inputTextR2.setFillColor(sf::Color::Black);
    sf::RectangleShape buttonR2(sf::Vector2f(80, 30));
    buttonR2.setPosition(190, 150);
    buttonR2.setFillColor(sf::Color(180, 180, 180));
    buttonR2.setOutlineColor(sf::Color::Black);
    buttonR2.setOutlineThickness(2);
    sf::Text buttonTextR2("applica", font, 18);
    buttonTextR2.setPosition(198, 152);
    buttonTextR2.setFillColor(sf::Color::Black);
    //y0
    sf::Text outputTextY0("y0: ", font, 30);
    outputTextY0.setPosition(15, 250);
    outputTextY0.setFillColor(sf::Color::Black);
    sf::RectangleShape inputBoxY0(sf::Vector2f(100, 30));
    inputBoxY0.setPosition(75, 255);
    inputBoxY0.setFillColor(sf::Color(180, 180, 180));
    inputBoxY0.setOutlineColor(sf::Color::Black);
    inputBoxY0.setOutlineThickness(2);
    sf::Text inputTextY0("", font, 20);
    inputTextY0.setPosition(0, 255);
    inputTextY0.setFillColor(sf::Color::Black);
    sf::RectangleShape buttonY0(sf::Vector2f(80, 30));
    buttonY0.setPosition(190, 255);
    buttonY0.setFillColor(sf::Color(180, 180, 180));
    buttonY0.setOutlineColor(sf::Color::Black);
    buttonY0.setOutlineThickness(2);
    sf::Text buttonTextY0("applica", font, 18);
    buttonTextY0.setPosition(198, 257);
    buttonTextY0.setFillColor(sf::Color::Black);
    //theta0
    sf::Text outputTextTheta0("t0: ", font, 30);
    outputTextTheta0.setPosition(15, 295);
    outputTextTheta0.setFillColor(sf::Color::Black);
    sf::RectangleShape inputBoxTheta0(sf::Vector2f(100, 30));
    inputBoxTheta0.setPosition(75, 300);
    inputBoxTheta0.setFillColor(sf::Color(180, 180, 180));
    inputBoxTheta0.setOutlineColor(sf::Color::Black);
    inputBoxTheta0.setOutlineThickness(2);
    sf::Text inputTextTheta0("", font, 20);
    inputTextTheta0.setPosition(0, 300);
    inputTextTheta0.setFillColor(sf::Color::Black);
    sf::RectangleShape buttonTheta0(sf::Vector2f(80, 30));
    buttonTheta0.setPosition(190, 300);
    buttonTheta0.setFillColor(sf::Color(180, 180, 180));
    buttonTheta0.setOutlineColor(sf::Color::Black);
    buttonTheta0.setOutlineThickness(2);
    sf::Text buttonTextTheta0("applica", font, 18);
    buttonTextTheta0.setPosition(198, 302);
    buttonTextTheta0.setFillColor(sf::Color::Black);
    //lancio singolo
    sf::RectangleShape buttonSingle(sf::Vector2f(80, 30));
    buttonSingle.setPosition(75, 370);
    buttonSingle.setFillColor(sf::Color(180, 180, 180));
    buttonSingle.setOutlineColor(sf::Color::Black);
    buttonSingle.setOutlineThickness(2);
    sf::Text buttonTextSingle(" lancia", font, 18);
    buttonTextSingle.setPosition(78, 372);
    buttonTextSingle.setFillColor(sf::Color::Black);

    //
    sf::RectangleShape separatingLine1(sf::Vector2f(2, 1600)); // Larghezza=spessore, Altezza=lunghezza
    separatingLine1.setPosition(500, 0);
    separatingLine1.setFillColor(sf::Color::Black);
    sf::RectangleShape separatingLine2(sf::Vector2f(1100,2)); // Larghezza=spessore, Altezza=lunghezza
    separatingLine2.setPosition(500, 600);
    separatingLine2.setFillColor(sf::Color::Black);
    sf::RectangleShape separatingLine3(sf::Vector2f(500, 2)); // Larghezza=spessore, Altezza=lunghezza
    separatingLine3.setPosition(0, 195);
    separatingLine3.setFillColor(sf::Color::Black);
    sf::RectangleShape separatingLine4(sf::Vector2f(2, 1600)); // Larghezza=spessore, Altezza=lunghezza
    separatingLine4.setPosition(500, 0);
    separatingLine4.setFillColor(sf::Color::Black);

    std::string userInput;
    bool inputActive = true;
    
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            
            /*if (event.type == sf::Event::TextEntered && inputActive) {
                if (event.text.unicode == '\b') {
                    if (!userInput.empty())
                        userInput.pop_back();
                } else if (event.text.unicode == '\r') {
                    outputText.setString("Hai scritto: " + userInput);
                    userInput.clear();
                } else if (event.text.unicode < 128) {
                    userInput += static_cast<char>(event.text.unicode);
                }
                inputText.setString(userInput);
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                button.setFillColor(sf::Color(100, 100, 100));
            }*/
        }
        //button1.update(window);
        window.clear(sf::Color(200,200,200));
        window.draw(rectangle1);
        window.draw(rectangle2);
        window.draw(separatingLine1); //
        window.draw(separatingLine2); 
        window.draw(separatingLine3); 
        window.draw(separatingLine4); 
        window.draw(inputBoxl);
        window.draw(buttonl); //
        window.draw(inputTextl);
        window.draw(outputTextl);
        window.draw(buttonTextl);
        window.draw(inputBoxR1);
        window.draw(buttonR1); //
        window.draw(inputTextR1);
        window.draw(outputTextR1);
        window.draw(buttonTextR1);
        window.draw(inputBoxR2); //
        window.draw(buttonR2);
        window.draw(inputTextR2);
        window.draw(outputTextR2);
        window.draw(buttonTextR2);
        window.draw(inputBoxY0); //
        window.draw(buttonY0);
        window.draw(inputTextY0);
        window.draw(outputTextY0);
        window.draw(buttonTextY0); 
        window.draw(inputBoxTheta0); //
        window.draw(buttonTheta0);
        window.draw(inputTextTheta0);
        window.draw(outputTextTheta0);
        window.draw(buttonTextTheta0);
        window.draw(buttonSingle); //
        window.draw(buttonTextSingle);
        window.draw(rectangleTry);
        
        window.display();
    }
}