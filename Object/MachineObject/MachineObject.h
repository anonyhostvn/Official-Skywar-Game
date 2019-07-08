#ifndef MACHINE_OBJECT_EXIST
#define MACHINE_OBJECT_EXIST

#include "../../modules/modules.h"

class MachineObject {
    protected:
        PolarVector<float> PolarRecentVelocity ; 
        float Speed ;
        float OmegaPhi ;
        CoordPoint<float> Position ; 
} ; 

#endif