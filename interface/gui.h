#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
using namespace sf;

class AppGui {
private:
    RenderWindow* window = new RenderWindow(VideoMode(500, 500), "BlockChain05");

public:
    AppGui() = default;
    ~AppGui() { delete window; }

    void init_visualize_app() {
        Font font;
        if (!font.loadFromFile("./assets/arial.ttf"))
            throw "Don't load font...";

        Text text;
        text.setFont(font);
        text.setString("GUI all right");
        text.setCharacterSize(40);
        text.setFillColor(Color::White);
        text.setStyle(Text::Bold);
        text.setPosition(window->getSize().x / 2 - text.getLocalBounds().width / 2,
                         window->getSize().y / 2 - text.getLocalBounds().height / 2);

        Clock clock;
        bool visible = true;

        while (window->isOpen()) {
            Event event;
            while (window->pollEvent(event))
            {
                if (event.type == Event::Closed)
                    window->close();
            }

            Time elapsed = clock.getElapsedTime();
            if (elapsed.asSeconds() >= 0.1)
            {
                visible = !visible;
                clock.restart();
            }

            if (visible)
                text.setFillColor(Color::White);
            else
                text.setFillColor(Color::Yellow);

            window->clear();
            window->draw(text);
            window->display();
        }
    }
};