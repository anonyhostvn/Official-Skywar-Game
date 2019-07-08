#include "Object/SpaceShip/SpaceShip.h" 


//? ======================= Init Module =============================================|
SpaceShip::SpaceShip() {
    SpaceShip::Position = {BigMapWidth / 2 , BigMapHeight / 2} ; 
    POS_SPACESHIP = &this->Position ;
    SpaceShipImg = loadTexture("images/SpaceShip/SpaceShip.png" , gMainRenderer) ; 

    // this->RecentVelocity = { 0 , -this->Speed} ; //! Init Recent Velocity in Coordinate (use with Old HandleEvent and Old Moving SpaceShip and Render Modules with Decartes Velocity)
    this->Speed = ShipSpeed ; 
    this->PolarRecentVelocity = {this->Speed , -pii / 2} ;
    this->OmegaPhi = 0 ; 
    this->Exist = true ;
}

//?==============================================================

//? ===================== New Render Modules =========================================|
//* ----------------------> Render Moudle with Polar Coordinate Velocity 

void SpaceShip::RenderSpaceShip () {
    CoordPoint<float> RenderPosition = {ScreenWidth / 2 , ScreenHeight / 2} ;
    CoordPoint<float> CamPosition = GetRealPosOfCam() ; 

    if (CamPosition.GetX() == 0) RenderPosition.SetX(SpaceShip::Position.GetX()) ; 
    else if (CamPosition.GetX() == BigMapWidth - ScreenWidth) RenderPosition.SetX(SpaceShip::Position.GetX() - CamPosition.GetX()) ;   

    if (CamPosition.GetY() == 0) RenderPosition.SetY(SpaceShip::Position.GetY()) ; 
    else if (CamPosition.GetY() == BigMapHeight - ScreenHeight) RenderPosition.SetY(SpaceShip::Position.GetY() - CamPosition.GetY()) ; 

    SDL_Rect DesRect = makeRect(RenderPosition.GetX() - ShipWidth / 2, RenderPosition.GetY() - ShipHeight / 2 , ShipWidth , ShipHeight) ; 


    float angle = (PolarRecentVelocity.GetPhi()) * 180 / pii ;
    SDL_RenderCopyEx(gMainRenderer , SpaceShip::SpaceShipImg , NULL , &DesRect , angle , NULL , SDL_FLIP_NONE) ;  
}

//?===================================================================================|*

//? ========================== Move Toward Mouse Version =============================|
//*------------------------> New Handle Event 
void SpaceShip::HandleEvent(SDL_Event& e) {

    if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
        switch (e.key.keysym.sym)
        {
        case SDLK_LEFT:
            this->OmegaPhi -= DeltaPhi ; 
            this->VRadius += DeltaR ; 
        break;

        case SDLK_RIGHT:
            this->OmegaPhi += DeltaPhi ; 
            this->VRadius += DeltaR ; 
        break ; 
        
        default:
            break;
        }
    } else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
        switch (e.key.keysym.sym)
        {
        case SDLK_LEFT:
            this->OmegaPhi += DeltaPhi ; 
            this->VRadius -= DeltaR ; 
        break;

        case SDLK_RIGHT:
            this->OmegaPhi -= DeltaPhi ; 
            this->VRadius -= DeltaR ;  
        break ; 
        
        default:
            break;
        }
    }
}

//?===================================================================================|

//? ====================Move the SpaceShip============================================|
//*--------------------> New Moving SpaceShip
void SpaceShip::Move() {
    if (Pause) return ; 

    PolarRecentVelocity.SetPhi(PolarRecentVelocity.GetPhi() + OmegaPhi) ; 
    PolarRecentVelocity.SetR(Speed + VRadius) ; 

    CoordVector<float> DecartesRecentVelocity = PolarRecentVelocity.ConvertToCoord() ; 

    Position.SetX(Position.GetX() + DecartesRecentVelocity.GetCoordX()) ; 
    Position.SetY(Position.GetY() + DecartesRecentVelocity.GetCoordY()) ; 

    if (Position.GetX() < 0 || Position.GetX() > BigMapWidth) 
        DecartesRecentVelocity.SetCoordX(-DecartesRecentVelocity.GetCoordX()) ; 
    if (Position.GetY() < 0 || Position.GetY() > BigMapHeight) 
        DecartesRecentVelocity.SetCoordY( -DecartesRecentVelocity.GetCoordY()) ; 

    PolarRecentVelocity = DecartesRecentVelocity.ConvertToPolar() ; 
}
//? ==================================================================================|


//?===================================================================================|

//? =================== Status Processing ============================================|
void SpaceShip::Destroy() {
    this->Exist = false ; 
}
//? ==================================================================================|

//? =============== Some Get and Set Function ========================================|
bool SpaceShip::GetExist() {
    return this->Exist ; 
}

CoordPoint<float> SpaceShip::GetPosition () {
    return this->Position ; 
}
//? ==================================================================================|