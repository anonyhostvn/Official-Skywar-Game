#ifndef SpaceShip_EXIST
#define SpaceShip_EXIST

#include "../../modules/modules.h"
#include "../ObjectConst.h"
#include "../ControlEngine.h"
#include "../MachineObject/MachineObject.h"
#include "../TrailEffect/TrailEffect.h" 

class SpaceShip : MachineObject {

     public: 
        SpaceShip() ; //? Constructor of Spaceship
        const int CenterPosX = ScreenWidth / 2 ,  
                  CenterPosY = ScreenHeight / 2 ; //? Center Position when spaceship not near the end of map

        bool GetExist () ;
        CoordPoint<float> GetPosition () ; 

        void Jump() ; //TODO Spaceship will 'hack' a distance when go into a 'magic cloud' 
        void Destroy() ; //TODO Destroy the Spaceship when being touch by bullet 
        void HandleEvent (SDL_Event& e) ; //? Handle Event Input of Player 
        void Move() ; //? Moving the Spaceship or change the position of spaceship arcording the velocity
        void RenderSpaceShip () ; //? Render Spaceship to screen
        void MoveTowardMouse()  ; //? An module where spaceship go toward the user's mouse

    private:
        bool Exist ; //? Status of Spaceship (only Bullet can change)
        float DeltaPhi = (float) pii / 50 ; //? The change of OmegaPhi when user press turn left/right
        float DeltaR = 0.5 ; //? The 'VRadius' will increase when user press turn left/right
        float VRadius = 0 ;  //? The Velocity of Radius (max = 2 , min = 0)
        SDL_Texture* SpaceShipImg = NULL ; //? Texture of Spaceship Image 
        SDL_Texture* SpaceShipImgDestroy = NULL ;  //? Texture when Spaceship is destroying 
}; 

#endif