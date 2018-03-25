#ifndef DEF_GAME
#define DEF_GAME

#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <string>
#include <iostream>
#include <array>



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
    Container<sf::Texture> textures;
    sf::Clock clock;
    std::vector<Card> cardArray;
    Package p;
    Package pRecto;
    Card activeCard;
    int const nbPlayer = 4;
    //Player* players[4];
    std::array<Player::Ptr,4> players;
    sf::Texture textureCardArray[52];
    sf::Texture tempTexture;


    //methodes
    void handle_std_events(sf::Event& event);
    void render();
    void update_fps(sf::Time, int&);
    void cardDistribution(Package& package);
    void generatePlayers();

    bool drawCard;
    bool drawPackageRecto;
    bool drawPackageVerso;
    bool hasClickedPackage;
    bool havePackageRecto;
    bool havePackageVerso;
    bool beginParty;
    bool canPlay = true;
    int activePlayerID;
    std::unique_ptr<std::unique_ptr<Player>> activePlayer = 0;
    bool nextPlayer;
    int unloadTexture = 0;


public:
    Game();
    int run();


};

#endif // DEF_GAME
