#ifndef TRAIL_EFFECT_EXIST
#define TRAIL_EFFECT_EXIST

#include "../../modules/modules.h"
#include "../ControlEngine.h"

const int NUM_SINGLE_TRAIL = 24 ; 
const int SingleTrailWidth = 20 ; 
const int SingleTrailHeight = 20 ;
const int SingleFrame = 24 ; 
const int FrameBreak = 0 ; 

struct SingleTrail {
    int Frame = 0 ;
    SDL_Rect DesRect ; 
    float Angle ;
    bool Exist = true ; 

    SingleTrail(const int& x ,const int& y ,const float& Angle) {
        this->DesRect.x = x ; 
        this->DesRect.y = y ;
        this->DesRect.w = SingleTrailWidth ; 
        this->DesRect.h = SingleTrailHeight ; 
        this->Angle = Angle ; 
    }

    void Process () {
        if (Frame >= SingleFrame) {
            Exist = false ;
            return ; 
        }

        this->Frame ++ ;
    }

    bool IsExist () {
        return this->Exist ; 
    }
} ; 

class TrailEffect {
    public:
        TrailEffect() ; 
        TrailEffect(CoordPoint<float>& Position , float& Angle) ; 
        ~TrailEffect() ; 
        void Process (CoordPoint<float>& Position , float& Angle) ;        
        void FreeMemory() ;

    private:
        SingleTrail* TrailContainer[NUM_SINGLE_TRAIL] ; 

        int RecentFrame = 0 ; 
        int LastFrame = 0 ; 

        int SingleTrailWidth ; 
        int SingleTrailHeight ;
} ;  

#endif