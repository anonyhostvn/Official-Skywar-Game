#include "modules/modules.h"

std::ofstream logIfs("logging.txt") ; 

SDL_Texture* gTrailBulletTexture ; 
SDL_Texture* gBulletTextureType1 ;
SDL_Texture* gBulletTexture[2] ; 

SDL_Rect ExplosionRect[NumberOfExplosion] ; 
SDL_Texture* gExplosionEffect ; 

SDL_Texture* gTrailEffect ; 
SDL_Rect TrailRect[NumberOfTrail] ; 

Mix_Chunk* gRumble = NULL ; 
Mix_Music* gBG_Sound = NULL ; 

SDL_Texture* gClouds[NUMBER_CLOUDS_TEXTURE] ;

SDL_Texture* gFrame ; 
SDL_Texture* gBarOut ; 
SDL_Texture* gBarIn ; 

SDL_Texture* PauseFilter ; 
SDL_Texture* ToPauseTexture ; 
SDL_Texture* ToContinueTexture ; 
SDL_Texture* PauseText ;
SDL_Texture* PressEsc ;
SDL_Texture* NewHighScoreText ; 

SDL_Texture* GoodJobText ; 
SDL_Texture* PlayAgainText ; 
SDL_Texture* ToMainMenuText ;
// SDL_Texture* BackEndGame ; 
 
SDL_Texture* OpeningTexture ; 

int RecentLife ;
int RecentScore ; 
int SumOfBullet  ; 

TTF_Font* GameFont ; 

void LoadExplosionEffect () {
    int WidthOfSingle = ExplosionWidth / NumberOfExplosionTextureCol , 
        HeightOfSingle = ExplosionHeight / NumberOfExplosionTextureRow ;

    for (int i = 0 ; i < NumberOfExplosionTextureRow ; i ++) {
        for (int j = 0 ; j < NumberOfExplosionTextureCol ; j ++) {
            int id = i * NumberOfExplosionTextureCol + j ; 
            ExplosionRect[id].x = j * WidthOfSingle ; 
            ExplosionRect[id].y = i * HeightOfSingle ;
            ExplosionRect[id].w = WidthOfSingle ; 
            ExplosionRect[id].h = HeightOfSingle ;  
        }
    }
}

void LoadTrailEffect () {
    int WidthOfSingle = TrailWidth / NumberOfTrailTextureCol , 
        HeightOfSingle = TrailHeight / NumberOfTrailTextureRow ; 

    for (int i = 0 ; i < NumberOfTrailTextureRow ; i ++) 
        for (int j = 0 ; j < NumberOfTrailTextureCol ; j ++) {
            int id = i * NumberOfTrailTextureCol + j ; 
            TrailRect[id].x = j * WidthOfSingle ; 
            TrailRect[id].y = i * HeightOfSingle ; 
            TrailRect[id].w = WidthOfSingle ; 
            TrailRect[id].h = HeightOfSingle ; 
        }
}

void LoadGUITexture () {
    gFrame = loadTexture("images/GUI/frame.png" , gMainRenderer) ;
    gBarIn = loadTexture("images/GUI/bar_2.png" , gMainRenderer) ; 
    gBarOut = loadTexture("images/GUI/bar_1.png" , gMainRenderer) ;
    PauseFilter = loadTexture("images/Filter/black.png" , gMainRenderer) ; 
    ToPauseTexture = loadTexture("images/Text/ToPause.png" , gMainRenderer) ; 
    ToContinueTexture = loadTexture("images/Text/ToContinue.png" , gMainRenderer) ; 
    PauseText = loadTexture("images/Text/Pause.png", gMainRenderer) ; 

    GoodJobText = loadTexture("images/Text/GoodJob.png", gMainRenderer) ;     
    PlayAgainText = loadTexture("images/Text/PlayAgain1.png", gMainRenderer) ; 
    ToMainMenuText = loadTexture("images/Text/ToMainMenu1.png", gMainRenderer) ; 
    // BackEndGame = loadTexture("images/Text/BackEnd.png", gMainRenderer) ; 
    OpeningTexture = loadTexture("images/GUI/Opening.png" , gMainRenderer) ; 
    PressEsc = loadTexture("images/GUI/PressEsc.png" , gMainRenderer) ; 
    NewHighScoreText = loadTexture("images/Text/NewHighScore.png" , gMainRenderer) ; 

    SDL_SetTextureBlendMode(PressEsc, SDL_BLENDMODE_BLEND) ; 
    SDL_SetTextureAlphaMod(PressEsc, GUIAlphaMod) ; 
    SDL_SetTextureBlendMode(gFrame , SDL_BLENDMODE_BLEND) ; 
    SDL_SetTextureAlphaMod(gFrame , GUIAlphaMod) ; 
    SDL_SetTextureBlendMode(gBarIn , SDL_BLENDMODE_BLEND) ; 
    SDL_SetTextureAlphaMod(gBarIn , GUIAlphaMod) ; 
    SDL_SetTextureBlendMode(gBarOut , SDL_BLENDMODE_BLEND) ; 
    SDL_SetTextureAlphaMod(gBarOut , GUIAlphaMod) ; 
    SDL_SetTextureBlendMode(PauseFilter , SDL_BLENDMODE_BLEND) ; 
    SDL_SetTextureAlphaMod(PauseFilter , PauseFilterAlpha) ; 
    SDL_SetTextureBlendMode(ToPauseTexture, SDL_BLENDMODE_BLEND) ; 
    SDL_SetTextureBlendMode(ToContinueTexture, SDL_BLENDMODE_BLEND) ;
    SDL_SetTextureBlendMode(PauseText, SDL_BLENDMODE_BLEND) ;
    SDL_SetTextureAlphaMod(PauseText, GUIAlphaMod) ; 
}

