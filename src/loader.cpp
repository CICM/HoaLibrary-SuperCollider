#include "SC_PlugIn.h"
#include "scEncoder.hpp"
#include "scDecoder.hpp"

static InterfaceTable * ft;


  PluginLoad(HoaLibrary){

    ft = inTable;
    
    DefineDtorUnit(Decoder2D);
    DefineDtorUnit(Encoder2D);
    
 
}
