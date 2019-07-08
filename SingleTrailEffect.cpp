#include "Object/TrailEffect/SingleTrailEffect/SingleTrailEffect.h"

SingleTrailEffect::SingleTrailEffect(SDL_Renderer* gMainRenderer, const int& RecentFrame ,CoordPoint<float>& Position , const float& Angle , const int& Width ,const int& Height){
    this->gMainRenderer = gMainRenderer ; 
    this->Position = Position ;
    this->Angle = Angle ; 
    this->Width = Width ;
    this->Height = Height ;

    this->RecentFrame = RecentFrame ; 
    this->Exist = true ; 
}

void SingleTrailEffect::Process(CoordPoint<float>& PosCam)  { 


    if ((RecentFrame) >= FRAME_FOR_EACH_TRAIL) {
        Exist = false ; 
        return ;
    }
    
    RecentFrame ++ ;

    CoordPoint<float> RealPos = {(Position).GetX() - PosCam.GetX() , (Position).GetY()  - PosCam.GetY()} ;

    if (RealPos.GetX() <= 0 || RealPos.GetY() <= 0 || RealPos.GetX() > ScreenWidth || RealPos.GetY() > ScreenHeight) return ; 

        // std::cout << RealPos.GetX() << " " << RealPos.GetY() <<" " << ScreenWidth  << " " << ScreenHeight <<  "\n" ;
    SDL_Rect DesRect = makeRect(RealPos.GetX() , RealPos.GetY() , Width , Height) ;

    float DAngle = (Angle) * 180 / pii ; 
    SDL_RenderCopyEx(this->gMainRenderer , gTrailBulletTexture , NULL , &DesRect , DAngle , NULL , SDL_FLIP_NONE) ;
}

bool SingleTrailEffect::GetStatus() {
    return this->Exist ; 
}