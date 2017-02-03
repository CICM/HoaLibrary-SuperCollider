#include "SC_PlugIn.h"
#include <Optim.hpp>

static InterfaceTable * ft;

namespace hoa{

    // OPTIM MAXRE
    struct Optim2DMaxRe : public Unit {

        Optim<Hoa2d, float>::MaxRe * optim;
        float * input, * output;
        int numberOfHarmonics;
    };

    // OPTIM MAXRE
    struct Optim3DMaxRe : public Unit {

        Optim<Hoa3d, float>::MaxRe * optim;
        float * input, * output;
        int numberOfHarmonics;
    };

    // OPTIM MAXRE
    struct Optim2DInPhase : public Unit {

        Optim<Hoa2d, float>::InPhase * optim;
        float * input, * output;
        int numberOfHarmonics;
    };

    // OPTIM MAXRE
    struct Optim3DInPhase : public Unit {

        Optim<Hoa3d, float>::InPhase * optim;
        float * input, * output;
        int numberOfHarmonics;
    };

    static void Optim2DMaxRe_process(Optim2DMaxRe * unit, int inNumSamples);

    static void Optim2DMaxRe_Ctor(Optim2DMaxRe * unit);

    static void Optim2DMaxRe_Dtor(Optim2DMaxRe * unit);

    static void Optim3DMaxRe_process(Optim3DMaxRe * unit, int inNumSamples);

    static void Optim3DMaxRe_Ctor(Optim3DMaxRe * unit);

    static void Optim3DMaxRe_Dtor(Optim3DMaxRe * unit);

    static void Optim2DInPhase_process(Optim2DInPhase * unit,
            int inNumSamples);

    static void Optim2DInPhase_Ctor(Optim2DInPhase * unit);

    static void Optim2DInPhase_Dtor(Optim2DInPhase * unit);

    static void Optim3DInPhase_process(Optim3DInPhase * unit,
            int inNumSamples);

    static void Optim3DInPhase_Ctor(Optim3DInPhase * unit);

    static void Optim3DInPhase_Dtor(Optim3DInPhase * unit);

    // FUNC DEFS
    static void Optim2DMaxRe_Ctor(Optim2DMaxRe * unit){

        int order = IN0(0);

       unit->optim = (Optim<Hoa2d,float>::MaxRe*)RTAlloc(unit->mWorld,
               sizeof(Optim<Hoa2d,float>::MaxRe(order)));

        new(unit->optim) Optim<Hoa2d,float>::MaxRe(order);

        unit->numberOfHarmonics = order*2+1;

        unit->input = (float*)RTAlloc(unit->mWorld,
                sizeof(float)* unit->numberOfHarmonics * FULLBUFLENGTH);

        unit->output = (float*)RTAlloc(unit->mWorld,
                sizeof(float)* unit->numberOfHarmonics * FULLBUFLENGTH);

        SETCALC(Optim2DMaxRe_process);

        Optim2DMaxRe_process(unit,1);
    }

    static void Optim2DMaxRe_Dtor(Optim2DMaxRe * unit){
        RTFree(unit->mWorld, unit->optim);
        RTFree(unit->mWorld, unit->input);
        RTFree(unit->mWorld, unit->output);
    }

    static void Optim2DMaxRe_process(Optim2DMaxRe * unit, int inNumSamples){

        Optim<Hoa2d, float>::MaxRe * tempOptim = unit->optim;

        int numHarmonics = unit->numberOfHarmonics;

        float * inputs = unit->input;

        float * outputs = unit->output;


        for (int i = 0; i<inNumSamples; ++i){
            for (int j = 0; j<numHarmonics; ++j){
                inputs[i*numHarmonics + j] = IN(j+1)[i];
            }
        }

        for (int i = 0; i < inNumSamples; ++i){
            tempOptim->process(inputs + i * numHarmonics,
                    outputs + i * numHarmonics);
        }

        for(int i = 0; i < inNumSamples; ++i){
            for (int j = 0; j< numHarmonics; ++j){
                float * out = OUT(j);
                out[i] = outputs[i * numHarmonics + j];
            }
        }
    }


    static void Optim3DMaxRe_Ctor(Optim3DMaxRe * unit){

        int order = IN0(0);

        unit->optim = (Optim<Hoa3d,float>::MaxRe*)RTAlloc(unit->mWorld,
                sizeof(Optim<Hoa3d,float>::MaxRe(order)));

        new(unit->optim) Optim<Hoa3d,float>::MaxRe(order);

        unit->numberOfHarmonics = (order +1) * (order + 1);

        unit->input = (float*)RTAlloc(unit->mWorld,
                sizeof(float)* unit->numberOfHarmonics * FULLBUFLENGTH);

        unit->output = (float*)RTAlloc(unit->mWorld,
                sizeof(float)* unit->numberOfHarmonics * FULLBUFLENGTH);

        SETCALC(Optim3DMaxRe_process);

        Optim3DMaxRe_process(unit,1);
    }

    static void Optim3DMaxRe_Dtor(Optim3DMaxRe * unit){
        RTFree(unit->mWorld, unit->optim);
        RTFree(unit->mWorld, unit->input);
        RTFree(unit->mWorld, unit->output);
    }

