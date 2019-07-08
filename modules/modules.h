#ifndef PRIVATE_MODULES
#define PRIVATE_MODULES

#include <SDL2/SDL.h> 
#include <SDL2/SDL_image.h> 
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h> 
#include <string> 
#include <algorithm>
#include <iostream> 

#include <fstream>
#include <chrono>
#include <ctime>  

#include <stdlib.h> 
#include <time.h> 
#include "DataPattern/DataStructure.h"
#include "DataPattern/DataConstance.h"

//? ---------------- Setup LTexture ---------------------------

static const int NUMBER_CLOUDS_TEXTURE = 8 ; 

//? -----------------------------------------------------------

//? -------------------- Init Text ---------------------------- 
//? -----------------------------------------------------------

//? ------------------Init color ------------------------------
static const SDL_Color Black = {0, 0 , 0}; 
//? -----------------------------------------------------------

//? ------------------- Debug ---------------------------------
extern std::ofstream logIfs ; 
extern int SumOfBullet ; 
//? -----------------------------------------------------------

//! ==================================================================================================

extern SDL_Renderer* gMainRenderer ;
extern SDL_Texture* BigMap ;

extern SDL_Texture* gTrailBulletTexture ; 
extern SDL_Texture* gBulletTexture[2] ;

extern SDL_Texture* gExplosionEffect ;
extern SDL_Rect ExplosionRect[NumberOfExplosion] ; 

extern SDL_Texture* gTrailEffect ; 
extern SDL_Rect TrailRect[NumberOfTrail] ; 

extern Mix_Chunk* gRumble ; 
extern Mix_Music* gBG_Sound ; 

extern SDL_Texture* gClouds[NUMBER_CLOUDS_TEXTURE] ; 

extern CoordPoint<float>* POS_SPACESHIP ;
extern bool IsLoser ; 
extern bool Pause ; 
extern bool quit ; 

extern SDL_Texture* gFrame ;
extern SDL_Texture* gBarOut ; 
extern SDL_Texture* gBarIn ; 

extern int RecentLife ; 
extern int RecentScore ; 

extern TTF_Font *GameFont ; 

extern SDL_Texture* PauseFilter ; 
extern SDL_Texture* ToPauseTexture ; 
extern SDL_Texture* ToContinueTexture ;
extern SDL_Texture* PauseText ;
extern SDL_Texture* GoodJobText ; 
extern SDL_Texture* PlayAgainText ; 
extern SDL_Texture* ToMainMenuText ;
// extern SDL_Texture* BackEndGame ; 
extern SDL_Texture* PressEsc ;
extern SDL_Texture* NewHighScoreText ; 

extern SDL_Texture* OpeningTexture ; 

enum {
    StatusPlayingGame , 
    StatusOpening , 
    StatusEndgame 
} GameStatus ; 
//! ===================================================================================================
bool initVideo (SDL_Window* &gMainWindow , SDL_Renderer* &gRenderer , SDL_Texture* &BigMap,  int width , int height) ; 

void closeProgram(SDL_Window* &gMainWindow , SDL_Renderer* &gRenderer) ; 

bool loadMedia(std :: string path , SDL_Renderer* &gMainRenderer) ; 

void renderTexture (SDL_Texture* &gTexture , SDL_Renderer* &gRenderer , int posX , int posY) ; 

void InitGame() ; 

SDL_Texture* loadTexture (const std :: string path , SDL_Renderer* gRenderer) ; 

SDL_Rect makeRect(int x , int y , int w , int h) ; 

SDL_Texture* CreateTextureFromString (const std::string& str) ; 

#endif
