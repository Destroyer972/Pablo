#include "player.hpp"
#include "../objects/card.hpp"

Player::Player(){}

Player::Player(int position){
    m_position = position;
    //carre.push_back(std::vector<Card>(2));
    //carre.push_back(std::vector<Card>(2));
    carre[0][0] = 0;
    carre[0][1] = 0;
    carre[1][0] = 0;
    carre[1][1] = 0;

}

void Player::addACard(Card card, int posX, int posY){
    this->carre[posX][posY] = std::make_unique<Card>(card);
    Card &c = *carre[posX][posY]; //Card in the player's hand
    if (m_position == 0){   //bottom
        if (posX == 0 && posY == 0){
            c.setPosition((WIN_W/2) - c.getSprite().getGlobalBounds().width - 10, WIN_H - c.getSprite().getGlobalBounds().height * 2 - 20);

        }
        else if (posX == 1 && posY == 0){
            c.setPosition((WIN_W/2) + 10, WIN_H - c.getSprite().getGlobalBounds().height * 2 - 20);
        }
        else if (posX == 0 && posY == 1){
            c.setPosition((WIN_W/2) - c.getSprite().getGlobalBounds().width - 10,WIN_H - c.getSprite().getGlobalBounds().height - 10);
        }
        else{
            c.setPosition((WIN_W/2) + 10,WIN_H - c.getSprite().getGlobalBounds().height - 10);
        }


    }

    else if (m_position == 2){ //top
        c.rotate(180.0f);
        if (posX == 0 && posY == 0){
            c.setPosition((WIN_W/2) + c.getSprite().getGlobalBounds().width + 10, c.getSprite().getGlobalBounds().height * 2 + 20);

        }
        else if (posX == 1 && posY == 0){
            c.setPosition((WIN_W/2)- 10, c.getSprite().getGlobalBounds().height * 2 + 20);
        }
        else if (posX == 0 && posY == 1){
            c.setPosition((WIN_W/2) + c.getSprite().getGlobalBounds().width + 10,c.getSprite().getGlobalBounds().height + 10);
        }
        else{
            c.setPosition((WIN_W/2)- 10,c.getSprite().getGlobalBounds().height + 10);
        }


    }

    else if (m_position == 3){ //Left
        c.rotate(90.0f);
        if (posX == 0 && posY == 0){
            c.setPosition(c.getSprite().getGlobalBounds().width *2 + 20,(WIN_H/2) - c.getSprite().getGlobalBounds().height -10);

        }
        else if (posX == 1 && posY == 0){
            c.setPosition(c.getSprite().getGlobalBounds().width *2 + 20,(WIN_H/2) + 10);
        }
        else if (posX == 0 && posY == 1){
            c.setPosition(c.getSprite().getGlobalBounds().width + 10,(WIN_H/2) - c.getSprite().getGlobalBounds().height -10);
        }
        else{
            c.setPosition(c.getSprite().getGlobalBounds().width + 10,(WIN_H/2) + 10);
        }

    }

    else if (m_position == 1){ //Right
    c.rotate(270.0f);
        if (posX == 0 && posY == 0){
            c.setPosition(WIN_W - c.getSprite().getGlobalBounds().width * 2 - 20,(WIN_H/2) + c.getSprite().getGlobalBounds().height + 10);

        }
        else if (posX == 1 && posY == 0){
            c.setPosition(WIN_W - c.getSprite().getGlobalBounds().width * 2 - 20,(WIN_H/2)- 10);
        }
        else if (posX == 0 && posY == 1){
            c.setPosition(WIN_W - c.getSprite().getGlobalBounds().width - 10,(WIN_H/2) + c.getSprite().getGlobalBounds().height + 10);
        }
        else{
            c.setPosition(WIN_W - c.getSprite().getGlobalBounds().width - 10,(WIN_H/2)- 10);
        }

    }

}

/*bool Player::haveCard(){
    Card carte = carre[0][0];
    if (carre[0][0] != nullptr){
        return true;
    }
}*/

Card Player::changeCard(Card card,int x,int y){
    Card c = *carre[x][y];
    addACard(card,x,y);
    return c;
}

Card& Player::getCard(int x, int y){

    return *carre[x][y];

}

std::vector<Card> Player::changeCard_(Card card,int x,int y,std::vector<Player::pos> posArray){
    std::vector<Card> cards; //Tableau contenant les cartes du joueur a echanger
    Card c; //tempory card
    for (unsigned int i=0;i<posArray.size();i++){

        c = *carre[posArray[i].x][posArray[i].y];

        cards.push_back(c); //add the card in the hand of the player in the array of card to exchange
        carre[posArray[i].x][posArray[i].y] = std::move(nullptr); //


    }

    addACard(card,x,y);


    return cards;

}

int Player::getPosition(){
    return m_position;
}

const std::array<std::array<Card::Ptr,2>,2>& Player::returnSquare(){
    return carre;
}


