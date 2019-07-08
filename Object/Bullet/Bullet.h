#ifndef BULLET_EXIST
#define BULLET_EXIST

#include "../../modules/modules.h"
#include "../ObjectConst.h" 
#include "../ControlEngine.h"
#include "../SpaceShip/SpaceShip.h"
#include "../MachineObject/MachineObject.h"
#include "../TrailEffect/TrailEffect.h"
#include "../ExplosionEffect/ExplosionEffect.h"

static const int FrameForEachBulletType1 = 1200 ; 

class Bullet : public MachineObject {
    public:
        Bullet() ; 
        
        void DetectingTarget () ; //? Detect the SpaceShip and justify the Velocity of Bullet 
        void Move () ;  //? Moving the SpaceShip (Change to Position arcording to Velocity)
        void Render() ; //? Display the Bullet (Arcording to the Position)
        void Destroy () ; //? Destroy the Bullet (Change the status or exist variable)
        bool StillAlive () ; //? Check if the bullet still alive  
        void FreeMemory() ;  //? Free the memory of texture of bullet 
        bool CollisionWith (Bullet& Other) ;  //? Check if 'this' Bullet have collision with other  
        CoordPoint<float> GetPosition () ;  //? Get Position of Bullet
        bool DetectCollisionWithSpaceShip() ; 
        int GetType() ; 

    protected:
        int Type = 0 ; 
        float BulletWidth , BulletHeight ;
        bool Exist ; //? Status of Bullet (is the Bullet Destroy ? )
        float DeltaPhi = pii / 80 ; //? The angle of Bullet when turning
        float ErrorRate = 10 ; //? means 0.1 or 10% 
        float TimeExist = 15000 ; //? Time for bullet until self-destroy
        TrailEffect* BulletTrailEffect ;

        int FrameExist = FrameForEachBulletType1 ; //? Frame for bullet until self-destroy
        int RecentFrame = 0 ; 
} ;

#endif