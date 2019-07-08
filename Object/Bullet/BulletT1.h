#ifndef BULLET_T1_EXIST
#define BULLET_T1_EXIST

#include "Bullet.h"

class BulletT1 : public Bullet {
    public:
        BulletT1() {
            this->Speed = BulletSpeedT1 ;
            this->Type = 1 ; 
            this->BulletHeight = BulletHeightConst[1] ; 
            this->BulletWidth = BulletWidthConst[1] ; 
            this->PolarRecentVelocity = {Speed, 0} ; //? Recent Polar Velocity 
            this->DeltaPhi = BulletDeltaPhiT1 ; 
        }
} ; 

#endif