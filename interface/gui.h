
#include "box.h"
#include "block.h"
#include "required.h"
using namespace sf;

static const sf::VideoMode desktop = sf::VideoMode::getDesktopMode();

////////
const string VIEW_BLOCKS = "Visualizar BlockChain";
const string LIST_USERS = "Usuarios registrados";
const string VIEW_TXS = "Usuarios registrados";
const string UPDATE_TX = "Modificar";
////////

class AppGui {
private:
    std::string title_app = "Our BlockChain05!";
    Options options = Options::initmenu;
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

        // boton de visualizar en tabla los usuarios registrados con fecha y n° de transacciones
        Button* listUsers_button = new Button(
            LIST_USERS, window.getSize().x/2, window.getSize().y /2, Color::Cyan
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
                        break;
                    
                    case Event::MouseButtonPressed:
                        if (viewBlocks_button->on_click(event)) {}
                        else if (listUsers_button->on_click(event)) {}
                        
                        break;

                    default:
                        break;
                }
            }
            window.clear(sf::Color::Black);

            // visualizar
            window.draw(title->getText());
            viewBlocks_button->draw(window);
            listUsers_button->draw(window);

            window.display();
        }
        delete title;
    }

    void loadFileBlockChain(const string file) {

    }

    void insertFile() {

    }

    void set_username() {
        return;
    }


public:  //// para realizar testing sin acceso al backend de la app

    void init_visualize_app() {
        while (options != Options::closed) {
            switch (options) {
                case Options::visualizate:
                    VisualizateBlocks();
                    break;

                case Options::listingTxs:
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
        
        while (window.isOpen()) {
            Event event;
            while (window.pollEvent(event)) {
                if (event.type == Event::Closed) {
                    options = Options::closed;
                    return;
                }
            }
            window.clear(sf::Color::Black);

            // visualizar
            window.display();
        }
    }


    void ViewTransactions() {
        // boton para ver las transacciones al seleccionar un usuario
        Button* viewTransactions_button = new Button(
            VIEW_TXS, window.getSize().x/2, window.getSize().y /2 + 50, Color::Cyan
        );
        
        while (window.isOpen()) {
            Event event;
            while (window.pollEvent(event)) {
                if (event.type == Event::Closed) {
                    options = Options::closed;
                    return;
                }
            }
            // visualizar
            viewTransactions_button->draw(window);
            window.display();
        }
    }


    void updateTransaction() {
        // boton para actualizar transaction
        Button* updateTransaction_button = new Button(
            UPDATE_TX, window.getSize().x/2, window.getSize().y /2 + 100, Color::Cyan
        );

        while (window.isOpen()) {
            Event event;
            while (window.pollEvent(event)) {
                if (event.type == Event::Closed) {
                    options = Options::closed;
                    return;
                }
            }
            // visualizar
            updateTransaction_button->draw(window);
            window.display();
        }
    }
};