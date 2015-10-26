#include "SC_PlugIn.h"
#include "Decoder.hpp"

static InterfaceTable * ft;

namespace hoa{

  // DECODER REGULAR
  struct Decoder2D : public Unit {
    Decoder<Hoa2d, float>::Regular * decoder;

    int numberOfHarmonics, numberOfOutputs;
  
  };


  static void Decoder2D_process(Decoder2D * unit, int inNumSamples);
    
  static void Decoder2D_Ctor(Decoder2D * unit);
  
  static void Decoder2D_Dtor(Decoder2D * unit);


  // DECODER BINAURAL
  struct Decoder2DBinaural : public Unit {
    Decoder<Hoa2d, float>::Binaural * decoder;
    int numberOfHarmonics;
  };


  static void Decoder2DBinaural_process(Decoder2DBinaural * unit, int inNumSamples);
    
  static void Decoder2DBinaural_Ctor(Decoder2DBinaural * unit);
  
  static void Decoder2DBinaural_Dtor(Decoder2DBinaural * unit);

  // FUNC DEFS
  static void Decoder2D_Ctor(Decoder2D * unit){

    int order = IN0(0);
    
    unit->numberOfOutputs = IN0(1);
    
    unit->decoder = (Decoder<Hoa2d,float>::Regular*)RTAlloc(unit->mWorld,sizeof(Decoder<Hoa2d,float>::Regular(order, unit->numberOfOutputs)));

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
      tempDecoder->process(input + i * numHarmonics, output + i * numOutputs);
    }
    
    for(int i = 0; i < inNumSamples; ++i){
      for (int j = 0; j< numOutputs; ++j){
	float * out = 	OUT(j);
	out[i] = output[i * numOutputs + j];
      }
    }
  }

  static void Decoder2DBinaural_Ctor(Decoder2DBinaural * unit){

    int order = IN0(0);
    
     int cropSize = IN0(1);

     unit->numberOfHarmonics = order * 2 + 1;
     
     unit->decoder = (Decoder<Hoa2d,float>::Binaural*)RTAlloc(unit->mWorld,sizeof(Decoder<Hoa2d,float>::Binaural(order)));

    new(unit->decoder) Decoder<Hoa2d,float>::Binaural(order);
    
    unit->decoder->setCropSize(cropSize);
    
    unit->decoder->computeRendering(FULLBUFLENGTH);
    
    SETCALC(Decoder2DBinaural_process);
  }

  static void Decoder2DBinaural_Dtor(Decoder2DBinaural * unit){
    RTFree(unit->mWorld, unit->decoder);
  }

  static void Decoder2DBinaural_process(Decoder2DBinaural * unit, int inNumSamples){
    
    Decoder<Hoa2d, float>::Binaural * tempDecoder = unit->decoder;

    int numHarmonics = unit->numberOfHarmonics;
    
    float ** input = new float *[numHarmonics];

    for (int i = 0; i < numHarmonics; ++i) input[i] = IN(i+2);
    
    float ** output = new float * [2];

    output[0] = OUT(0);
    output[1] = OUT(1);
       
    tempDecoder->processBlock(const_cast<const float **>(input),output);
    
  }
 PluginLoad(Decoder){

    ft = inTable;
  
    DefineDtorUnit(Decoder2D);
    DefineDtorUnit(Decoder2DBinaural);
  
  }
}
