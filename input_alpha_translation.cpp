#include "input_alpha_translation.h"

using namespace std;

string input_to_alpha(int input, bool shift)
{
    if(!shift)
    {
        switch(input)
        {
            case SDLK_a:
                return "a";
                break;
            case SDLK_b:
                return "b";
                break;
            case SDLK_c:
                return "c";
                break;
            case SDLK_d:
                return "d";
                break;
            case SDLK_e:
                return "e";
                break;
            case SDLK_f:
                return "f";
                break;
            case SDLK_g:
                return "g";
                break;
            case SDLK_h:
                return "h";
                break;
            case SDLK_i:
                return "i";
                break;
            case SDLK_j:
                return "j";
                break;
            case SDLK_k:
                return "k";
                break;
            case SDLK_l:
                return "l";
                break;
            case SDLK_m:
                return "m";
                break;
            case SDLK_n:
                return "n";
                break;
            case SDLK_o:
                return "o";
                break;
            case SDLK_p:
                return "p";
                break;
            case SDLK_q:
                return "q";
                break;
            case SDLK_r:
                return "r";
                break;
            case SDLK_s:
                return "s";
                break;
            case SDLK_t:
                return "t";
                break;
            case SDLK_u:
                return "u";
                break;
            case SDLK_v:
                return "v";
                break;
            case SDLK_w:
                return "w";
                break;
            case SDLK_x:
                return "x";
                break;
            case SDLK_y:
                return "y";
                break;
            case SDLK_z:
                return "z";
                break;
            case SDLK_SPACE:
                return " ";
                break;
            case SDLK_1:
                return "&";
                break;
            case SDLK_2:
                return "é";
                break;
            case SDLK_3:
                return "\"";
                break;
            case SDLK_4:
                return "'";
                break;
            case SDLK_5:
                return "(";
                break;
            case SDLK_6:
                return "-";
                break;
            case SDLK_7:
                return "è";
                break;
            case SDLK_8:
                return "_";
                break;
            case SDLK_9:
                return "ç";
                break;
            case SDLK_0:
                return "à";
                break;
            case SDLK_RIGHTPAREN:
                return ")";
                break;
            case SDLK_EQUALS:
                return "=";
                break;
            case SDLK_SEMICOLON:
                return ";";
                break;
            case SDLK_COLON:
                return ":";
                break;
            case SDLK_EXCLAIM:
                return "!";
                break;
            case SDLK_KP_1:
                return "1";
                break;
            case SDLK_KP_2:
                return "2";
                break;
            case SDLK_KP_3:
                return "3";
                break;
            case SDLK_KP_4:
                return "4";
                break;
            case SDLK_KP_5:
                return "5";
                break;
            case SDLK_KP_6:
                return "6";
                break;
            case SDLK_KP_7:
                return "7";
                break;
            case SDLK_KP_8:
                return "8";
                break;
            case SDLK_KP_9:
                return "9";
                break;
            case SDLK_KP_0:
                return "0";
                break;
            default:
                return "";
        }
    }
    else
    {
        if(input_to_alpha(input) != "")
        {
            string lettre("");
            lettre += toupper(input_to_alpha(input)[0]);
            return lettre;
        }
        else{return "";}
    }
}
