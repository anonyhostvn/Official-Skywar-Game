#include "Object/Nature/Nature.h"

Nature::Nature() {
    srand(time(NULL)) ; 

    for (int i = 0 ; i < MAX_CLOUDS ; i ++) {
        CloudContainer[i] = new Cloud(rand() % BigMapWidth , rand() % BigMapHeight , rand() % NUMBER_CLOUDS_TEXTURE) ;
    }
}

void Nature::Render() {
 
    CoordPoint<float> PosCam = GetRealPosOfCam() ;

    for (int i = 0 ; i < MAX_CLOUDS ; i ++) CloudContainer[i]->Process() ; 
}