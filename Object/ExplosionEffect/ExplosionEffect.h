#ifndef EXPLOSION_EFFECT_EXIST
#define EXPLOSION_EFFECT_EXIST

#include "../../modules/modules.h"
#include "../SpaceShip/SpaceShip.h"
#include "../ControlEngine.h"

static const int SingleExplosionWidth = 500 ; 
static const int SingleExplosionHeight = 500 ; 
static const int MaxExplosion = 20 ; 

struct SingleExplosion {
    SDL_Rect DesRect ;
    int RecentFrame = 0 ;
    bool Exist = true ; 

    SingleExplosion(int x , int y) {
        this->DesRect.x = x ; 
        this->DesRect.y = y ; 
        this->DesRect.w = SingleExplosionWidth ; 
        this->DesRect.h = SingleExplosionHeight ; 
    }

    void Process () {
        if (this->RecentFrame >= NumberOfExplosion) {
            this->Exist = false ; 
            return ; 
        }

        this->RecentFrame ++ ; 
    }
} ; 

class ExplosionEffect {

    public:
        ExplosionEffect() ; 
        void ProcessRender() ;
        void AddNewExplosion(CoordPoint<float> Position) ; 

    private:
        SingleExplosion* ExplosionContainer[MaxExplosion] ;
} ; 

#endif