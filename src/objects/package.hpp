#ifndef DEF_PACKAGE
#define DEF_PACKAGE

#include <SFML/Graphics.hpp>

#include "string"
#include "../constants.hpp"
#include "card.hpp"
#include "../abstract/container.hpp"
#include "../../debug.hpp"

class Package{
private:
     std::vector<Card> m_cardArray;
     sf::Texture m_texture;
     sf::Sprite m_sprite;
     State m_state;


     int width = CARD_WIDTH;
     int height = CARD_HEIGHT;
     int m_posX;
     int m_posY;




public:
    Package();
    Package(std::vector<Card>, State,sf::Texture& bkgTexture);
    void shuffling();
    void setPosition(int posX,int posY);
    sf::Sprite& getSprite();
    float getWidth();
    float getHeight();
    Card& getFirstCard();
    Card takeFirstCard();
    void addCard(Card card);
    int getSize();
    void loadSprite();
    void clear();
    void returnPackage();



    //statics functions
    static std::vector<Card> generatePackage(State state,Container<sf::Texture>& textures);
    static void transferCard(Package& packageA,Package& packageB);



};

#endif // DEF_PACKAGE
