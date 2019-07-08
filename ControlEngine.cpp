#include "Object/ControlEngine.h"

const int NumDirection = 16;

CoordPoint<float> GetRealPosOfCam () {
    CoordPoint<float> res(0 , 0) ; 

    float SpaceShipX = POS_SPACESHIP->GetX() , 
        SpaceShipY = POS_SPACESHIP->GetY() ; 
    
    float PosCamX = 0 , PosCamY = 0 ; 

    if (SpaceShipX + ScreenWidth / 2  > BigMapWidth) PosCamX = BigMapWidth - ScreenWidth ; 
    else if (SpaceShipX - ScreenWidth / 2  < 0) PosCamX = 0 ; 
    else PosCamX =  SpaceShipX - ScreenWidth / 2 ;

    if (SpaceShipY + ScreenHeight / 2 > BigMapHeight) PosCamY = BigMapHeight - ScreenHeight ; 
    else if (SpaceShipY - ScreenHeight / 2 < 0) PosCamY = 0 ; 
    else PosCamY  = SpaceShipY - ScreenHeight / 2 ; 

    return {PosCamX , PosCamY} ; 
}