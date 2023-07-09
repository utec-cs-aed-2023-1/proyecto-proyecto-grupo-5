#include <SFML/Graphics.hpp>

using namespace sf;

// RenderWindow window(VideoMode::getFullscreenModes()[0], "BlockChain05");
RenderWindow window(VideoMode(1920, 1060), "BlockChain05");

enum Options {
    closed,         // cuando la app se cierra
    aboutUs,        // sobre nosotros
    initmenu,       // cuando muestra el menu incial
    visualizate,    // cuando muestra la vista de bloques
    profileUser,    // Vista del perfil de usuario
    changeTxForm    // vista del formulario para el cambio de transaccion
};