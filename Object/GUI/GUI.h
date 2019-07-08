#ifndef GUI_EXIST
#define GUI_EXIST

#include "../../modules/modules.h"

static const int TextWidth = 160 ; 
static const int TextHeight = 40 ; 

class GUI {
    public: 
        GUI() ; 
        void Render() ; 
    private:  
        int GUIScore ; 
        SDL_Rect FrameRect ;  
        SDL_Rect BarOutRect ; 
        SDL_Rect BarInRect ;
        SDL_Rect ScoreRect ;
        SDL_Rect TextInTopRight ;  
        SDL_Rect FilterRect ; 
        SDL_Rect PauseTextRect ; 
        SDL_Rect PressEscRect ; 

        SDL_Texture* TextInTopRightTexture ;

        int AlphaNumberText = 0 ; 
} ; 

#endif