bool initVideo (SDL_Window* &gMainWindow , SDL_Renderer* &gRenderer , SDL_Texture* &BigMap,  int width , int height) {

    if (SDL_Init(SDL_INIT_VIDEO) == -1) {
        printf("Init SDL_VIDEO FAILED \n") ; 
        return false ; 
    }

    if (!IMG_Init(IMG_INIT_PNG)) {
        printf("Init PNG Failed \n") ; 
        return false ; 
    }

    Mix_Init(MIX_INIT_FLAC) ;
    Mix_Init(MIX_INIT_MP3) ; 

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT , 2 , 8192) < 0) {
        printf("Init Mixer Failed \n") ; 
        Mix_GetError(); 
        return false ; 
    }

    if (TTF_Init() == -1) {
        printf("Init TTf Failed") ; 
        return false ; 
    }

    gMainWindow = SDL_CreateWindow("Sky War" , SDL_WINDOWPOS_UNDEFINED , SDL_WINDOWPOS_UNDEFINED , width , height , SDL_WINDOW_SHOWN) ; 

    if (gMainWindow == NULL) {
        printf("Create Window Failed \n")  ; 
        return false ; 
    }

    gRenderer = SDL_CreateRenderer(gMainWindow , -1 , SDL_RENDERER_ACCELERATED) ; 

    if (gRenderer == NULL) {
        printf("Create Renderer from Window Failed \n") ; 
        return false ; 
    }

    BigMap = loadTexture("images/Big-Map.png" , gRenderer) ; 

    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

    gTrailBulletTexture = loadTexture("images/Effect/Trail-Effect.png" , gRenderer) ;
    gBulletTexture[0] = loadTexture("images/Bullet/Bullet1.png" , gRenderer)  ; 
    gBulletTexture[1] = loadTexture("images/Bullet/Bullet2.png" , gRenderer) ; 
    gExplosionEffect = loadTexture("images/Effect/explosion.png" , gRenderer) ;
    gTrailEffect = loadTexture("images/Effect/trail.png" , gRenderer) ;
    

    for (int i = 0 ; i < NUMBER_CLOUDS_TEXTURE ; i ++) {
        std::string NameCloud = "images/nature/cloud" + std::to_string(i) + ".png" ; 
        gClouds[i] = loadTexture(NameCloud , gRenderer) ; 
    } 
    LoadExplosionEffect() ; 
    LoadTrailEffect() ; 
    LoadGUITexture() ; 

    gRumble = Mix_LoadWAV("sounds/rumble.wav") ;
    gBG_Sound = Mix_LoadMUS("sounds/bg_sound.mp3") ;  

    GameFont = TTF_OpenFont("fonts/PermanentMarker-Regular.ttf" , 180) ; 

    return true ; 
}

void InitGame () {
    RecentLife = MaxLife ; 
    RecentScore = 0 ;
    SumOfBullet = 0 ;
}

void closeProgram(SDL_Window* &gMainWindow , SDL_Renderer* &gMainRenderer) {
    SDL_DestroyRenderer(gMainRenderer) ; 
    SDL_DestroyWindow(gMainWindow) ; 
    Mix_FreeChunk(gRumble) ;
    Mix_FreeMusic(gBG_Sound) ; 
    gRumble = NULL ; 
    gBG_Sound = NULL ; 

    logIfs.close() ; 
}

SDL_Rect makeRect(int x , int y , int w , int h) { 
    SDL_Rect resRect ; 
    resRect.x = x ; 
    resRect.y = y ; 
    resRect.w = w ; 
    resRect.h = h ; 

    return resRect ; 
}


SDL_Texture* CreateTextureFromString (const std::string& str) {
    SDL_Surface *ResSurface = TTF_RenderText_Solid(GameFont , str.c_str() , Black) ;
    SDL_Texture *ResTexture = SDL_CreateTextureFromSurface(gMainRenderer , ResSurface) ;
    SDL_SetTextureBlendMode(ResTexture , SDL_BLENDMODE_BLEND) ; 
    SDL_SetTextureAlphaMod(ResTexture, GUIAlphaMod) ; 
    return ResTexture ; 
} 