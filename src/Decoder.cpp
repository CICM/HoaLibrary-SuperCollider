#include "SC_PlugIn.h"
#include "Decoder.hpp"

static InterfaceTable * ft;

namespace hoa{

  // DECODER REGULAR 2D
  struct Decoder2D : public Unit {
    Decoder<Hoa2d, float>::Regular * decoder;

    float * input, * output;
    
    int numberOfHarmonics, numberOfOutputs;
  
  };
  
  // DECODER IRREGULAR 2D
  struct Decoder2DIrregular : public Unit {
    Decoder<Hoa2d, float>::Irregular * decoder;

    float * input, * output;
    
    int numberOfHarmonics, numberOfOutputs;
  
  };

  // DECODER BINAURAL 2D
  struct Decoder2DBinaural : public Unit {
    Decoder<Hoa2d, float>::Binaural * decoder;
    int numberOfHarmonics;
  };

  // DECODER REGULAR 3D
  struct Decoder3D : public Unit {
    Decoder<Hoa3d, float>::Regular * decoder;

    float * input, * output;
    
    int numberOfHarmonics, numberOfOutputs;
  
  };

  // DECODER BINAURAL 3D
  struct Decoder3DBinaural : public Unit {
    Decoder<Hoa3d, float>::Binaural * decoder;
    int numberOfHarmonics;
  };
  
  static void Decoder2D_process(Decoder2D * unit, int inNumSamples);
    
  static void Decoder2D_Ctor(Decoder2D * unit);
  
  static void Decoder2D_Dtor(Decoder2D * unit);

  static void Decoder2DIrregular_process(Decoder2DIrregular * unit, int inNumSamples);
    
  static void Decoder2DIrregular_Ctor(Decoder2DIrregular * unit);
  
  static void Decoder2DIrregular_Dtor(Decoder2DIrregular * unit);

  static void Decoder2DBinaural_process(Decoder2DBinaural * unit, int inNumSamples);
    
  static void Decoder2DBinaural_Ctor(Decoder2DBinaural * unit);
  
  static void Decoder2DBinaural_Dtor(Decoder2DBinaural * unit);

  static void Decoder3D_process(Decoder3D * unit, int inNumSamples);
    
  static void Decoder3D_Ctor(Decoder3D * unit);
  
  static void Decoder3D_Dtor(Decoder3D * unit);

  static void Decoder3DBinaural_process(Decoder3DBinaural * unit, int inNumSamples);
    
  static void Decoder3DBinaural_Ctor(Decoder3DBinaural * unit);
  
  static void Decoder3DBinaural_Dtor(Decoder3DBinaural * unit);
  
  // FUNC DEFS
  static void Decoder2D_Ctor(Decoder2D * unit){

    int order = IN0(0);
    
    unit->numberOfOutputs = IN0(1);
    
    unit->decoder = (Decoder<Hoa2d,float>::Regular*)RTAlloc(unit->mWorld,sizeof(Decoder<Hoa2d,float>::Regular(order, unit->numberOfOutputs)));

    new(unit->decoder) Decoder<Hoa2d,float>::Regular(order,unit->numberOfOutputs);
    
    unit->numberOfHarmonics = order*2+1;

    unit->input = (float*)RTAlloc(unit->mWorld,sizeof(float)* unit->numberOfHarmonics * FULLBUFLENGTH);
    unit->output = (float*)RTAlloc(unit->mWorld,sizeof(float)* unit->numberOfOutputs * FULLBUFLENGTH);
    
    unit->decoder->computeRendering(FULLBUFLENGTH);
    
    SETCALC(Decoder2D_process);
    
    Decoder2D_process(unit,1);
  }

  static void Decoder2D_Dtor(Decoder2D * unit){
    RTFree(unit->mWorld, unit->decoder);
    RTFree(unit->mWorld, unit->input);
    RTFree(unit->mWorld, unit->output);
  }