    static void Optim3DMaxRe_process(Optim3DMaxRe * unit, int inNumSamples){

        Optim<Hoa3d, float>::MaxRe * tempOptim = unit->optim;

        int numHarmonics = unit->numberOfHarmonics;

        float * inputs = unit->input;

        float * outputs = unit->output;


        for (int i = 0; i<inNumSamples; ++i){
            for (int j = 0; j<numHarmonics; ++j){
                inputs[i*numHarmonics + j] = IN(j+1)[i];
            }
        }

        for (int i = 0; i < inNumSamples; ++i){
            tempOptim->process(inputs + i * numHarmonics,
                    outputs + i * numHarmonics);
        }

        for(int i = 0; i < inNumSamples; ++i){
            for (int j = 0; j< numHarmonics; ++j){
                float * out = OUT(j);
                out[i] = outputs[i * numHarmonics + j];
            }
        }
    }


    static void Optim2DInPhase_Ctor(Optim2DInPhase * unit){

        int order = IN0(0);

        unit->optim = (Optim<Hoa2d,float>::InPhase*)RTAlloc(unit->mWorld,
                sizeof(Optim<Hoa2d,float>::InPhase(order)));

        new(unit->optim) Optim<Hoa2d,float>::InPhase(order);

        unit->numberOfHarmonics = order*2+1;

        unit->input = (float*)RTAlloc(unit->mWorld,
                sizeof(float)* unit->numberOfHarmonics * FULLBUFLENGTH);

        unit->output = (float*)RTAlloc(unit->mWorld,
                sizeof(float)* unit->numberOfHarmonics * FULLBUFLENGTH);

        SETCALC(Optim2DInPhase_process);

        Optim2DInPhase_process(unit,1);
    }

    static void Optim2DInPhase_Dtor(Optim2DInPhase * unit){
        RTFree(unit->mWorld, unit->optim);
        RTFree(unit->mWorld, unit->input);
        RTFree(unit->mWorld, unit->output);
    }

    static void Optim2DInPhase_process(Optim2DInPhase * unit,
            int inNumSamples){

        Optim<Hoa2d, float>::InPhase * tempOptim = unit->optim;

        int numHarmonics = unit->numberOfHarmonics;

        float * inputs = unit->input;

        float * outputs = unit->output;


        for (int i = 0; i<inNumSamples; ++i){
            for (int j = 0; j<numHarmonics; ++j){
                inputs[i*numHarmonics + j] = IN(j+1)[i];
            }
        }

        for (int i = 0; i < inNumSamples; ++i){
            tempOptim->process(inputs + i * numHarmonics,
                    outputs + i * numHarmonics);
        }

        for(int i = 0; i < inNumSamples; ++i){
            for (int j = 0; j< numHarmonics; ++j){
                float * out = OUT(j);
                out[i] = outputs[i * numHarmonics + j];
            }
        }
    }


    static void Optim3DInPhase_Ctor(Optim3DInPhase * unit){

        int order = IN0(0);

        unit->optim = (Optim<Hoa3d,float>::InPhase*)RTAlloc(unit->mWorld,
                sizeof(Optim<Hoa3d,float>::InPhase(order)));

        new(unit->optim) Optim<Hoa3d,float>::InPhase(order);

        unit->numberOfHarmonics = (order +1) * (order + 1);

        unit->input = (float*)RTAlloc(unit->mWorld,
                sizeof(float)* unit->numberOfHarmonics * FULLBUFLENGTH);

        unit->output = (float*)RTAlloc(unit->mWorld,
                sizeof(float)* unit->numberOfHarmonics * FULLBUFLENGTH);

        SETCALC(Optim3DInPhase_process);

        Optim3DInPhase_process(unit,1);
    }

    static void Optim3DInPhase_Dtor(Optim3DInPhase * unit){
        RTFree(unit->mWorld, unit->optim);
        RTFree(unit->mWorld, unit->input);
        RTFree(unit->mWorld, unit->output);
    }

    static void Optim3DInPhase_process(Optim3DInPhase * unit,
            int inNumSamples){

        Optim<Hoa3d, float>::InPhase * tempOptim = unit->optim;

        int numHarmonics = unit->numberOfHarmonics;

        float * inputs = unit->input;

        float * outputs = unit->output;


        for (int i = 0; i<inNumSamples; ++i){
            for (int j = 0; j<numHarmonics; ++j){
                inputs[i*numHarmonics + j] = IN(j+1)[i];
            }
        }

        for (int i = 0; i < inNumSamples; ++i){
            tempOptim->process(inputs + i * numHarmonics,
                    outputs + i * numHarmonics);
        }

        for(int i = 0; i < inNumSamples; ++i){
            for (int j = 0; j< numHarmonics; ++j){
                float * out = OUT(j);
                out[i] = outputs[i * numHarmonics + j];
            }
        }
    }

    PluginLoad(Optim){

        ft = inTable;

        DefineDtorUnit(Optim2DMaxRe);
        DefineDtorUnit(Optim3DMaxRe);
        DefineDtorUnit(Optim2DInPhase);
        DefineDtorUnit(Optim3DInPhase);

    }
}
