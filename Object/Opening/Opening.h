#ifndef OPENING_EXIST
#define OPENING_EXIST

#include "../../modules/modules.h"

static const int StartPosX = 391 ;
static const int StartPosY = ScreenHeight - 240 ; 
static const int StartWidth = 230 ;
static const int StartHeight = 67 ; 

static const int ExitPosX = 391 ; 
static const int ExitPosY = ScreenHeight - 132 ; 
static const int ExitWidth = 230 ; 
static const int ExitHeight = 67 ; 

class OpeningGame {
    public:
        OpeningGame () {
            Selection = NotChoose ; 
        }

        void Init() {
            Selection = NotChoose ; 
        }

        bool IsSelect () {
            if (Selection == NotChoose) return false ; 
            return true ; 
        }

        bool IsStart () {
            if (Selection == EnterStart) return true ; 
            return false ; 
        }

        void Process(SDL_Event e) {
            if (e.type == SDL_MOUSEBUTTONDOWN) {
                int X , Y ; 
                SDL_GetMouseState(&X , &Y) ;
                if (X >= StartPosX && 
                    Y >= StartPosY && 
                    X <= StartPosX + StartWidth && 
                    Y <= StartPosY + StartHeight) {
                        Selection = EnterStart ; 
                    }

                else if (X >= ExitPosX && 
                         Y >= ExitPosY &&
                         X <= ExitPosX + ExitWidth &&
                         Y <= ExitPosY + ExitHeight) {
                             Selection = EnterExit ; 
                         }
            }
        }

        void Render() {
            SDL_RenderCopy(gMainRenderer , OpeningTexture , NULL , NULL) ;
        }

    private:
        enum {
            NotChoose,
            EnterStart,
            EnterExit 
        } Selection ; 
} ; 

#endif