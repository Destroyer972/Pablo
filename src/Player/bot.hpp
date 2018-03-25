#ifndef DEF_BOT
#define DEF_BOT

#include "player.hpp"
#include "../objects/package.hpp"

class Bot : public Player{

private:

public:
    Bot();
    Bot(int position);

    virtual Package& choosePackage(Package& pVerso,Package& pRecto);
    virtual Player::pos selectedCard(Card& activeCard);
    void test(int x);

};

#endif // DEF_BOT
