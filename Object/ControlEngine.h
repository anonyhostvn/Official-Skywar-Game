#ifndef ENGINECONTROL_EXIST
#define ENGINECONTROL_EXIST

#include "../modules/modules.h" 


enum Dimension {TurnLeft , TurnRight} ;

// extern CoordVector TurningVector[16] ; 
extern const int NumDirection ; 

CoordPoint<float> GetRealPosOfCam () ; 

#endif