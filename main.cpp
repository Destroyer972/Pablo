#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "src/game.hpp"
#include "src/scenes/inGame.hpp"
int main()
{

    Game game {};
    int ret = game.run();
    return ret;

}