  static void Decoder2D_process(Decoder2D * unit, int inNumSamples){
    
    Decoder<Hoa2d, float>::Regular * tempDecoder = unit->decoder;
    
    int numOutputs = unit->numberOfOutputs;
    
    int numHarmonics = unit->numberOfHarmonics;
    
    float * inputs = unit->input;
    
    float * outputs = unit->output;


    for (int i = 0; i<inNumSamples; ++i){
      for (int j = 0; j<numHarmonics; ++j){
	inputs[i*numHarmonics + j] = IN(j+2)[i];
      }
    }
       
    for (int i = 0; i < inNumSamples; ++i){
      tempDecoder->process(inputs + i * numHarmonics, outputs + i * numOutputs);
    }
    
    for(int i = 0; i < inNumSamples; ++i){
      for (int j = 0; j< numOutputs; ++j){
	float * out = 	OUT(j);
	out[i] = outputs[i * numOutputs + j];
      }
    }
  }

  static void Decoder2DIrregular_Ctor(Decoder2DIrregular * unit){

    int order = IN0(0);
    
    unit->numberOfOutputs = IN0(1);
    
    unit->decoder = (Decoder<Hoa2d,float>::Irregular*)RTAlloc(unit->mWorld,sizeof(Decoder<Hoa2d,float>::Irregular(order, unit->numberOfOutputs)));

    new(unit->decoder) Decoder<Hoa2d,float>::Irregular(order,unit->numberOfOutputs);
    
    unit->numberOfHarmonics = order*2+1;

    unit->input = (float*)RTAlloc(unit->mWorld,sizeof(float)* unit->numberOfHarmonics * FULLBUFLENGTH);
    unit->output = (float*)RTAlloc(unit->mWorld,sizeof(float)* unit->numberOfOutputs * FULLBUFLENGTH);
    
    unit->decoder->setPlanewavesRotation(IN0(2),0,0);
    
    unit->decoder->computeRendering(FULLBUFLENGTH);
    
    SETCALC(Decoder2DIrregular_process);
    
    Decoder2DIrregular_process(unit,1);
  }

  static void Decoder2DIrregular_Dtor(Decoder2DIrregular * unit){
    RTFree(unit->mWorld, unit->decoder);
    RTFree(unit->mWorld, unit->input);
    RTFree(unit->mWorld, unit->output);
  }

