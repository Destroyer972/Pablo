#ifndef INGAME_HPP_INCLUDED
#define INGAME_HPP_INCLUDED

#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <string>
#include <iostream>
#include <array>


#include "../abstract/container.hpp"
#include "../objects/card.hpp"
#include "../objects/package.hpp"
#include "../constants.hpp"
#include "../Player/player.hpp"
#include "../Player/person.hpp"
#include "../Player/bot.hpp"
#include "../../debug.hpp"
#include "../abstract/scene.hpp"

class InGame : public Scene{
private:

    Container<sf::Texture> textures;
    sf::Clock clock;
    std::vector<Card> cardArray;
    Package p;
    Package pRecto;
    Card activeCard;
    std::vector<Card> activeCardVec;
    std::vector<Player::pos> activeCardPos;
    int const nbPlayer = 4;
    std::array<Player::Ptr,4> players;
    sf::Texture textureCardArray[52];
    sf::Texture tempTexture;


    void endOfRound();
    static int compareHandOfPlayer(std::array<Player::Ptr,4>&); //return the ID of the player who have the hand with least point

    //methodes

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
    GameState gameState;

    bool nextPlayer;
    int unloadTexture = 0;
    bool canSayPablo;
    bool saidPablo;
    int lastPlayerID = 100;

    struct position{
        float x;
        float y;
    };

    int ID;
    float roation;
    position packagePosition;
    position cardCoord;
    Player::pos cardPosition;
    std::array<std::array<position,4>,4> cardPositionArray;

public:

    InGame();

    int run();

    void handle_std_events(sf::Event& event);
    void handle_animation();
    //Virtual functions
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    virtual void update() const{};





};

#endif // INGAME_HPP_INCLUDED
