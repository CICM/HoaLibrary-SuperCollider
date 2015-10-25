#include "SC_PlugIn.h"
#include "Encoder.hpp"

static InterfaceTable * ft;

namespace hoa{

  struct Encoder2D : public Unit {
    Encoder<Hoa2d, float>::DC * encoder;

    int numberOfHarmonics;
  
  };


  static void Encoder2D_process(Encoder2D * unit, int inNumSamples);
    
  static void Encoder2D_Ctor(Encoder2D * unit);
  
  static void Encoder2D_Dtor(Encoder2D * unit);


  
  // FUNC DEFS
  static void Encoder2D_Ctor(Encoder2D * unit){

    float order = *IN(1);
    
    unit->encoder = (Encoder<Hoa2d,float>::DC *)RTAlloc(unit->mWorld,sizeof(Encoder<Hoa2d,float>::DC(order)));

    new(unit->encoder) Encoder<Hoa2d,float>::DC(order);
    
    unit->numberOfHarmonics = order*2+1;
    
    unit->encoder->setAzimuth(0.);

    unit->encoder->setRadius(1.0);

    unit->encoder->setMute(false);

    SETCALC(Encoder2D_process);
    
    Encoder2D_process(unit,1);
  }

  static void Encoder2D_Dtor(Encoder2D * unit){
    RTFree(unit->mWorld, unit->encoder);
  }

  static void Encoder2D_process(Encoder2D * unit, int inNumSamples){
    
    Encoder<Hoa2d, float>::DC * tempEncoder = unit->encoder;
    
    float * input = IN(0);
	
    float * azimuth = IN(2);
    
    float * radius = IN(3);
    
    int nHarmonics = unit->numberOfHarmonics;
    
    float output[inNumSamples * nHarmonics];
    
    tempEncoder->setAzimuth(*azimuth);
    tempEncoder->setRadius(*radius);
       
    for (int i = 0; i < inNumSamples; ++i){
      tempEncoder->process(input+i, output + i * nHarmonics);
    }
    
    for(int i = 0; i < inNumSamples; ++i){
      for (int j = 0; j< nHarmonics; ++j){
	float * out = 	OUT(j);
	out[i] = output[i * nHarmonics + j];
      }
    }
  }

  PluginLoad(Encoder2D){

    ft = inTable;
  
    DefineDtorUnit(Encoder2D);
  
  }
}
