#include <SFML/Graphics.hpp>

// Usar el define RESOURCES_DIR
#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
#define RESOURCE_PATH TOSTRING(RESOURCES_DIR)

int main()
{
    auto window = sf::RenderWindow{ { 800u, 600u }, "Clon-1945" };
    window.setFramerateLimit(144);

    // Cargar la textura desde un archivo
    sf::Texture avion_sp;
    if (!avion_sp.loadFromFile(std::string(RESOURCE_PATH) + "/textures/aircraft_sprites/aircrafts.png")) {
        return -1; // Si la textura no se carga, salir del programa
    }

    // Crear un sprite y aplicarle la textura
    sf::Sprite avion;
    avion.setTexture(avion_sp);
    avion.setPosition(385,500);

    int frame = 0;
    sf::Clock clock; // para medir el tiempo
    sf::IntRect rectSourceSprite(0,0,32,32);

    // Game Loop (update del juego)
    while (window.isOpen())
    {

        //ReadInput Actualizar los estados de los perifericos de entrada
        for (auto event = sf::Event{};
             window.pollEvent(event);
                )
        {
            // CIERRA EL PROGRAMA CLICKEANDO EN X
            if (event.type == sf::Event::Closed)
                window.close();

            // Cierra la ventana con ESCAPE
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                }
            }
            //end events
        }

        // CMD Donde vamos a darnos cuenta que se apreto - Joystick
        if (clock.getElapsedTime().asSeconds() > 0.01f)
        {
            frame++;
            if(frame >= 4)
                frame = 0;
            rectSourceSprite.left = frame * 32;
            avion.setTextureRect(rectSourceSprite);
            clock.restart();
        }
        sf::Time elapsed = clock.restart();
        float deltaTime = elapsed.asSeconds();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) avion.move(-100.0f * deltaTime,0.0f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) avion.move(100.0f * deltaTime,0.0f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) avion.move(0.0f,-100.0f * deltaTime);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) avion.move(0.0f,100.0f * deltaTime);

        // Update
        // le vamos a dar con el joystick y update actualiza los estaedos del juego en si
        // o de los personajes

        window.clear(sf::Color::Blue);



        // Draw

        sf::CircleShape circle(150);
        circle.setFillColor(sf::Color::Green);
        circle.setPosition(375, 25);
        window.draw(circle);

        window.draw(avion);

        // Display - Flip
        window.display();
    }

    // Liberación del Juego

    return 0;
}
