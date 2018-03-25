#include "bot.hpp"

Bot::Bot(){}

Bot::Bot(int position) : Player(position)
{}

Package& Bot::choosePackage(Package& pVerso,Package& pRecto){
    if(pRecto.getSize()>0){
        if(pRecto.getFirstCard().getValue() < 5){
            return pRecto;
        }else {return pVerso;}
    }else{return pVerso;}

}

Player::pos Bot::selectedCard(Card& activeCard){

    Player::pos pos;

    //Choisir ou mettre la carte et transmettre les coordonnes a x et y

    pos.x = 1;
    pos.y = 1;

    return pos;
}
