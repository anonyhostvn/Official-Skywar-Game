#ifndef NATURE_EXIST
#define NAUTRE_EXIST

#include "../../modules/modules.h"
#include "../ControlEngine.h"

static const int MAX_CLOUDS = 100 ;
static const int CLOUD_WIDTH = 400 ; 
static const int CLOUD_HEIGHT = 300 ;

struct Cloud {
    SDL_Rect CloudRect ; 
    int id ; 

    Cloud (int x , int y , int id) {
        CloudRect.x = x ;
        CloudRect.y = y ; 
        CloudRect.w = CLOUD_WIDTH + rand() % 50; 
        CloudRect.h = CLOUD_HEIGHT + rand() % 50;
        this->id = id ; 
    }

    void Process() {
        CoordPoint<float> PosCam = GetRealPosOfCam() ;
        SDL_Rect DesRect = CloudRect ; 
        DesRect.x -= PosCam.GetX() ; 
        DesRect.y -= PosCam.GetY() ; 
        SDL_RenderCopy(gMainRenderer , gClouds[id] , NULL , &DesRect) ; 
    }
} ; 

class Nature {
    public:
        Nature() ;
        void Render() ;  
    private:
        Cloud* CloudContainer[MAX_CLOUDS] ; 
}; 

#endif