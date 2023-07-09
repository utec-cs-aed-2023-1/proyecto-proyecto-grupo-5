
#include "box.h"
#include "block.h"
using namespace sf;

static const sf::VideoMode desktop = sf::VideoMode::getDesktopMode();

////////
const string VIEW_BLOCKS = "Visualizar BlockChain";
const string ABOUT_US = "Sobre nosotros";
const string VIEW_TXS = "Usuarios registrados";
const string UPDATE_TX = "Modificar";
const string EXIT = "Atrás";
////////

class AppGui {
private:
    std::string title_app = "Our BlockChain05!";
    Options options = Options::initmenu;
    bool onEvent = false;
    // BlockChain* blockchain;

public:  /// inicialización

    AppGui()  {
        // blockchain = new BlockChain; 

        // configurar la posicion de la ventana en el centro del escritorio
        window.setFramerateLimit(60);
        window.setPosition(Vector2<int>(desktop.width / 2 - window.getSize().x / 2, 
                                        desktop.height / 2 - window.getSize().y / 2 - 20));

    }

    ~AppGui() {}

private:  //// funcionalidades

    void mainMenu() {
        // boton de visualizar los bloques
        Button* viewBlocks_button = new Button(
            VIEW_BLOCKS, window.getSize().x/2, window.getSize().y /2 - 50, Color::Cyan
        );

        Button* about_us_button = new Button(
            ABOUT_US, window.getSize().x/2, window.getSize().y /2 + 20, Color::Cyan
        );

        // Titilo de la app en el menu
        Message* title = new Message(
            title_app, desktop.width /2, 0, 40, Color::Yellow
        );

        while (window.isOpen()) {
            Event event;
            while (window.pollEvent(event)) {
                // en menu solo se cierra o se presiona un botón
                switch (event.type) {
                    case Event::Closed:
                        options = Options::closed;
                        return;
                    
                    case Event::MouseButtonPressed:
                        if (viewBlocks_button->on_click(window, event)) {
                            options = Options::visualizate;
                            onEvent = true;
                        }
                        else if (about_us_button->on_click(window, event)) {
                            options = Options::profileUser;
                            onEvent = true;
                        }
                        
                        break;

                    default:
                        break;
                }
            }
            window.clear(sf::Color::Black);

            if (onEvent) {
                delete viewBlocks_button;
                delete about_us_button;
                delete title;
                return;
            } 
            else {
                // visualizar
                window.draw(title->getText());
                viewBlocks_button->draw(window);
                about_us_button->draw(window);
                window.display();
            }
        }
    }

    void loadFileBlockChain(const string file) {

    }

    void insertFile() {

    }

    void set_username() {
        return;
    }

    void updateTransaction() {
    }


public:  //// para realizar testing sin acceso al backend de la app

    void init_visualize_app() {
        while (options != Options::closed) {
            onEvent = false;
            switch (options) {
                case Options::visualizate:
                    VisualizateBlocks();
                    break;

                case Options::profileUser:
                    ProfileUser();
                    break;

                case Options::initmenu:
                    mainMenu();
                    break;
            
                default:
                    break;
            }
        }
        window.close();
    }

private:   //// Views

    void VisualizateBlocks() {
        // boton para ver las transacciones al seleccionar un usuario en un bloque
        Button* view_profile_button = new Button(
            VIEW_TXS, window.getSize().x/2, window.getSize().y /2 + 50, Color::Cyan
        );

        while (window.isOpen()) {
            Event event;
            while (window.pollEvent(event)) {
                switch (event.type) {
                    case Event::Closed:
                        options = Options::closed;
                        return;
                    
                    case Event::MouseButtonPressed:
                        if (view_profile_button->on_click(window, event)) {
                            options = Options::profileUser;
                            onEvent = true;
                        }
                        
                        break;

                    default:
                        break;
                }
            }
            window.clear(sf::Color::Black);

            if (onEvent) {
                delete view_profile_button;
                return;
            } 
            else {
                // visualizar
                view_profile_button->draw(window);
                window.display();
            }
        }
    }

    void ProfileUser() {
        // boton para actualizar transaction
        Button* updateTransaction_button = new Button(
            UPDATE_TX, window.getSize().x/2, window.getSize().y /2 + 30, Color::Cyan
        );

        Button* exit_profile = new Button(
            EXIT, window.getSize().x/2 + 50, window.getSize().y /2 - 40, Color::Cyan
        );
        
        while (window.isOpen()) {
            Event event;
            while (window.pollEvent(event)) {
                switch (event.type) {
                    case Event::Closed:
                        options = Options::closed;
                        return;
                    
                    case Event::MouseButtonPressed:
                        if (exit_profile->on_click(window, event)) {
                            options = Options::visualizate;
                            onEvent = true;
                        }
                        
                        break;

                    default:
                        break;
                }
            }

            if (onEvent) {
                delete updateTransaction_button;
                delete exit_profile;
                return;
            } 
            else {
                // visualizar
                exit_profile->draw(window);
                updateTransaction_button->draw(window);
                window.display();
            }
        }
    }
};