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

    #define BUTTON_TEXT_SIZE 51

    #define TAB_END -1000000

    #define INVINCIBILITY_FRAME 120

    char const ENTER('¤');

    //Les fonctions des boutons
    enum{F_QUIT, F_GAME, F_OPTIONS, F_DIFFICULTY_CHOICE, F_SET_DIFFICULTY, F_SCORES_TABLE, F_SWITCH_MISSILES, F_SWITCH_DEBRIS, F_USE_DEBUG_ROOM};

    //Les paramètres du jeu
    enum{P_MISSILES_ON, P_DEBRIS_ON, P_PARAMETER_NUMBER};

    //Les paramètres des menus
    enum{IS_MAIN_MENU, DELETE_SCREENSHOT, MENU_PARAMETER_NUMBER};

    //Pour les vecteur et les coordonnées en général
    enum{X,Y,NORM};

    //La largeure et la hauteur
    enum{W,H};

    //Pour définir le "l'original" et le "modifiable"
    enum{PREVIOUS,CURRENT};

    //explicite
    enum{TOP,BOTTOM,LEFT,RIGHT,PRIME};
    //explicite
    enum{UP,DOWN};

    //Pour le dash de bobstyle
    enum{BEGIN,END};

    //Les tailles des débris
    enum{TINY,SMALL,MEDIUM,BIG,RANDOM};

    //les modes de difficulté
    enum{TOO_EASY,EASY,INTERMEDIATE,HARD,UNFAIR};

    //Les modes de Handler
    enum{GAME,MENU,WRITE};

    //Les type des entités
    enum{ENTITY,BOBSTYLE,DEBRIS,CLOUD,PROJECTILE,HOMING_MISSILE,MAX_ENTITY_NUMBER};

    //Les paramètres des entités
    enum{DEBUG_MODE,ALIVE,IN_SCREEN,MOTION,COLLISIONNABLE,ANIMATED,BOOMERANG,IS_ON_BORDER,ENTITY_PRAMAMETER_NUMBER};

#endif // CONSTANTS_H_INCLUDED
