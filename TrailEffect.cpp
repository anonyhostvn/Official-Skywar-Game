#include "Object/TrailEffect/TrailEffect.h"

TrailEffect::TrailEffect() {

}

TrailEffect::TrailEffect(CoordPoint<float>& Position , float& Angle) {
    this->SingleTrailWidth = SingleTrailWidth ; 
    this->SingleTrailHeight = SingleTrailHeight ;

    
    for (int i = 0 ; i < NUM_SINGLE_TRAIL ; i ++) {
        TrailContainer[i] = NULL ; 
    }

    TrailContainer[0] = new SingleTrail(Position.GetX() , Position.GetY() , Angle) ; 
}

TrailEffect::~TrailEffect() {
    for (int i = 0 ; i < NUM_SINGLE_TRAIL ; i ++) delete(TrailContainer[i]) ; 
}

void TrailEffect::Process (CoordPoint<float>& Position , float& Angle) {

    CoordPoint<float> PosCam = GetRealPosOfCam() ; 

    for (int i = 0 ; i < NUM_SINGLE_TRAIL ; i ++) if (TrailContainer[i] != NULL && !TrailContainer[i]->IsExist()) {
            delete(TrailContainer[i]) ;
            TrailContainer[i] = NULL ; 
    }

    for (int i = 0 ; i < NUM_SINGLE_TRAIL ; i ++ ) if (TrailContainer[i] == NULL) {
        TrailContainer[i] = new SingleTrail(Position.GetX() , Position.GetY() , Angle) ; 
        break ; 
    }

    for (int i = 0 ; i < NUM_SINGLE_TRAIL ; i ++) if (TrailContainer[i] != NULL) {
        TrailContainer[i]->Process() ;
        SDL_Rect DesRect = TrailContainer[i]->DesRect ; 
        int RecentFrame = TrailContainer[i]->Frame ; 
        float RecentAngle = TrailContainer[i]->Angle * 180 / pii  ; 

        DesRect.x -= PosCam.GetX() ;
        DesRect.y -= PosCam.GetY() ; 
        if (DesRect.x >= 0 && DesRect.y >= 0 && DesRect.x <= ScreenWidth && DesRect.y <= ScreenHeight) {
            SDL_RenderCopyEx(gMainRenderer , gTrailEffect , &TrailRect[RecentFrame] , &DesRect , RecentAngle , NULL , SDL_FLIP_NONE) ; 
        }
    }
}


void TrailEffect::FreeMemory() {
}
