#include "AllInclude.h"

//? ================ Screen Window Status ============================
SDL_Window* gMainWindow = NULL ; 
SDL_Renderer* gMainRenderer = NULL ; 
SDL_Texture* BigMap = NULL ;  
SDL_Event e ; 
bool IsLoser = false ; 
bool Pause = false ; 
bool quit = false ; 

EndGame* EndGameGui = NULL ;
OpeningGame* OpeningGui = NULL ; 
//? ===========================================================

//? ===================== Game Object =========================
CoordPoint<float>* POS_SPACESHIP = NULL ; 
SpaceShip* MainShip = NULL ; 
Nature* GameNature = NULL ;
ExplosionEffect* GameExplosionEffect = NULL ; 
CameraMan* MainCam = NULL  ;
BulletMachine* GameBulletMachine = NULL  ;
GUI* GAMEGUI = NULL ;
//? ===========================================================

//? ============== Short Module ===============================
void Initialize () {
    initVideo(gMainWindow , gMainRenderer , BigMap, ScreenWidth , ScreenHeight) ;
    GameStatus = StatusOpening ; 

    EndGameGui = new EndGame() ; 
    OpeningGui = new OpeningGame() ;
}

void FreeGameMemory() {
    if (MainShip != NULL) delete(MainShip) ; 
    if (MainCam != NULL) delete(MainCam) ; 
    if (GameNature != NULL) delete(GameNature) ; 
    if (GameExplosionEffect != NULL) delete(GameExplosionEffect) ; 

    MainShip = NULL ; 
    MainCam = NULL ; 
    GameNature = NULL ; 
    GameExplosionEffect = NULL ; 
}

void ResetGame () {
    Mix_PlayMusic(gBG_Sound , -1) ; 

    FreeGameMemory() ; 

    //Mix_HaltMusic() ; 
    Pause = false ;
    MainShip = new SpaceShip; 
    GameNature = new Nature;
    GameExplosionEffect = new ExplosionEffect ; 
    MainCam = new CameraMan ;
    GameBulletMachine = new BulletMachine(GameExplosionEffect) ;
    GAMEGUI = new GUI() ;

}

void MoveObject () {
    MainShip->Move() ; 
    GameBulletMachine->Processing() ; 
}

void RenderingGameObject () {
    MainCam->RenderCamera() ; 
    GameNature->Render() ;
    MainShip->RenderSpaceShip() ;
    GameBulletMachine->Render() ; 
    GAMEGUI->Render() ;
}

//? =============================================================================

void Process () {
    SDL_RenderClear(gMainRenderer) ; 

    InitGame () ;
    ResetGame() ;

    int TimeDelay ; 
    unsigned int StartingFrameTime ;

    while (!quit) {
        StartingFrameTime = SDL_GetTicks() ;

        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true ;
            } 
            if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_SPACE) {
                Pause = !Pause;
            } 
            
            if (Pause && e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) {
                GameStatus = StatusOpening ; 
                return ; 
            }
            
            MainShip->HandleEvent(e) ; 
        }

        SDL_RenderClear(gMainRenderer) ; 

        MoveObject() ; 
        RenderingGameObject() ; 

        //? _____________ Processing Loser ______________________
        if (RecentLife <= 0) {
            GameStatus = StatusEndgame ;
            break ; 
        }
        //? _____________________________________________________

        SDL_RenderPresent(gMainRenderer) ;

        TimeDelay = std::max((int) 15 - (int) SDL_GetTicks() + (int) StartingFrameTime , 1) ;

        SDL_Delay(TimeDelay) ;
    }

    if (GameStatus == StatusEndgame)
    for (int i = 1 ; i <= 200 ; i ++) {
        SDL_RenderClear(gMainRenderer) ; 
        MoveObject() ; 
        RenderingGameObject() ; 

        SDL_RenderPresent(gMainRenderer) ;
        SDL_Delay(15) ; 
    }

    FreeGameMemory() ; 

}

void EndGameGUI () {

    EndGameGui->BeginEndGame() ; 

    while (!quit && !EndGameGui->IsChoose()) {
         while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true ;
            } else EndGameGui->Process(e) ;
        }

        SDL_RenderClear(gMainRenderer) ; 
        EndGameGui->Render() ;
        SDL_RenderPresent(gMainRenderer) ; 
        SDL_Delay(8) ;

    }

    if (EndGameGui->PlayAgain()) GameStatus = StatusPlayingGame ; 
    else GameStatus = StatusOpening ; 
}

void OpeningGUI () {
    FreeGameMemory() ; 
    Mix_HaltMusic() ; 
    OpeningGui->Init() ;

    while (!quit && !OpeningGui->IsSelect()) {
         while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true ;
            } else OpeningGui->Process(e) ;
        }

        SDL_RenderClear(gMainRenderer) ; 
        OpeningGui->Render() ; 
        SDL_RenderPresent(gMainRenderer) ; 
        SDL_Delay(8) ;
    }

    if (OpeningGui->IsStart()) GameStatus = StatusPlayingGame ; 
    else quit = true ; 
}

void GameGui () {
    SDL_SetRenderDrawColor(gMainRenderer , 0xFF , 0xFF , 0xFF , 0xFF) ;

    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true ;
            }
        }

        SDL_RenderClear(gMainRenderer) ; 
        if (GameStatus == StatusPlayingGame) Process() ;
        else if (GameStatus == StatusEndgame) EndGameGUI() ; 
        else OpeningGUI() ;

        if (quit) return ; 
    }
}

void testing () {
    int frame = 0 ;
    bool quit = false ; 
    SDL_Event e ; 

    SDL_SetRenderDrawColor(gMainRenderer , 0 , 0 , 0 , 0) ;
    SDL_RenderClear(gMainRenderer) ;

    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true ; 
            }
        }

    }

    SDL_RenderClear(gMainRenderer) ; 
    SDL_RenderPresent(gMainRenderer) ; 
    SDL_Delay(1000) ;

    closeProgram(gMainWindow , gMainRenderer) ; 
}

int main () {
    Initialize() ; 
    // Process() ; 
    GameGui() ; 

    closeProgram(gMainWindow , gMainRenderer) ;  
    return 0 ; 
}