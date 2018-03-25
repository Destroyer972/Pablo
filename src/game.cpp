#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "game.hpp"

#include "../debug.hpp"
#include "objects/card.hpp"
#include "objects/package.hpp"
#include <iostream>
#include <ctime>
#include <string>
#include <cstdlib>
#include <clocale>
#include <string>
#include <sstream>



Game::Game() :
     window(sf::VideoMode(WIN_W, WIN_H), WIN_TITLE, sf::Style::Titlebar | sf::Style::Close)
    {
        int k = 0;
        //Card card = Card(Coeur,Roi, State::Verso,t);
        for (int i=0;i<=3;i++){

            for (int j=1;j<=13;j++){
                if (!tempTexture.loadFromFile("assets/Cards/" + std::to_string(j) + "-" + Card::colorToString(static_cast<Color>(i)) + ".png")){
                    tempTexture.loadFromFile("assets/Cards/2-carreau.png");
                    unloadTexture++;

                }

                textureCardArray[k] = tempTexture;
                textures.add(std::to_string(j) + "-" + Card::colorToString(static_cast<Color>(i)),tempTexture);

                k++;
            }

        }
        DebugLog(SH_ERR, std::to_string(unloadTexture) + " textures n'ont pas ete charges");
        //sf::Texture deuxCa;
        //deuxCa.loadFromFile("assets/Cards/2-carreau.png");

        //textures.add("2-carreau",deuxCa);


        sf::Texture bkg;
        bkg.loadFromFile("assets/Cards/bkg-card.png");
        textures.add("bkg-card",bkg);


        //card = Card(Color::Carreau,2,State::Verso,this->textures.get("2-carreau"));
        //cardArray.push_back(card);
        //p = Package(cardArray,State::Verso,textures.get("bkg-card"));
        p = Package(Package::generatePackage(State::Verso,textures),State::Verso,this->textures.get("bkg-card"));
        p.setPosition((WIN_W/2)-p.getWidth() - 10, (WIN_H/2)-(p.getHeight()/2));
        std::vector<Card> car;
        pRecto = Package(car,State::Recto,this->textures.get("bkg-card"));
        pRecto.setPosition((WIN_W/2) + 10, (WIN_H/2)-(p.getHeight()/2));

        generatePlayers();
        //player.getCard(0,0).presentation();

        drawCard = false;
        drawPackageRecto = false;
        hasClickedPackage = false;
        havePackageRecto = false;
        activePlayerID=0;
        nextPlayer = false;



        //activePlayer = players[0];
    }




int Game::run(){
    int _fps_update = 0;
    sf::Event event;
    beginParty = true;
    float timer =1.0f;
    p.shuffling();
    cardDistribution(p);
    players[0]->getCard(0,0).returnCard();
    players[0]->getCard(1,0).returnCard();
    drawCard = true;
    while (window.isOpen())
    {
         sf::Time dt = this->clock.restart();

        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                    this->window.close();
                    break;

                default:
                    break;

            }
            //On dispatche les events
            this->handle_std_events(event);
            //DebugLog(SH_SPE,"spe");
        }

        this->window.clear();
        this->render();
        this->window.display();

         timer += 1.0f;
    }

    return 0;
}

