#include "package.hpp"
#include <iostream>
Package::Package(){}

Package::Package(std::vector<Card> cardArray, State state,sf::Texture& bkgTexture){

    m_cardArray = cardArray;
    m_state = state;

    if (state==State::Verso){
        //m_texture.loadFromFile("assets/Cards/bkg-card.png");

        m_sprite.setTexture(bkgTexture);
    }
    else{
        if (m_cardArray.size() > 0){
            m_texture = m_cardArray.front().getTexture();
            m_sprite.setTexture(m_texture);
        }

    }

    m_sprite.setScale(.4f,.4f);

    this->setPosition(10,10);

}

void Package::shuffling(){
srand(time(0));
	int i = 0;
	Card temp;
	int nombreTire;
	int const taille = this->m_cardArray.size();

	for (i = 0; i < taille-1; i++) {
		nombreTire = rand() % (taille-1);
		temp = m_cardArray[i];
		m_cardArray[i] = m_cardArray[nombreTire];
		m_cardArray[nombreTire] = temp;

	}
}

void Package::setPosition(int posX,int posY){
    m_posX = posX;
    m_posY = posY;
    m_sprite.move(m_posX,m_posY);
}

const sf::Sprite& Package::getSprite() const{
    return m_sprite;
}

float Package::getWidth(){
    return this->m_sprite.getGlobalBounds().width;
}

float Package::getHeight(){
    return this->m_sprite.getGlobalBounds().height;
}

Card& Package::getFirstCard(){
    return this->m_cardArray.front();
}

Card Package::takeFirstCard(){

        Card card = this->getFirstCard();
        this->m_cardArray.erase(m_cardArray.begin());
        return card;

}

void Package::addCard(Card card){
    m_cardArray.insert(m_cardArray.begin(),card);
}

int Package::getSize(){
    return m_cardArray.size();
}

void Package::loadSprite(){
    if (m_cardArray.size() > 0){
            m_texture = m_cardArray.front().getTexture();
            m_sprite.setTexture(m_texture);
        }
}

std::vector<Card> Package::generatePackage(State state,Container<sf::Texture>& textures){

    std::vector<Card> cardArray;
    Color col;
    for (int j=0;j<=3;j++){
        DebugLog(SH_SPE,std::to_string(j));
        for(int i=1;i <= 13;i++){
            col = static_cast<Color>(j);

            //cardArray.emplace_back(col,i,state,textures.get(std::to_string(i) + "-" + Card::colorToString(col)),textures.get("bkg-card"));
            cardArray.emplace(cardArray.begin(),col,i,state,textures.get(std::to_string(i) + "-" + Card::colorToString(col)),textures.get("bkg-card"));
            //cardArray.emplace_back(col,i,state,textures.get("2-carreau"),textures.get("bkg-card"));
            cardArray.front().setPosition(10,10);
        }

    }

    return cardArray;
}

void Package::clear(){
    this->m_cardArray.clear();
}

void Package::returnPackage(){
    for (unsigned int i=0;i<m_cardArray.size();i++){
        m_cardArray[i].returnCard();
    }
}

void Package::transferCard(Package& packageA,Package& packageB){

    packageB.m_cardArray = packageA.m_cardArray;


}
