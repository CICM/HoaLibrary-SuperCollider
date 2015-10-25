#ifndef __SC_DECODER
#define __SC_DECODER

#include "SC_PlugIn.h"
#include "Decoder.hpp"

using hoa::Decoder;
using hoa::Hoa2d;

struct Decoder2D : Unit {

  Decoder<Hoa2d, float>::Regular * decoder;
    
  int numberOfHarmonics, numberOfOutputs;
};

extern void Decoder2D_Ctor(Decoder2D * unit);
extern void Decoder2D_Dtor(Decoder2D * unit);
extern void Decoder2D_process(Decoder2D * unit, int inNumSamples);

#endif
