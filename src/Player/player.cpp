#include "player.hpp"
#include "../objects/card.hpp"

Player::Player(){}

Player::Player(int position){
    m_position = position;
}

void Player::addACard(Card card, int posX, int posY){
    if (m_position == 0){   //bottom
        if (posX == 0 && posY == 0){
            card.setPosition((WIN_W/2) - card.getSprite().getGlobalBounds().width - 10, WIN_H - card.getSprite().getGlobalBounds().height * 2 - 20);

        }
        else if (posX == 1 && posY == 0){
            card.setPosition((WIN_W/2) + 10, WIN_H - card.getSprite().getGlobalBounds().height * 2 - 20);
        }
        else if (posX == 0 && posY == 1){
            card.setPosition((WIN_W/2) - card.getSprite().getGlobalBounds().width - 10,WIN_H - card.getSprite().getGlobalBounds().height - 10);
        }
        else{
            card.setPosition((WIN_W/2) + 10,WIN_H - card.getSprite().getGlobalBounds().height - 10);
        }


    }

    else if (m_position == 2){ //top
        card.rotate(180.0f);
        if (posX == 0 && posY == 0){
            card.setPosition((WIN_W/2) + card.getSprite().getGlobalBounds().width + 10, card.getSprite().getGlobalBounds().height * 2 + 20);

        }
        else if (posX == 1 && posY == 0){
            card.setPosition((WIN_W/2)- 10, card.getSprite().getGlobalBounds().height * 2 + 20);
        }
        else if (posX == 0 && posY == 1){
            card.setPosition((WIN_W/2) + card.getSprite().getGlobalBounds().width + 10,card.getSprite().getGlobalBounds().height + 10);
        }
        else{
            card.setPosition((WIN_W/2)- 10,card.getSprite().getGlobalBounds().height + 10);
        }


    }

    else if (m_position == 3){ //Left
        card.rotate(90.0f);
        if (posX == 0 && posY == 0){
            card.setPosition(card.getSprite().getGlobalBounds().width *2 + 20,(WIN_H/2) - card.getSprite().getGlobalBounds().height -10);

        }
        else if (posX == 1 && posY == 0){
            card.setPosition(card.getSprite().getGlobalBounds().width *2 + 20,(WIN_H/2) + 10);
        }
        else if (posX == 0 && posY == 1){
            card.setPosition(card.getSprite().getGlobalBounds().width + 10,(WIN_H/2) - card.getSprite().getGlobalBounds().height -10);
        }
        else{
            card.setPosition(card.getSprite().getGlobalBounds().width + 10,(WIN_H/2) + 10);
        }

    }

    else if (m_position == 1){ //Right
    card.rotate(270.0f);
        if (posX == 0 && posY == 0){
            card.setPosition(WIN_W - card.getSprite().getGlobalBounds().width * 2 - 20,(WIN_H/2) + card.getSprite().getGlobalBounds().height + 10);

        }
        else if (posX == 1 && posY == 0){
            card.setPosition(WIN_W - card.getSprite().getGlobalBounds().width * 2 - 20,(WIN_H/2)- 10);
        }
        else if (posX == 0 && posY == 1){
            card.setPosition(WIN_W - card.getSprite().getGlobalBounds().width - 10,(WIN_H/2) + card.getSprite().getGlobalBounds().height + 10);
        }
        else{
            card.setPosition(WIN_W - card.getSprite().getGlobalBounds().width - 10,(WIN_H/2)- 10);
        }

    }
    this->carre[posX][posY] = card;
}

/*bool Player::haveCard(){
    Card carte = carre[0][0];
    if (carre[0][0] != nullptr){
        return true;
    }
}*/

Card Player::changeCard(Card card,int x,int y){
    Card c = carre[x][y];
    addACard(card,x,y);
    return c;
}

Card& Player::getCard(int x, int y){

    return carre[x][y];

}

int Player::getPosition(){
    return m_position;
}

Package& Player::choosePackage(Package& pVerso,Package& pRecto){}
Player::pos Player::selectedCard(Card& activeCard){}
