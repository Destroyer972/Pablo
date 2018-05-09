#ifndef DEF_CARD
#define DEF_CARD

#include <SFML/Graphics.hpp>
#include "../constants.hpp"
#include <iostream>
#include "../../debug.hpp"
#include <string>


class Card {
private:
    Color m_couleur;
    int m_number;
    int value;
    State m_state;
    sf::Texture m_texture;
    sf::Texture m_bkgTexture;
    sf::Sprite m_sprite;
    sf::Sprite m_bkgSprite;

    int width = CARD_WIDTH;
    int height = CARD_HEIGHT;
    int posX = ((WIN_W/2)-(width/2));
    int posY = ((WIN_H/2)-(height/2));




public:
    Card();
    Card(Color,int,State, sf::Texture&,sf::Texture& bkgTexture);
    Card(Color couleur,int number,State state);
    ~Card();


    void setPosition(int X, int Y);
    void rotate(float angle);
    void returnCard();

    const Color getColor();
    const int getNumber();
    const sf::Sprite& getSprite() const;
    const sf::Texture& getTexture();
    const void presentation();
    const int getValue();
    const float getX(){
        return m_bkgSprite.getPosition().x;
    }

    using Ptr = std::unique_ptr<Card>;

    friend bool operator==(Card const& a,Card const& b);
    static std::string colorToString(Color col){
        switch (col){
        case Color::Pique:
            return "Pique";
            break;
        case Color::Trefle:
            return "Trefle";
            break;
        case Color::Carreau:
            return "Carreau";
            break;
        case Color::Coeur:
            return "Coeur";
            break;
        default:
            return "";
            break;
            }
    }



};

#endif // DEF_CARD
