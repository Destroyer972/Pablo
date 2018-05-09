#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "game.hpp"
#include "scenes/inGame.hpp"

#include "../debug.hpp"
#include "objects/card.hpp"
#include "objects/package.hpp"
#include <iostream>
#include <ctime>
#include <string>
#include <cstdlib>
#include <clocale>
#include <string>
#include <sstream>



Game::Game() :
     window(sf::VideoMode(WIN_W, WIN_H), WIN_TITLE, sf::Style::Titlebar | sf::Style::Close),activeScene(IG)
    {
    IG.run();

    }




int Game::run(){
    int _fps_update = 0;
    sf::Event event;
    float timer =1.0f;

    while (window.isOpen())
    {
         sf::Time dt = this->clock.restart();

        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                    this->window.close();
                    break;

                default:
                    break;

            }
            //On dispatche les events

            this->handle_std_events(event);
        }

        this->window.clear();
        this->render();

        this->window.display();

         timer += 1.0f;
    }

    return 0;
}

void Game::render(){

    window.draw(IG);


}

void Game::handle_std_events(sf::Event& event){
    if (&activeScene == &IG){
        switch(event.type){
        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::Escape){
                DebugLog(SH_INFO,"Open pause menu");
                //Open the pause Menu
            }
        }
        IG.handle_std_events(event);

    }

}






