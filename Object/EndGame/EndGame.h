#ifndef END_GAME_EXIST
#define END_GAME_EXIST

#include "../../modules/modules.h"

static const int GoodJobPosX = 109 ; 
static const int GoodJobPosY = ScreenHeight - 494 ; 
static const int GoodJobWidth = 800 ; 
static const int GoodJobHeight = 112 ; 

static const int ToMainMenuPosX = 300 ; 
static const int ToMainMenuPosY = ScreenHeight - 260 ; 
static const int ToMainMenuWidth = 152 ; 
static const int ToMainMenuHeight = 141 ; 

static const int PlayAgainPosX = 511 ; 
static const int PlayAgainPosY = ScreenHeight - 260 ;
static const int PlayAgainWidth = 152 ; 
static const int PlayAgainHeight = 141 ; 

static const int HighScoreWidth = 200 ; 
static const int HighScoreHeight = 80 ; 
static const int HighScorePosX = (ScreenWidth - HighScoreWidth) / 2 ;
static const int HighScorePosY = 0 ;

static const int ScoreTexturePosX = HighScorePosX + 20; 
static const int ScoretexturePosY = HighScoreHeight - 20; 
static const int ScoreTextureWidth = 140 ; 
static const int ScoreTextureHeight = 50 ;

class EndGame {
    public:
        EndGame() {
            Selection = NotChoose ;
            GoodJobRect = makeRect(GoodJobPosX , GoodJobPosY , GoodJobWidth , GoodJobHeight) ; 
            PlayAgainRect = makeRect(PlayAgainPosX , PlayAgainPosY , PlayAgainWidth , PlayAgainHeight) ; 
            ToMainMenuRect = makeRect(ToMainMenuPosX , ToMainMenuPosY , ToMainMenuWidth , ToMainMenuHeight) ;
            HighScoreRect = makeRect(HighScorePosX , HighScorePosY , HighScoreWidth , HighScoreHeight) ; 
            ScoreRect = makeRect(ScoreTexturePosX , ScoretexturePosY , ScoreTextureWidth , ScoreTextureHeight) ;
        } 

        void BeginEndGame () {
            Selection = NotChoose ;
            this->HighScore = 0 ; 

            std::string ScoreText = "Your score : " + std::to_string(RecentScore) ;
            this->ScoreTexture = CreateTextureFromString(ScoreText) ;

            std::ifstream ifs ("Score.txt") ;
            if (ifs.is_open()) ifs >> HighScore ;
            ifs.close() ;

            if (RecentScore > HighScore) {
                IsHighScore = true ; 
                std::ofstream ofs("Score.txt") ;
                ofs << RecentScore ; 
                ofs.close() ; 
            }
            else IsHighScore = false ;
        }

        bool IsChoose () {
            if (Selection == NotChoose) return false ;
            return true ; 
        }

        bool PlayAgain () {
            if (Selection == EnterPlayAgain) return true ; 
            return false ; 
        }

        void Process(SDL_Event &e) {            
            if (e.type == SDL_MOUSEBUTTONDOWN) {
                int X , Y ; 
                SDL_GetMouseState(&X , &Y) ;
                if (X >= PlayAgainPosX && 
                    Y >= PlayAgainPosY && 
                    X <= PlayAgainPosX + PlayAgainWidth && 
                    Y <= PlayAgainPosY + PlayAgainHeight) {
                        Selection = EnterPlayAgain ; 
                    }

                else if (X >= ToMainMenuPosX && 
                         Y >= ToMainMenuPosY &&
                         X <= ToMainMenuPosX + ToMainMenuWidth &&
                         Y <= ToMainMenuPosY + ToMainMenuHeight) {
                             Selection = EnterToMainMenu ; 
                         }
            }
        }

        void Render () {
            SDL_RenderCopy(gMainRenderer , BigMap , NULL , NULL) ; 
            SDL_RenderCopy(gMainRenderer , GoodJobText , NULL , &GoodJobRect) ; 
            SDL_RenderCopy(gMainRenderer , PlayAgainText , NULL , &PlayAgainRect) ; 
            SDL_RenderCopy(gMainRenderer , ToMainMenuText , NULL , &ToMainMenuRect) ;
            if (IsHighScore) SDL_RenderCopy(gMainRenderer , NewHighScoreText , NULL , &HighScoreRect) ; 
            SDL_RenderCopy(gMainRenderer , ScoreTexture , NULL , &ScoreRect) ;
        }

    private:
        SDL_Rect GoodJobRect , 
                 PlayAgainRect ,
                 ToMainMenuRect , 
                 ScoreRect , 
                 HighScoreRect ; 
        
        SDL_Texture* ScoreTexture ;
        int HighScore ;
        bool IsHighScore ; 

        enum {
            NotChoose,
            EnterPlayAgain,
            EnterToMainMenu
        } Selection ;
} ; 

#endif