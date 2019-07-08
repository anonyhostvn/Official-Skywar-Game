#include "Object/ExplosionEffect/ExplosionEffect.h"

ExplosionEffect::ExplosionEffect () {
    for (int i = 0 ; i < MaxExplosion ; i ++) ExplosionContainer[i] = NULL ;
}

void ExplosionEffect::ProcessRender() {

    CoordPoint<float> PosCam = GetRealPosOfCam() ;

    for (int i = 0 ; i < MaxExplosion ; i ++) if (ExplosionContainer[i] != NULL) {
        int RecentFrame = ExplosionContainer[i]->RecentFrame ; 
        SDL_Rect DesRect= ExplosionContainer[i]->DesRect ; 
        DesRect.x -= PosCam.GetX() ; 
        DesRect.y -= PosCam.GetY() ; 
        // if (DesRect.x >= 0 && DesRect.x <= ScreenWidth && DesRect.y >= 0 && DesRect.y <= ScreenHeight) 
            SDL_RenderCopy(gMainRenderer , gExplosionEffect , &ExplosionRect[RecentFrame] , &DesRect) ; 
        ExplosionContainer[i]->Process() ; 
        if (!ExplosionContainer[i]->Exist) {
            delete(ExplosionContainer[i]) ; 
            ExplosionContainer[i] = NULL ; 
        }
    }
}

void ExplosionEffect::AddNewExplosion(CoordPoint<float> Position) {
    for (int i = 0 ; i < MaxExplosion ; i ++) if (ExplosionContainer[i] == NULL) {
        Mix_PlayChannel(-1 , gRumble , 0) ;
        ExplosionContainer[i] = new SingleExplosion(Position.GetX() - SingleExplosionWidth / 2 , Position.GetY() - SingleExplosionHeight / 2) ; 
        return ; 
    }
}