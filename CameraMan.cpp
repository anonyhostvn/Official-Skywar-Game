#include "Object/CameraMan/CameraMan.h"
CameraMan::CameraMan () {
}

void CameraMan::RenderCamera() {

    CoordPoint<float> RealPos = GetRealPosOfCam() ;
    
    SDL_Rect SrcRect = makeRect(RealPos.GetX() , RealPos.GetY() , ScreenWidth , ScreenHeight) , 
             DesRect = makeRect(0 , 0 , ScreenWidth , ScreenHeight) ; 

    SDL_RenderCopyEx (gMainRenderer , BigMap , &SrcRect , &DesRect , NULL , NULL , SDL_FLIP_NONE) ; 
}