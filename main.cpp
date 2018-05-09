#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "src/game.hpp"
#include "src/scenes/inGame.hpp"
int main()
{

    //Game game {};
    //int ret = game.run();
    //return ret;

    sf::RenderWindow window(sf::VideoMode(WIN_W, WIN_H), WIN_TITLE, sf::Style::Titlebar | sf::Style::Close);
    InGame IG;
    IG.run();
    while (window.isOpen())
    {
        // on inspecte tous les évènements de la fenêtre qui ont été émis depuis la précédente itération
        sf::Event event;
        while (window.pollEvent(event))
        {
            // évènement "fermeture demandée" : on ferme la fenêtre
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(IG);
        window.display();
    }


    return 0;

}
