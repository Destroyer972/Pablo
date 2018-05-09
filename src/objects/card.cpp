#include "card.hpp"
#include <iostream>
Card::Card(){


}

Card::Card(Color couleur, int number, State state, sf::Texture& texture,sf::Texture& bkgTexture){
    this->m_couleur = couleur;
    this->m_number = number;
    this->m_state = state;
    this->m_texture = texture;
    this->m_bkgTexture = bkgTexture;
    this->m_sprite.setTexture(texture);
    this->m_bkgSprite.setTexture(bkgTexture);


    if (number <= 10){value = number;}
    else if (number == 13 && couleur == Color::Pique){value = 0;}
    else {value = 10;}

    m_sprite.setScale(.4f,.4f);
    m_sprite.setPosition(this->posX,this->posY);
    m_bkgSprite.setScale(.4f,.4f);
    m_bkgSprite.setPosition(this->posX,this->posY);
    }

Card::Card(Color couleur,int number,State state){
    this->m_couleur = couleur;
    this->m_number = number;
    this->m_state = state;


}

Card::~Card(){}

void Card::setPosition(int X, int Y){
    this->posX = X;
    this->posY = Y;
    this->m_sprite.setPosition(posX,posY);
    this->m_bkgSprite.setPosition(posX,posY);

}

void Card::rotate(float angle){
    this->m_sprite.setRotation(angle);
    this->m_bkgSprite.setRotation(angle);
}

void Card::returnCard(){
    if(m_state == State::Recto){m_state = State::Verso;}
    else{m_state = State::Recto;}
}

const Color Card::getColor(){
    return this->m_couleur;
}

const int Card::getNumber(){
    return this->m_number;
}

const sf::Texture& Card::getTexture(){
    return m_texture;
}

const void Card::presentation(){
    DebugLog(SH_INFO," " + std::to_string(this->m_number) + " de " + colorToString(this->m_couleur));
}

const sf::Sprite& Card::getSprite() const{
    if (m_state == State::Recto){return m_sprite;}
    else {return m_bkgSprite;}
}

const int Card::getValue(){
    return value;
}

bool operator==(Card const& a,Card const& b){
    if(a.m_number == b.m_number && a.m_couleur == b.m_couleur){return true;}else{return false;}
}



