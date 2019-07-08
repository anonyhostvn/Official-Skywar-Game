#ifndef PRIVATE_DATACONST_EXIST
#define PRIVATE_DATACONST_EXIST

static const int BigMapWidth = 4000 ; 
static const int BigMapHeight = 5665 ;  
static const int ScreenWidth = 1000 ; 
static const int ScreenHeight = 600 ;
static const double pii = 3.14159265358979323846  ; 

static const int ExplosionWidth = 4096 ; 
static const int ExplosionHeight = 4096 ; 
static const int NumberOfExplosionTextureRow = 8 ; 
static const int NumberOfExplosionTextureCol = 8 ; 
static const int NumberOfExplosion = NumberOfExplosionTextureCol * NumberOfExplosionTextureRow ;

static const int TrailWidth = 768 ; 
static const int TrailHeight = 32 ; 
static const int NumberOfTrailTextureRow = 1 ; 
static const int NumberOfTrailTextureCol = 24 ; 
static const int NumberOfTrail = NumberOfTrailTextureCol * NumberOfTrailTextureRow ; 

static const int FrameWidth = 300 ; 
static const int FrameHeight = 100 ; 
static const int FramePosY = ScreenHeight - FrameHeight ; 
static const int FramePosX = 330 ;
static const int GUIAlphaMod = 180 ; 
static const int BarLifePosX = FramePosX + 30 ; 
static const int BarLifePosY = FramePosY + 15 ; 
static const int BarLifeWidth = 240 ; 
static const int BarLifeHeight = 40 ; 
static const int PauseTextWidth = 200 ; 
static const int PauseTextHeight = 40 ;
static const int PauseTextPosX = (ScreenWidth - PauseTextWidth) / 2 ; 
static const int PauseTextPosY = ScreenHeight / 3 ; 

static const int MaxLife = 10 ; 
static const int DamageBullet[2] = {2 , 3} ; 
static const int ScoreBullet[2] = {100 , 150} ; 

static const int PauseFilterAlpha = 140 ; 

#endif