void Game::render(){
    if (drawPackageVerso){window.draw(p.getSprite());}

        for (int i=0;i<=nbPlayer -1;i++){
            window.draw(players[i]->getCard(0,0).getSprite());
            window.draw(players[i]->getCard(1,0).getSprite());
            window.draw(players[i]->getCard(0,1).getSprite());
            window.draw(players[i]->getCard(1,1).getSprite());

        }

    if (drawCard){window.draw(activeCard.getSprite());}
    if (drawPackageRecto){window.draw(pRecto.getSprite());}

}

 void Game::handle_std_events(sf::Event& event){


    if (nextPlayer){
        if (activePlayerID==nbPlayer -1){activePlayerID=0;canPlay = true;}else{activePlayerID++;canPlay = false;}
        nextPlayer = false;

    }
    if (activePlayerID>=1 && havePackageVerso){
        //it's a bot
        Package& pp = players[activePlayerID]->choosePackage(p,pRecto);
        activeCard = pp.takeFirstCard();
        if (&pp == &p){activeCard.returnCard();}
        activeCard.presentation();
        Player::pos pos = players[activePlayerID]->selectedCard(activeCard);
        activeCard.returnCard();
        activeCard = players[activePlayerID]->changeCard(activeCard,pos.x,pos.y);
        activeCard.returnCard();
        activeCard.presentation();
        pRecto.addCard(activeCard);
        drawCard = false;
        DebugLog(SH_INFO,"le joueur " + std::to_string(activePlayerID) + " a joue");
        nextPlayer = true;
        std::cout << std::to_string(pRecto.getSize()) << std::endl;
    }
    if (pRecto.getSize() > 0){
        drawPackageRecto = true;
        havePackageRecto = true;
        pRecto.loadSprite();
    }
    else if (pRecto.getSize() == 0){
        drawPackageRecto = false;
        havePackageRecto = false;

    }
    if (p.getSize()>0){
        drawPackageVerso = true;
        drawPackageVerso = true;
    }
    else if (p.getSize() == 0){
        drawPackageVerso = false;
        havePackageVerso = false;
    }

    switch(event.type){

    case sf::Event::MouseButtonReleased:
        switch (event.mouseButton.button) {
        case sf::Mouse::Left:

            if (activePlayerID ==0){
            if (this->p.getSprite().getGlobalBounds().contains(event.mouseButton.x,event.mouseButton.y) && !hasClickedPackage && canPlay && havePackageVerso) {
                    if (beginParty){players[0]->getCard(0,0).returnCard();players[0]->getCard(1,0).returnCard();beginParty = false;}
                activeCard = p.takeFirstCard();

                activeCard.setPosition((WIN_W/2)-p.getWidth() - 10, (WIN_H/2)-(p.getHeight()/2));
                activeCard.returnCard();
                drawCard = true;
                hasClickedPackage = true;
            }

            else if(havePackageRecto && !hasClickedPackage && canPlay){
                if (pRecto.getSprite().getGlobalBounds().contains(event.mouseButton.x,event.mouseButton.y)){
                    activeCard = pRecto.takeFirstCard();
                    activeCard.setPosition((WIN_W/2)-p.getWidth() - 10, (WIN_H/2)-(p.getHeight()/2)); //Position temporaire
                    activeCard.rotate(.0f);
                    DebugLog(SH_INFO,"take");
                    drawCard = true;
                    hasClickedPackage = true;

                }

            }

            if (this->players[0]->getCard(0,0).getSprite().getGlobalBounds().contains(event.mouseButton.x,event.mouseButton.y) && hasClickedPackage == true){
                activeCard.returnCard();
                activeCard = players[0]->changeCard(activeCard,0,0);
                DebugLog(SH_INFO, "echange de carte entre la pioche et la carte en position 0;0");
                activeCard.returnCard();
                pRecto.addCard(activeCard);
                hasClickedPackage = false;
                drawCard = false;
                nextPlayer = true;


            }
            else if (this->players[0]->getCard(1,0).getSprite().getGlobalBounds().contains(event.mouseButton.x,event.mouseButton.y) && hasClickedPackage == true){
                activeCard.returnCard();
                activeCard = players[0]->changeCard(activeCard,1,0);
                DebugLog(SH_INFO, "echange de carte entre la pioche et la carte en position 1;0");
                pRecto.addCard(activeCard);
                hasClickedPackage = false;
                drawCard = false;
                nextPlayer = true;
            }

            else if (this->players[0]->getCard(0,1).getSprite().getGlobalBounds().contains(event.mouseButton.x,event.mouseButton.y) && hasClickedPackage == true){
                activeCard.returnCard();
                activeCard = players[0]->changeCard(activeCard,0,1);
                DebugLog(SH_INFO, "echange de carte entre la pioche et la carte en position 1;0");
                pRecto.addCard(activeCard);
                hasClickedPackage = false;
                drawCard = false;
                nextPlayer = true;

            }
            else if (this->players[0]->getCard(1,1).getSprite().getGlobalBounds().contains(event.mouseButton.x,event.mouseButton.y) && hasClickedPackage == true){
                activeCard.returnCard();
                activeCard = players[0]->changeCard(activeCard,1,1);
                DebugLog(SH_INFO, "echange de carte entre la pioche et la carte en position 1;0");
                pRecto.addCard(activeCard);
                hasClickedPackage = false;
                drawCard = false;
                nextPlayer = true;

            }


            if (pRecto.getSize() > 0){
                drawPackageRecto = true;
                havePackageRecto = true;
                pRecto.loadSprite();
            }
            else if (pRecto.getSize() == 0){
                drawPackageRecto = false;
                havePackageRecto = false;

            }
            }





        default:
            break;
        }
    case sf::Event::KeyReleased:
        switch(event.key.code){
        case sf::Keyboard::A:
            if (activePlayerID >= 1){
                //it's a bot


            }
        default:
            break;




        }
        default:
            break;

    }

 }

 void Game::cardDistribution(Package& package){
    for (int i=0;i<=1;i++){
        for (int a = 0;a <= nbPlayer - 1;a++){
            players[a]->addACard(package.takeFirstCard(),i,0);
            //players[a]->getCard(i,0).presentation();
        }

    }
    for (int j=0;j<=1;j++){
        for (int b = 0;b<= nbPlayer - 1;b++){
            players[b]->addACard(package.takeFirstCard(),j,1);
        }
    }


 }

 void Game::generatePlayers(){
    players[0] = std::make_unique<Player>(0);
    for (int i = 1;  i<= nbPlayer -1;i++){
        players[i] = std::make_unique<Bot>(i);
        DebugLog(SH_INFO,"Joueur " + std::to_string(i) + " cree");



    }
}



