#ifndef __SC_ENCODER
#define __SC_ENCODER

#include "SC_PlugIn.h"
#include "Encoder.hpp"

using hoa::Encoder;
using hoa::Hoa2d;

  struct Encoder2D : Unit {
    Encoder<Hoa2d, float>::DC * encoder;

    int numberOfHarmonics;
  
  };

extern void Encoder2D_Ctor(Encoder2D * unit);
extern void Encoder2D_Dtor(Encoder2D * unit);
extern void Encoder2D_process(Encoder2D * unit, int inNumSamples);
#endif
