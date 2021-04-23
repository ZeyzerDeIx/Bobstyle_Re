#ifndef CONSTANTS_H_INCLUDED
#define CONSTANTS_H_INCLUDED

    #include <SDL2/SDL.h>
    #include <SDL2/SDL_ttf.h>
    #include <iostream>
    #include <cassert>
    #include <vector>
    #include <list>
    #include <string>
    #include <math.h>
    #include <sstream>
    #include <stdlib.h>
    #include <time.h>
    #include <fstream>
    #include <map>

    #define MILISEC_PER_FRAME 16 //nombre de milisecondes par frame (reglé pour 60 FPS actuellement)
    #define INFINITE 10000000000000000 //nombre theoriquement inateignable symbolisant l'infini

    //constantes cummulables
    #define FLAG_RIGHT 0x00000001
    #define FLAG_LEFT 0x00000010
    #define FLAG_UP 0x00000100
    #define FLAG_DOWN 0x00001000
    #define FLAG_NONE 0x00000000

    //hauteur de la bordure supperrieure
    #define TOP_BORDER_HIGHT 120
    #define BORDER_DISTANCE_SCORE 320

    //nombre de phase d'animation de bobstyle_truster
    #define BOBSTYLE_TRUSTER_PHASES 12

    #define BACK_SCREEN_COLOR_R 17
    #define BACK_SCREEN_COLOR_G 17
    #define BACK_SCREEN_COLOR_B 25

    char const ENTER('¤');

    //les fonctions des boutons
    enum{F_QUIT, F_GAME, F_OPTIONS, F_DIFFICULTY_CHOICE, F_SET_DIFFICULTY, F_SCORES_TABLE};

    enum{X,Y,NORM};
    enum{W,H};
    enum{PREVIOUS,CURRENT};
    enum{TOP,BOTTOM,LEFT,RIGHT,PRIME};
    enum{UP,DOWN};
    enum{DEBUG_MODE,ALIVE,IN_SCREEN,MOTION,COLLISIONNABLE,ANIMATED,BOOMERANG};
    enum{BEGIN,END};
    enum{TINY,SMALL,MEDIUM,BIG,RANDOM};
    enum{TOO_EASY,EASY,INTERMEDIATE,HARD,UNFAIR};
    enum{GAME,MENU,WRITE};
    enum{ENTITY,BOBSTYLE,DEBRIS,CLOUD,MISSILE,MAX_ENTITY_NUMBER};

#endif // CONSTANTS_H_INCLUDED
