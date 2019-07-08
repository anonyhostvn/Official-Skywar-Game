#include "modules/modules.h"

bool loadMedia(std :: string path , SDL_Renderer* &gMainRenderer) {
    SDL_Surface* LoadedSurface = IMG_Load(path.c_str()) ; 

    if (LoadedSurface == NULL) {
        printf("Load Image Failed 1 \n") ;
        return false ;  
    }

    SDL_Texture* gTexture = SDL_CreateTextureFromSurface(gMainRenderer , LoadedSurface) ;

    SDL_FreeSurface(LoadedSurface) ; 

    SDL_RenderCopy(gMainRenderer , gTexture , NULL , NULL) ; 
}

SDL_Texture* loadTexture (const std :: string path , SDL_Renderer* gRenderer) {
    SDL_Surface* LoadedSurface = IMG_Load(path.c_str()) ; 

    if (LoadedSurface == NULL) {
        std::cout << "Load Img Failed 2 " << path << "\n" ;  
    }

    SDL_Texture* resultTexture = SDL_CreateTextureFromSurface(gRenderer , LoadedSurface) ; 

    return resultTexture; //! If remove this line, the program still work !!!!!
}

void renderTexture (SDL_Texture* &gTexture , SDL_Renderer* &gRenderer , int posX , int posY){
    SDL_Rect rect ; 
    rect.x = posX ; 
    rect.y = posY ; 
    SDL_QueryTexture(gTexture , NULL , NULL , &rect.w , &rect.h) ; 
    SDL_RenderCopy(gRenderer , gTexture , NULL, &rect) ; 
}