#ifndef BULLET_MACHINE_EXIST
#define BULLET_MACHINE_EXIST

#include <list>
#include <vector> 

#include "../../modules/modules.h"
#include "../Bullet/AllBullet.h"
#include "../SpaceShip/SpaceShip.h"

static const int MaxLevel = 10 ;
static const int BulletEachLevel = 3 ;
static const int MaxBullet = MaxLevel ;
static const int InitialBullet = 3 ; 
static const int FrameBetweenBulletConst = 1200  ;  

class BulletMachine {
    protected:
        int RecentLevel = InitialBullet ; 
        int NumberOfBulletFire = 0 ;
        int Threshold = InitialBullet ; 
        Bullet* BulletContainer[MaxBullet] ; //? All Bullet in game
        int RecentFrame = 0 ; //? Fire Bullet Arcording Frame
        int FrameBetweenBullet ; 
        int CountBulletFire = 0 ; //! The number of bullet the machine has fire when start game
        ExplosionEffect* MainExplosionEffect ;

    public:
        BulletMachine (ExplosionEffect* MainExplosionEffect);  //! The constructor of bullet machine 
        void Processing () ; //! Processing each frame 
        void FireNewBullet() ;  //! Fire new bullet 
        void DetectCollision() ; //! Detect Collision between two bullet 
        void Render() ; //? Render object 
} ; 

#endif