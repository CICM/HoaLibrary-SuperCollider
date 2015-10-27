#include "SC_PlugIn.h"
#include "Encoder.hpp"

static InterfaceTable * ft;

namespace hoa{

  struct Encoder2D : public Unit {
    Encoder<Hoa2d, float>::DC * encoder;

    float * output;
    
    int numberOfHarmonics;
  };
  
  struct Encoder3D : public Unit {
    Encoder<Hoa3d, float>::DC * encoder;

    float * output;
    
    int numberOfHarmonics;
  };


  static void Encoder2D_process(Encoder2D * unit, int inNumSamples);
    
  static void Encoder2D_Ctor(Encoder2D * unit);
  
  static void Encoder2D_Dtor(Encoder2D * unit);


  static void Encoder3D_process(Encoder3D * unit, int inNumSamples);
    
  static void Encoder3D_Ctor(Encoder3D * unit);
  
  static void Encoder3D_Dtor(Encoder3D * unit);


  
  // FUNC DEFS
  static void Encoder2D_Ctor(Encoder2D * unit){

    float order = IN0(3);
    
    unit->encoder = (Encoder<Hoa2d,float>::DC *)RTAlloc(unit->mWorld,sizeof(Encoder<Hoa2d,float>::DC(order)));

    new(unit->encoder) Encoder<Hoa2d,float>::DC(order);
    
    unit->numberOfHarmonics = order*2+1;
    
    unit->output = (float*)RTAlloc(unit->mWorld,sizeof(float)* FULLBUFLENGTH * unit->numberOfHarmonics);
    
    unit->encoder->setAzimuth(IN0(1));

    unit->encoder->setRadius(IN0(2));

    unit->encoder->setMute(false);

    SETCALC(Encoder2D_process);
    
    Encoder2D_process(unit,1);
  }

  static void Encoder2D_Dtor(Encoder2D * unit){
    RTFree(unit->mWorld, unit->encoder);
    RTFree(unit->mWorld, unit->output);
  }

  static void Encoder2D_process(Encoder2D * unit, int inNumSamples){
    
    Encoder<Hoa2d, float>::DC * tempEncoder = unit->encoder;
    
    float * input = IN(0);
	
    float * azimuth = IN(1);
    
    float * radius = IN(2);
    
    int numHarmonics = unit->numberOfHarmonics;
    
    float * tempOutput = unit->output;
    
    if(*azimuth != tempEncoder->getAzimuth()) tempEncoder->setAzimuth(*azimuth);
    
    if(*radius != tempEncoder->getRadius()) tempEncoder->setRadius(*radius);
       
    for (int i = 0; i < inNumSamples; ++i){
	
	tempEncoder->process(input+i, tempOutput + i * numHarmonics);
    }
    
    for(int i = 0; i < inNumSamples; ++i){
      for (int j = 0; j< numHarmonics; ++j){
	float * out = 	OUT(j);
	out[i] = tempOutput[i * numHarmonics + j];
      }
    }
  }

  // FUNC DEFS
  static void Encoder3D_Ctor(Encoder3D * unit){

    float * azimuth = IN(1);
    
    float * elevation = IN(2);
    
    float * radius = IN(3);

    float order = IN0(4);
    
    unit->encoder = (Encoder<Hoa3d,float>::DC *)RTAlloc(unit->mWorld,sizeof(Encoder<Hoa3d,float>::DC(order)));

    new(unit->encoder) Encoder<Hoa3d,float>::DC(order);
    
    unit->numberOfHarmonics = (order+1) * (order+1);
    
    unit->output = (float*)RTAlloc(unit->mWorld,sizeof(float)* FULLBUFLENGTH * unit->numberOfHarmonics);
    
    unit->encoder->setAzimuth(*azimuth);
    
    unit->encoder->setElevation(*elevation);

    unit->encoder->setRadius(*radius);

    unit->encoder->setMute(false);

    SETCALC(Encoder3D_process);
    
    Encoder3D_process(unit,1);
  }

  static void Encoder3D_Dtor(Encoder3D * unit){
    RTFree(unit->mWorld, unit->encoder);
    RTFree(unit->mWorld, unit->output);
  }

  static void Encoder3D_process(Encoder3D * unit, int inNumSamples){
    
    Encoder<Hoa3d, float>::DC * tempEncoder = unit->encoder;
    
    float * input = IN(0);
	
    float * azimuth = IN(1);
    
    float * elevation = IN(2);
    
    float * radius = IN(3);
    
    int numHarmonics = unit->numberOfHarmonics;
    
    float * tempOutput = unit->output;
    
    if(*azimuth != tempEncoder->getAzimuth()) tempEncoder->setAzimuth(*azimuth);

    if(*elevation != tempEncoder->getElevation()) tempEncoder->setElevation(*elevation);
    
    if(*radius != tempEncoder->getRadius()) tempEncoder->setRadius(*radius);
       
    for (int i = 0; i < inNumSamples; ++i){
	
	tempEncoder->process(input+i, tempOutput + i * numHarmonics);
    }
    
    for(int i = 0; i < inNumSamples; ++i){
      for (int j = 0; j< numHarmonics; ++j){
	float * out = 	OUT(j);
	out[i] = tempOutput[i * numHarmonics + j];
      }
    }
  }

  PluginLoad(Encoder){

    ft = inTable;
  
    DefineDtorUnit(Encoder2D);
    DefineDtorUnit(Encoder3D);
  
  }
}
