#ifndef DEF_CONSTANTS
#define DEF_CONSTANTS

#define DEV_MODE

#define DISPLAY_FPS_IN_TITLE 1

//window
#define WIN_W 1000
#define WIN_H 1000
#define WIN_TITLE "Pablo"


//Card

    //Number
#define As 1
#define Deux 2
#define Trois 3
#define Quatre 4
#define Cinq 5
#define Six 6
#define Sept 7
#define Huit 8
#define Neuf 9
#define Dix 10
#define Valet 11
#define Dame 12
#define Roi 13

enum class Number{
as,
deux,
trois,
quatre,
cinq,
six,
sept,
huit,
neuf,
dix,
valet,
dame,
roi

};

enum class State{
Recto,
Verso
};

enum class Color{
Coeur,
Trefle,
Carreau,
Pique
};



#define CARD_HEIGHT 10
#define CARD_WIDTH 5
#endif // DEF_CONSTANTS
