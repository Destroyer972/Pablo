#ifndef DEF_GAME
#define DEF_GAME

#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <string>
#include <iostream>
#include <array>

#include "scenes/inGame.hpp"

#include "abstract/container.hpp"
#include "objects/card.hpp"
#include "objects/package.hpp"
#include "constants.hpp"
#include "Player/player.hpp"
#include "Player/person.hpp"
#include "Player/bot.hpp"

class Game{

private:
    //variables
    sf::RenderWindow window;
    sf::Clock clock;
    InGame IG;
    sf::Drawable& activeScene;

    //methodes
    void handle_std_events(sf::Event& event);
    void render();
    void update_fps(sf::Time, int&);




public:
    Game();
    int run();


};

#endif // DEF_GAME
