#ifndef PID_HPP
#define PID_HPP

#define FLIGHT_MODE

#ifdef FLIGHT_MODE
#include <Arduino.h>
#include <stdint.h>
#endif

#ifdef SIMULATION_MODE
#include "..\..\..\time.hpp"
#include "FilterFIR.hpp"
#endif

#define DERIVATIVE_BUFFER_SIZE 100

typedef struct
{
    double proportional;
    double integral;
    double derivative;
} PID_Constants_t;

class PID
{
private:
    // Bounds for integral to prevent windup
    double integralUpperBound;
    double integralLowerBound;
    double integralDecayRate;

    // State information for PID calculation
    double state;
    double stateDot;
    double deltaState;
    double saveState;

    double error;
    double errorDot;

    double desiredState;
    double desiredStateDot;
    double deltaDesiredState;
    double saveDesiredState;

    // deltas for calculus computation
    double time;
    double deltaTime;
    double saveTime;

    // Result information
    double PIDResult;

    // If you dont know what these are ur just bad
    double proportionalConstant, integralConstant, derivativeConstant;
    double proportionalOutput, integralOutput, derivativeOutput;
    double derivativeBuffer[DERIVATIVE_BUFFER_SIZE];
    double deltaError;

public:
    // My heart beats, my lungs breath, yet I do not live
    //  - Proker 1
    PID(double proportionalConstant_, double integralConstant_, double derivativeConstant_);
    PID(PID_Constants_t pidConstants);
    PID();
    ~PID();

    double updateCtrlState(double state_, double time_);
    double updateCtrlState(double state_, double stateDot_, double time_);

    double updateCtrlSys(double state_, double desiredState_, double time_);
    double updateCtrlSys(double state_, double stateDot_, double desiredState_, double time_);

    // These update the stored state information
    void setDesiredState(double currentDesiredState_);
    void setState(double state_);
    void setState(double state_, double stateDot_);

    void setPIDConstants(double proportionalConstant, double integralConstant, double derivativeConstant);
    void setPIDConstants(PID_Constants_t pidConstants);
    void setPIDConstantsNickZieg(double ultimateConstant, double responsePeriod);

    void setTime();
    void setTimeSeconds(double time_);
    void setTimeMillis(uint64_t time_);
    void setTimeMicros(uint64_t time_);
    void setConstantDeltaTime(double deltaTime_);

    // Calculate proportional, integral, and derivative seperatly
    // then sum with sumPID to calculate output
    void calcProportionalOutput();
    void calcIntegralOutput();
    void calcBoundedIntegralOutput(double lowerBound, double upperBound); // this calculates integral with bounds
    void calcDerivativeOutput();
    void sumPID();

    // Retreive PID sum result
    double getPIDResult() { return PIDResult; }
    double getProportionalOutput() { return proportionalOutput; }
    double getIntegralOutput() { return integralOutput; }
    double getDerivativeOutput() { return derivativeOutput; }
};

#endif