  static void Decoder2DIrregular_process(Decoder2DIrregular * unit, int inNumSamples){
    
    Decoder<Hoa2d, float>::Irregular * tempDecoder = unit->decoder;
    
    int numOutputs = unit->numberOfOutputs;
    
    int numHarmonics = unit->numberOfHarmonics;
    
    float * inputs = unit->input;
    
    float * outputs = unit->output;


    for (int i = 0; i<inNumSamples; ++i){
      for (int j = 0; j<numHarmonics; ++j){
	inputs[i*numHarmonics + j] = IN(j+3)[i];
      }
    }
       
    for (int i = 0; i < inNumSamples; ++i){
      tempDecoder->process(inputs + i * numHarmonics, outputs + i * numOutputs);
    }
    
    for(int i = 0; i < inNumSamples; ++i){
      for (int j = 0; j< numOutputs; ++j){
	float * out = 	OUT(j);
	out[i] = outputs[i * numOutputs + j];
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
    
    float ** input =  (float**)RTAlloc(unit->mWorld,sizeof(float*)*numHarmonics);

    for (int i = 0; i < numHarmonics; ++i) input[i] = IN(i+2);
    
    float ** output = (float**)RTAlloc(unit->mWorld, sizeof(float*)*2);

    output[0] = OUT(0);
    output[1] = OUT(1);
       
    tempDecoder->processBlock(const_cast<const float **>(input),output);

    RTFree(unit->mWorld,input);
    RTFree(unit->mWorld,output);
    
  }

  static void Decoder3D_Ctor(Decoder3D * unit){

    int order = IN0(0);
    
    unit->numberOfOutputs = IN0(1);
    
    unit->decoder = (Decoder<Hoa3d,float>::Regular*)RTAlloc(unit->mWorld,sizeof(Decoder<Hoa3d,float>::Regular(order, unit->numberOfOutputs)));

    new(unit->decoder) Decoder<Hoa3d,float>::Regular(order,unit->numberOfOutputs);
    
    unit->numberOfHarmonics = (order +1) * (order + 1);

    unit->input = (float*)RTAlloc(unit->mWorld,sizeof(float)* unit->numberOfHarmonics * FULLBUFLENGTH);

    unit->output = (float*)RTAlloc(unit->mWorld,sizeof(float)* unit->numberOfOutputs * FULLBUFLENGTH);
    
    unit->decoder->computeRendering(FULLBUFLENGTH);
    
    SETCALC(Decoder3D_process);
    
    Decoder3D_process(unit,1);
  }

  static void Decoder3D_Dtor(Decoder3D * unit){
    RTFree(unit->mWorld, unit->decoder);
    RTFree(unit->mWorld, unit->input);
    RTFree(unit->mWorld, unit->output);
  }

  static void Decoder3D_process(Decoder3D * unit, int inNumSamples){
    
    Decoder<Hoa3d, float>::Regular * tempDecoder = unit->decoder;
    
    int numOutputs = unit->numberOfOutputs;
    
    int numHarmonics = unit->numberOfHarmonics;
    
    float * inputs = unit->input;
    
    float * outputs = unit->output;


    for (int i = 0; i<inNumSamples; ++i){
      for (int j = 0; j<numHarmonics; ++j){
	inputs[i*numHarmonics + j] = IN(j+2)[i];
      }
    }
       
    for (int i = 0; i < inNumSamples; ++i){
      tempDecoder->process(inputs + i * numHarmonics, outputs + i * numOutputs);
    }
    
    for(int i = 0; i < inNumSamples; ++i){
      for (int j = 0; j< numOutputs; ++j){
	float * out = 	OUT(j);
	out[i] = outputs[i * numOutputs + j];
      }
    }
  }

  static void Decoder3DBinaural_Ctor(Decoder3DBinaural * unit){

    int order = IN0(0);
    
    int cropSize = IN0(1);

    unit->numberOfHarmonics = (order +1) * (order + 1);
     
    unit->decoder = (Decoder<Hoa3d,float>::Binaural*)RTAlloc(unit->mWorld,sizeof(Decoder<Hoa3d,float>::Binaural(order)));

    new(unit->decoder) Decoder<Hoa3d,float>::Binaural(order);
    
    unit->decoder->setCropSize(cropSize);
    
    unit->decoder->computeRendering(FULLBUFLENGTH);
    
    SETCALC(Decoder3DBinaural_process);
  }

  static void Decoder3DBinaural_Dtor(Decoder3DBinaural * unit){
    RTFree(unit->mWorld, unit->decoder);
  }

  static void Decoder3DBinaural_process(Decoder3DBinaural * unit, int inNumSamples){
    
    Decoder<Hoa3d, float>::Binaural * tempDecoder = unit->decoder;

    int numHarmonics = unit->numberOfHarmonics;
    
    float ** input =  (float**)RTAlloc(unit->mWorld,sizeof(float*)*numHarmonics);

    for (int i = 0; i < numHarmonics; ++i) input[i] = IN(i+2);
    
    float ** output = (float**)RTAlloc(unit->mWorld, sizeof(float*)*2);

    output[0] = OUT(0);
    output[1] = OUT(1);
       
    tempDecoder->processBlock(const_cast<const float **>(input),output);

    RTFree(unit->mWorld,input);
    RTFree(unit->mWorld,output);
    
  }
  PluginLoad(Decoder){

    ft = inTable;
  
    DefineDtorUnit(Decoder2D);
    DefineDtorUnit(Decoder2DIrregular);
    DefineDtorUnit(Decoder2DBinaural);
    DefineDtorUnit(Decoder3D);
    DefineDtorUnit(Decoder3DBinaural);
  
  }
}
