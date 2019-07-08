#include "Object/Bullet/Bullet.h"

//? ===================== Constructor ====================================================
Bullet::Bullet () {
    SumOfBullet ++ ;

    srand(time(NULL)) ; 
    this->Exist = true ;

    float RandPhi = (float) (rand() % 618) / 10 ;
    PolarVector<float> RandomVector(1.5 * ScreenWidth , RandPhi) ;
    CoordVector<float> RandomVtr = RandomVector.ConvertToCoord() ;
    int X = POS_SPACESHIP->GetX() + RandomVtr.GetCoordX() , Y = POS_SPACESHIP->GetY() + RandomVtr.GetCoordY() ; 
    this->Position = {X , Y } ; //? Random Starting Position 

    this->OmegaPhi = 0 ;

    float Angle = this->PolarRecentVelocity.GetPhi() ; 
    this->BulletTrailEffect = new TrailEffect(this->Position , Angle) ;
}
//?=================================================================================================

//! Detecting Target and justify the Velocity 
void Bullet::DetectingTarget () { 
    CoordPoint<float> SpaceShipPosition = *POS_SPACESHIP ; 
    CoordVector<float> Direction = Position.MakeVector(SpaceShipPosition) ; 
    PolarVector<float> PDirection = Direction.ConvertToPolar() ;

    if (abs(PDirection.GetPhi() - PolarRecentVelocity.GetPhi()) <= DeltaPhi / ErrorRate) return ; 

    if (PolarRecentVelocity.GetPhi() + DeltaPhi < PDirection.GetPhi()) {
        if (PDirection.GetPhi() - PolarRecentVelocity.GetPhi() < pii * 2 - PDirection.GetPhi() + PolarRecentVelocity.GetPhi()) {
            PolarRecentVelocity.SetPhi(PolarRecentVelocity.GetPhi() + DeltaPhi) ; 
        } else {
            PolarRecentVelocity.SetPhi(PolarRecentVelocity.GetPhi() - DeltaPhi) ; 
        }
    } else if (PDirection.GetPhi() + DeltaPhi < PolarRecentVelocity.GetPhi()) {
        if (PolarRecentVelocity.GetPhi() - PDirection.GetPhi() < pii * 2 - PolarRecentVelocity.GetPhi() + PDirection.GetPhi()) {
            PolarRecentVelocity.SetPhi(PolarRecentVelocity.GetPhi() - DeltaPhi) ; 
        } else {
            PolarRecentVelocity.SetPhi(PolarRecentVelocity.GetPhi() + DeltaPhi) ; 
        }
    }
    
}

//! Move Bullet with Velocity in Polar Coordinate 
void Bullet::Move() {
    if (Pause) return ; 

    this->DetectingTarget() ; 


    CoordVector<float> RecentDecartesVelocity = PolarRecentVelocity.ConvertToCoord() ; 

    Position.SetX(Position.GetX() + RecentDecartesVelocity.GetCoordX()) ; 
    Position.SetY(Position.GetY() + RecentDecartesVelocity.GetCoordY()) ; 

    this->RecentFrame ++ ;  
    if (this->RecentFrame >= this->FrameExist) {
        Destroy() ;
    }
} 

void Bullet::Render() {
    CoordPoint<float> PosCam = GetRealPosOfCam() ; 

    float Phi = PolarRecentVelocity.GetPhi() ; 
    BulletTrailEffect->Process(this->Position , Phi) ;

    if (!(Position.GetX() >= PosCam.GetX() && Position.GetX() + BulletWidth <= PosCam.GetX() + ScreenWidth
        && Position.GetY() >= PosCam.GetY() && Position.GetY() + BulletHeight <= PosCam.GetY() + ScreenHeight)) return ; 

    if (this->DetectCollisionWithSpaceShip()) {
        this->Destroy() ; 
        // this->PolarRecentVelocity.SetPhi(this->PolarRecentVelocity.GetPhi() + pii) ; //! Need Fixx
        RecentLife -= DamageBullet[this->Type] ;
        return ; 
    }

    SDL_Rect DesRect = makeRect(Position.GetX() - PosCam.GetX() , Position.GetY() - PosCam.GetY() , BulletWidth , BulletHeight) ; 

    float angle = PolarRecentVelocity.GetPhi() * 180 / pii ;

    // SDL_RenderCopyEx(gMainRenderer , gBulletTextureType1 , NULL , &DesRect , angle , NULL , SDL_FLIP_NONE) ;
    SDL_RenderCopyEx(gMainRenderer , gBulletTexture[this->Type] , NULL , &DesRect , angle , NULL , SDL_FLIP_NONE) ;   
}

//? ============================== Status Processing =======================================
void Bullet::Destroy() {
    SumOfBullet -- ; 

    RecentScore += ScoreBullet[this->Type] ;
    this->Exist = false ;
}

bool Bullet::StillAlive() {
    return this->Exist ; 
}

void Bullet::FreeMemory() {
    (*BulletTrailEffect).FreeMemory() ;
}

bool Bullet::CollisionWith (Bullet& Other) {
    CoordPoint<float> OtherPosition = Other.GetPosition() ; 
    return this->Position.SqrDistanceTo(OtherPosition) <= BulletWidth * BulletWidth / 4 ; 
}

bool Bullet::DetectCollisionWithSpaceShip() {
    bool Collision = false ; 

    CoordPoint<float> SpaceShipPosition = *POS_SPACESHIP ;  

    if (sqrt(Position.SqrDistanceTo(SpaceShipPosition)) <= (float) ShipHeight / 2 + BulletHeight / 2) Collision = true ;

    return Collision ; 
}

//? ========================================================================================

//? ============================ Some Get and Set Function =================================

CoordPoint<float> Bullet::GetPosition () {
    return this->Position ; 
}

int Bullet::GetType() {
    return this->Type ; 
}

//? ========================================================================================
