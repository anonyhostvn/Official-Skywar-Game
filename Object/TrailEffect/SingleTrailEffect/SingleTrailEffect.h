#ifndef SINGLE_TRAIL_EFFECT
#define SINGLE_TRAIL_EFFECT

#include "../../../modules/modules.h"

static const int FRAME_BETWEEN_TRAIL = 5 ; 
static const int FRAME_FOR_EACH_TRAIL = 100 ; 

class SingleTrailEffect {

    public:
        SingleTrailEffect(SDL_Renderer* gMainRenderer , const int& RecentFrame, CoordPoint<float>& Position , const float& Angle , const int& Width ,const int& Height) ;
        void Process(CoordPoint<float>& PosCam) ; 
        bool GetStatus () ;

    private:
        SDL_Renderer* gMainRenderer ;

        int FrameExist ;
        int RecentFrame;

        int Width ; 
        int Height ; 

        CoordPoint<float> Position ;
        float Angle ;
        bool Exist ; 
} ; 

#endif