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
        canSayPablo = false;
        saidPablo = false;
        std::array<int,4> test;
        test[0] = 1;

        DebugLog(SH_SPE,std::to_string(test[0]));

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

            if (players[i]->returnSquare()[0][0] != nullptr){window.draw(players[i]->getCard(0,0).getSprite());}

            if (players[i]->returnSquare()[1][0] != nullptr){window.draw(players[i]->getCard(1,0).getSprite());}

            if (players[i]->returnSquare()[0][1] != nullptr){window.draw(players[i]->getCard(0,1).getSprite());}

            if (players[i]->returnSquare()[1][1] != nullptr){window.draw(players[i]->getCard(1,1).getSprite());}

        }

    if (drawCard){window.draw(activeCard.getSprite());}
    if (drawPackageRecto){window.draw(pRecto.getSprite());}

}

 void Game::handle_std_events(sf::Event& event){


    if (nextPlayer){
        if (activePlayerID==nbPlayer -1){
            activePlayerID=0;
            canPlay = true;
            if(!saidPablo){
                canSayPablo = true;
            }
        }
        else{
            activePlayerID++;
            canPlay = false;
            canSayPablo = false;
        }
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
            if (activePlayerID == lastPlayerID){
                endOfRound();

            }
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
        Package::transferCard(pRecto,p);
        pRecto.clear();
        p.shuffling();
        p.returnPackage();
        drawPackageVerso = true;
        havePackageVerso = true;
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
                activeCard.rotate(.0f);
                activeCard.returnCard();
                drawCard = true;
                hasClickedPackage = true;
                DebugLog(SH_SPE,"mark 1");

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
            if (this->players[0]->returnSquare()[0][0] != nullptr){ // We check if the card exist before check if the player click on this
                if (this->players[0]->getCard(0,0).getSprite().getGlobalBounds().contains(event.mouseButton.x,event.mouseButton.y) && hasClickedPackage == true){
                    activeCard.returnCard();
                    bool alpha = false;
                    Player::pos pos;
                    pos.x = pos.y = 0;
                    for (unsigned int i=0;i<activeCardPos.size();i++){
                        if (activeCardPos[i].x == pos.x && activeCardPos[i].y == pos.y){ // If the card was already selected
                            alpha = true;
                            break;
                        }
                    }if (!alpha){activeCardPos.push_back(pos);DebugLog(SH_SPE,"Card selected");}
                    activeCardVec = players[0]->changeCard_(activeCard,0,0,activeCardPos);
                    DebugLog(SH_INFO, "echange de carte entre la pioche et la carte en position 0;0");
                    for (int i=0;i<=activeCardVec.size()-1;i++){
                        activeCardVec[i].returnCard();
                        pRecto.addCard(activeCardVec[i]);
                    }
                    activeCardPos.clear();
                    activeCardVec.clear();
                    hasClickedPackage = false;
                    drawCard = false;
                    nextPlayer = true;

                    DebugLog(SH_SPE,"00000000");


                }
            }
            if (this->players[0]->returnSquare()[1][0] != nullptr){ // We check if the card exist before check if the player click on this
                if (this->players[0]->getCard(1,0).getSprite().getGlobalBounds().contains(event.mouseButton.x,event.mouseButton.y) && hasClickedPackage == true){
                    activeCard.returnCard();
                    bool alpha = false;
                    Player::pos pos;
                    pos.x = 1;pos.y = 0;
                    for (unsigned int i=0;i<activeCardPos.size();i++){
                        if (activeCardPos[i].x == pos.x && activeCardPos[i].y == pos.y){
                            alpha = true;
                            break;
                        }
                    }if (!alpha){activeCardPos.push_back(pos);DebugLog(SH_SPE,"Card selected");}
                    activeCardVec = players[0]->changeCard_(activeCard,1,0,activeCardPos);
                    DebugLog(SH_INFO, "echange de carte entre la pioche et la carte en position 1;0");
                    for (int i=0;i<=activeCardVec.size()-1;i++){
                        activeCardVec[i].returnCard();
                        pRecto.addCard(activeCardVec[i]);
                    }
                    activeCardPos.clear();
                    activeCardVec.clear();
                    hasClickedPackage = false;
                    drawCard = false;
                    nextPlayer = true;
                    DebugLog(SH_SPE,"11111110000");
                }
            }
            if (this->players[0]->returnSquare()[0][1] != nullptr){
                if (this->players[0]->getCard(0,1).getSprite().getGlobalBounds().contains(event.mouseButton.x,event.mouseButton.y) && hasClickedPackage == true){
                    activeCard.returnCard();
                    bool alpha = false;
                    Player::pos pos;
                    pos.x = 0;pos.y = 1;
                    for (unsigned int i=0;i<activeCardPos.size();i++){
                        if (activeCardPos[i].x == pos.x && activeCardPos[i].y == pos.y){
                            alpha = true;
                            break;
                        }
                    }if (!alpha){activeCardPos.push_back(pos);DebugLog(SH_SPE,"Card selected");}
                    activeCardVec = players[0]->changeCard_(activeCard,0,1,activeCardPos);
                    DebugLog(SH_INFO, "echange de carte entre la pioche et la carte en position 0;1");
                    for (int i=0;i<=activeCardVec.size()-1;i++){
                        activeCardVec[i].returnCard();
                        pRecto.addCard(activeCardVec[i]);
                    }
                    activeCardPos.clear();
                    activeCardVec.clear();
                    hasClickedPackage = false;
                    drawCard = false;
                    nextPlayer = true;

                }
            }
            if (this->players[0]->returnSquare()[1][1] != nullptr){
                if (this->players[0]->getCard(1,1).getSprite().getGlobalBounds().contains(event.mouseButton.x,event.mouseButton.y) && hasClickedPackage == true){
                    activeCard.returnCard();
                    bool alpha = false;
                    Player::pos pos;
                    pos.x = 1;pos.y = 1;
                    for (unsigned int i=0;i<activeCardPos.size();i++){
                        if (activeCardPos[i].x == pos.x && activeCardPos[i].y == pos.y){
                            alpha = true;
                            break;
                        }
                    }if (!alpha){activeCardPos.push_back(pos);DebugLog(SH_SPE,"Card selected");}
                    activeCardVec = players[0]->changeCard_(activeCard,1,1,activeCardPos);
                    DebugLog(SH_INFO, "echange de carte entre la pioche et la carte en position 1;1");
                    for (int i=0;i<=activeCardVec.size()-1;i++){
                        activeCardVec[i].returnCard();
                        pRecto.addCard(activeCardVec[i]);
                    }
                    activeCardPos.clear();
                    activeCardVec.clear();
                    hasClickedPackage = false;
                    drawCard = false;
                    nextPlayer = true;

                }
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
                DebugLog(SH_INFO,"The pack is empty");
                drawPackageVerso = false;
                havePackageVerso = false;
                Package::transferCard(pRecto,p);
                pRecto.clear();
                p.shuffling();
                p.returnPackage();
                drawPackageVerso = true;
                havePackageVerso = true;
            }
            }
            break;

        case sf::Mouse::Right:
            if (activePlayerID ==0){
                bool addPosInActivePos;
                bool addPosD;
                Player::pos pos;
                if (this->players[0]->returnSquare()[0][0] != nullptr){
                    if (this->players[0]->getCard(0,0).getSprite().getGlobalBounds().contains(event.mouseButton.x,event.mouseButton.y) && hasClickedPackage == true){
                        pos.x = 0; pos.y = 0;
                        if (activeCardPos.size() >0){
                            for(int i=0;i<=activeCardPos.size()-1;+i++){
                                if (activeCardPos[i].x == pos.x && activeCardPos[i].y == pos.y){

                                    activeCardPos.erase(activeCardPos.begin() + i);
                                    addPosInActivePos = false;
                                    DebugLog(SH_INFO, "carte en position 0;0 deselectionnee");
                                    break;
                                }else {addPosInActivePos = true;}


                            }
                        }else {addPosInActivePos = true;}
                        if (addPosInActivePos){

                            #ifndef DEV_MODE
                            if (activeCardPos.size() > 0){
                                for (int i=0;i<=activeCardPos.size()-1;i++){ //Check if the card number correspond with the card number of the other card
                                    if (players[0]->getCard(activeCardPos[i].x,activeCardPos[i].y).getNumber() != players[0]->getCard(0,0).getNumber()){
                                        DebugLog(SH_INFO,"Vous ne pouvez pas selectionner une carte avec un autre nombre");
                                        addPosD = false;break;
                                    }else{addPosD = true;}
                                }
                            }else{addPosD = true;}
                            if (addPosD){
                                activeCardPos.push_back(pos);
                                DebugLog(SH_INFO, "Carte en position 0;0 selectionnee");
                                DebugLog(SH_SPE,std::to_string(activeCardPos.size()) + " cartes ont ete selctionnees");
                            }
                            #else
                                activeCardPos.push_back(pos);
                                DebugLog(SH_INFO, "Carte en position 0;0 selectionnee");
                                DebugLog(SH_SPE,std::to_string(activeCardPos.size()) + " cartes ont ete selctionnees");
                            #endif // DEV_MODE


                        }

                    }
                }
                if (this->players[0]->returnSquare()[1][0] != nullptr){
                    if (this->players[0]->getCard(1,0).getSprite().getGlobalBounds().contains(event.mouseButton.x,event.mouseButton.y) && hasClickedPackage == true){
                        pos.x = 1; pos.y = 0;
                        if (activeCardPos.size() >0){
                            for(int i=0;i<=activeCardPos.size()-1;+i++){
                                if (activeCardPos[i].x == pos.x && activeCardPos[i].y == pos.y){

                                    activeCardPos.erase(activeCardPos.begin() + i);
                                    addPosInActivePos = false;
                                    DebugLog(SH_INFO, "carte en position 1;0 deselectionnee");
                                    break;
                                }else {addPosInActivePos = true;}


                            }
                        }else {addPosInActivePos = true;}
                        if (addPosInActivePos){
                            #ifndef DEV_MODE
                            if (activeCardPos.size() > 0){
                                for (int i=0;i<=activeCardPos.size()-1;i++){ //Check if the card number correspond with the card number of the other card
                                    if (players[0]->getCard(activeCardPos[i].x,activeCardPos[i].y).getNumber() != players[0]->getCard(1,0).getNumber()){
                                        DebugLog(SH_INFO,"You can't select a card with an other number");
                                        addPosD = false;
                                        break;
                                    }else{addPosD = true;}
                                }
                            }else{addPosD = true;}
                            if (addPosD){
                                activeCardPos.push_back(pos);
                                DebugLog(SH_INFO, "Carte en position 1;0 selectionnee");
                                DebugLog(SH_SPE,std::to_string(activeCardPos.size()) + " cartes ont ete selctionnees");
                            }
                            #else
                                activeCardPos.push_back(pos);
                                DebugLog(SH_INFO, "Carte en position 0;0 selectionnee");
                                DebugLog(SH_SPE,std::to_string(activeCardPos.size()) + " cartes ont ete selctionnees");
                            #endif // DEV_MODE


                        }
                    }
                }

                if (this->players[0]->returnSquare()[0][1] != nullptr){
                    if (this->players[0]->getCard(0,1).getSprite().getGlobalBounds().contains(event.mouseButton.x,event.mouseButton.y) && hasClickedPackage == true){
                            DebugLog(SH_SPE,"testttt");
                        pos.x = 0; pos.y = 1;
                        if (activeCardPos.size() >0){
                            for(int i=0;i<=activeCardPos.size()-1;+i++){
                                if (activeCardPos[i].x == pos.x && activeCardPos[i].y == pos.y){

                                    activeCardPos.erase(activeCardPos.begin() + i);
                                    addPosInActivePos = false;
                                    DebugLog(SH_INFO, "carte en position 0;1 deselectionnee");
                                    break;
                                }else {addPosInActivePos = true;}


                            }
                        }else {addPosInActivePos = true;}

                        if (addPosInActivePos){
                            #ifndef DEV_MODE
                            if (activeCardPos.size() > 0){
                                for (int i=0;i<=activeCardPos.size()-1;i++){ //Check if the card number correspond with the card number of the other card
                                    if (players[0]->getCard(activeCardPos[i].x,activeCardPos[i].y).getNumber() != players[0]->getCard(0,1).getNumber()){
                                        DebugLog(SH_INFO,"You can't select a card with an other number");
                                        addPosD = false;break;
                                    }else{addPosD = true;}
                                }
                            }else{addPosD = true;}
                            if (addPosD){
                                activeCardPos.push_back(pos);
                                DebugLog(SH_INFO, "Carte en position 0;1 selectionnee");
                                DebugLog(SH_SPE,std::to_string(activeCardPos.size()) + " cartes ont ete selctionnees");
                            }
                            #else
                                activeCardPos.push_back(pos);
                                DebugLog(SH_INFO, "Carte en position 0;0 selectionnee");
                                DebugLog(SH_SPE,std::to_string(activeCardPos.size()) + " cartes ont ete selctionnees");
                            #endif // DEV_MODE


                        }
                    }
                }

                if (this->players[0]->returnSquare()[1][1] != nullptr){
                    if (this->players[0]->getCard(1,1).getSprite().getGlobalBounds().contains(event.mouseButton.x,event.mouseButton.y) && hasClickedPackage == true){
                        pos.x = 1;
                        pos.y = 1;
                        if (activeCardPos.size() >0){
                            for(int i=0;i<=activeCardPos.size()-1;+i++){
                                if (activeCardPos[i].x == pos.x && activeCardPos[i].y == pos.y){
                                        activeCardPos.erase(activeCardPos.begin()+i);
                                        addPosInActivePos = false;
                                        DebugLog(SH_INFO, "Carte en position 1;1 deselectionnee");
                                        break;
                                }else{addPosInActivePos = true;}


                            }
                        }else {addPosInActivePos = true;}
                        if (addPosInActivePos){
                            #ifndef DEV_MODE
                            if (activeCardPos.size() > 0){
                                for (int i=0;i<=activeCardPos.size()-1;i++){ //Check if the card number correspond with the card number of the other card
                                    if (players[0]->getCard(activeCardPos[i].x,activeCardPos[i].y).getNumber() != players[0]->getCard(1,1).getNumber()){
                                        DebugLog(SH_INFO,"You can't select a card with an other number");
                                        addPosD = false;break;
                                    }else{addPosD = true;}
                                }
                            }else{addPosD = true;}
                            if (addPosD){
                                activeCardPos.push_back(pos);
                                DebugLog(SH_INFO, "Carte en position 1;1 selectionnee");
                                DebugLog(SH_SPE,std::to_string(activeCardPos.size()) + " cartes ont ete selctionnees");
                            }
                            #else
                                activeCardPos.push_back(pos);
                                DebugLog(SH_INFO, "Carte en position 0;0 selectionnee");
                                DebugLog(SH_SPE,std::to_string(activeCardPos.size()) + " cartes ont ete selctionnees");
                            #endif // DEV_MODE
                        }
                    }
                }


            }


        default:
            break;

        }

        break;

    case sf::Event::KeyReleased:
        if (event.key.code == sf::Keyboard::P && canSayPablo){
            saidPablo = true;
            canSayPablo = false;
            lastPlayerID = nbPlayer -1;
            DebugLog(SH_INFO,"Player 0 say Pablo");
        }
        break;



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

void Game::endOfRound(){
    for(int i=0;i<=nbPlayer -1;i++){
        players[i]->getCard(0,0).returnCard();
        players[i]->getCard(1,0).returnCard();
        players[i]->getCard(0,1).returnCard();
        players[i]->getCard(1,1).returnCard();

    }
    int df = compareHandOfPlayer(players);
    DebugLog(SH_INFO,"Le joueur " + std::to_string(df) + " a gagne ! ");

}

int Game::compareHandOfPlayer(std::array<Player::Ptr,4>& playerArray){
    int ID = 0;
    int activeValue =0;
    int leastValue = 500;
    for (int i=0;i<=3;i++){
        activeValue+=playerArray[i]->getCard(0,0).getValue();
        activeValue+=playerArray[i]->getCard(1,0).getValue();
        activeValue+=playerArray[i]->getCard(0,1).getValue();
        activeValue+=playerArray[i]->getCard(1,1).getValue();

        if (activeValue < leastValue){leastValue = activeValue;ID = i;}


        activeValue = 0;

    }

    return ID;
}



