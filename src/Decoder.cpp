#include "SC_PlugIn.h"
#include "Decoder.hpp"

static InterfaceTable * ft;

namespace hoa{

  struct Decoder2D : public Unit {
    Decoder<Hoa2d, float>::Regular * decoder;

    int numberOfHarmonics, numberOfOutputs;
  
  };


  static void Decoder2D_process(Decoder2D * unit, int inNumSamples);
    
  static void Decoder2D_Ctor(Decoder2D * unit);
  
  static void Decoder2D_Dtor(Decoder2D * unit);


  // FUNC DEFS
  static void Decoder2D_Ctor(Decoder2D * unit){

    float order = IN0(1);
    
    unit->numberOfOutputs = IN0(2);
    
    unit->decoder = (Decoder<Hoa2d,float>::Regular *)RTAlloc(unit->mWorld,sizeof(Decoder<Hoa2d,float>::Regular(order,unit->numberOfOutputs)));

    new(unit->decoder) Decoder<Hoa2d,float>::Regular(order,unit->numberOfOutputs);
    
    unit->numberOfHarmonics = order*2+1;
    
    unit->decoder->computeRendering(FULLBUFLENGTH);
    
    SETCALC(Decoder2D_process);
    
    Decoder2D_process(unit,1);
  }

  static void Decoder2D_Dtor(Decoder2D * unit){
    RTFree(unit->mWorld, unit->decoder);
  }

  static void Decoder2D_process(Decoder2D * unit, int inNumSamples){
    
    Decoder<Hoa2d, float>::Regular * tempDecoder = unit->decoder;
    
    int numOutputs = unit->numberOfOutputs;
    
    int numHarmonics = unit->numberOfHarmonics;
    
    float input[inNumSamples * numHarmonics];
    
    float output[inNumSamples * numOutputs];


    for (int i = 0; i<inNumSamples; ++i){
      for (int j = 0; j<numHarmonics; ++j){
	input[i*numHarmonics + j] = IN(j+2)[i];
      }
    }
       
    for (int i = 0; i < inNumSamples; ++i){
      tempDecoder->process(input+i * numHarmonics, output + i * numOutputs);
    }
    
    for(int i = 0; i < inNumSamples; ++i){
      for (int j = 0; j< numOutputs; ++j){
	float * out = 	OUT(j);
	out[i] = output[i * numHarmonics + j];
      }
    }
  }

 PluginLoad(Decoder2D){

    ft = inTable;
  
    DefineDtorUnit(Decoder2D);
  
  }
}
