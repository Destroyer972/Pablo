#ifndef DEF_PLAYER
#define DEF_PLAYER

#include "../objects/card.hpp"
#include "../objects/package.hpp"
#include <iostream>
#include <array>

class Player{

private:
    //std::array<std::array<Card,2>,2> carre;
    std::vector<std::vector<Card>> carre;
    int m_position;

public:
    Player();
    Player(int position);
    void addACard(Card card, int posX,int posY);
    Card changeCard(Card card,int x,int y);
    bool haveCard();
    Card& getCard(int x, int y);
    int getPosition();


    struct pos{
        int x;
        int y;
    };
    using Ptr = std::unique_ptr<Player>;

    //virtual function
    virtual Package& choosePackage(Package& pVerso,Package& pRecto);
    virtual Player::pos selectedCard(Card& activeCard);
};

#endif // DEF_PLAYER
