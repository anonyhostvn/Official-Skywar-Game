#include "Object/GUI/GUI.h"

GUI::GUI() {

    this->FrameRect = makeRect(FramePosX , FramePosY , FrameWidth , FrameHeight) ; 
    this->BarOutRect = makeRect(BarLifePosX , BarLifePosY , BarLifeWidth , BarLifeHeight) ; 
    this->BarInRect = makeRect(BarLifePosX + 4 , BarLifePosY + 4 , BarLifeWidth - 8 , BarLifeHeight - 8) ; 
    this->ScoreRect = makeRect(FramePosX + FrameWidth / 3 , FramePosY + FrameHeight / 2 , FrameWidth / 3 , FrameHeight / 3) ; 
    this->TextInTopRight = makeRect(ScreenWidth - TextWidth , 0 , TextWidth , TextHeight) ; 
    this->FilterRect = makeRect(0 , 0 , ScreenWidth , ScreenHeight) ; 
    this->PauseTextRect = makeRect(PauseTextPosX , PauseTextPosY , PauseTextWidth , PauseTextHeight) ;
    this->PressEscRect = makeRect(0 ,0 , TextWidth , TextHeight) ; 

    GUIScore = 0 ; 

    this->TextInTopRightTexture = NULL ; 
}

void GUI::Render() {
    if (GUIScore < RecentScore) GUIScore ++ ; 
    std::string Score = "Score : " + std::to_string(GUIScore) ; 
    SDL_Texture* ScoreTexture = CreateTextureFromString(Score) ;     

    int BarInRectWidth =  (double) (BarLifeWidth - 8) * ((double) RecentLife / MaxLife) ; 
    if (this->BarInRect.w > BarInRectWidth) this->BarInRect.w -- ;  

    TextInTopRightTexture = Pause ? ToContinueTexture : ToPauseTexture ; 
    SDL_SetTextureAlphaMod(TextInTopRightTexture , AlphaNumberText) ;
    AlphaNumberText = (AlphaNumberText >= 200) ? 0 : AlphaNumberText + 1 ; 

    SDL_RenderCopy(gMainRenderer , TextInTopRightTexture , NULL , &TextInTopRight) ; 
    SDL_RenderCopy(gMainRenderer , gFrame , NULL , &FrameRect) ; 

    SDL_RenderCopy(gMainRenderer , gBarOut , NULL , &BarOutRect) ; 
    SDL_RenderCopy(gMainRenderer , gBarIn , NULL , &BarInRect) ; 

    SDL_RenderCopy(gMainRenderer , ScoreTexture , NULL , &ScoreRect) ;

    if (Pause) {
        SDL_RenderCopy(gMainRenderer , PauseFilter , NULL , &FilterRect) ; 
        SDL_RenderCopy(gMainRenderer , PauseText , NULL , &PauseTextRect) ; 
        SDL_RenderCopy(gMainRenderer , PressEsc , NULL , &PressEscRect) ; 
    }
}