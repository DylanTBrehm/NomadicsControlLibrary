
#ifndef PID_CPP
#define PID_CPP

#include "PID.hpp"

PID::PID(double proportionalConstant_, double integralConstant_, double derivativeConstant_)
{
    proportionalConstant = proportionalConstant_;
    integralConstant = integralConstant_;
    derivativeConstant = derivativeConstant_;
    state = 0;
    desiredState = 0;
    integralOutput = 0;
    PIDResult = 0;
    error = 0;
    saveError = 0;
    compareTime = 0;

    integralLowerBound = 0;
    integralUpperBound = 0;

    proportionalOutput = 0;
    integralOutput = 0;
    derivativeOutput = 0;

    integralDecayRate = 0.9995;

    for (int i = 0; i < DERIVATIVE_BUFFER_SIZE; i++)
    {
        derivativeBuffer[i] = 0;
    }
}

PID::PID(PID_Constants_t pidConstants)
{
    proportionalConstant = pidConstants.proportional;
    integralConstant = pidConstants.integral;
    derivativeConstant = pidConstants.derivative;

    state = 0;
    desiredState = 0;
    integralOutput = 0;
    PIDResult = 0;
    error = 0;
    saveError = 0;
    compareTime = 0;

    integralLowerBound = 0;
    integralUpperBound = 0;

    for (int i = 0; i < DERIVATIVE_BUFFER_SIZE; i++)
    {
        derivativeBuffer[i] = 0;
    }
}

PID::PID()
{
    proportionalConstant = 0;
    integralConstant = 0;
    derivativeConstant = 0;

    state = 0;
    desiredState = 0;
    integralOutput = 0;
    error = 0;
    compareTime = 0;

    integralLowerBound = 0;
    integralUpperBound = 0;
    PIDResult = 0;

    for (int i = 0; i < DERIVATIVE_BUFFER_SIZE; i++)
    {
        derivativeBuffer[i] = 0;
    }
}

PID::~PID()
{
}

// This sets the desired state
// This must be called before set state
// To be correct
void PID::setDesiredState(double desiredState_)
{
    desiredState = desiredState_;
}

void PID::setState(double state_)
{
    // setting the state updates all necessary error information
    // must set desired state first
    state = state_;
    error = desiredState - state;
    deltaError = error - saveError;
    saveError = error;
}

void PID::setDeltaTime()
{
    deltaTime = (micros() / 1000000.0) - compareTime;
    compareTime = (micros() / 1000000.0);
}

void PID::setConstantDeltaTime(double deltaTime_)
{
    deltaTime = deltaTime_;
}

void PID::calculateProportional()
{
    proportionalOutput = proportionalConstant * error;
}

void PID::calculateIntegral()
{
    integralOutput = integralOutput * (integralDecayRate) + integralConstant * error * deltaTime;
}

void PID::calculateBoundedIntegral(double lowerBound, double upperBound)
{
    integralOutput = integralOutput + integralConstant * error * deltaTime;

    if (integralOutput < lowerBound)
    {
        integralOutput = lowerBound;
    }
    else if (upperBound < integralOutput)
    {
        integralOutput = upperBound;
    }
}

void PID::calculateDerivative()
{
    double bufferSum = 0;
    double value = 0;

    derivativeOutput = derivativeConstant * (deltaError / deltaTime);
    // derivativeOutput =derivativeConstant * (deltaError / deltaTime);
}

void PID::sumPID()
{
    PIDResult = proportionalOutput + derivativeOutput + integralOutput;
}

void PID::setPIDConstants(double proportionalConstant_, double integralConstant_, double derivativeConstant_)
{
    proportionalConstant = proportionalConstant_;
    integralConstant = integralConstant_;
    derivativeConstant = derivativeConstant_;
}

void PID::setPIDConstants(PID_Constants_t pidConstants)
{
    proportionalConstant = pidConstants.proportional;
    integralConstant = pidConstants.integral;
    derivativeConstant = pidConstants.derivative;
}

void PID::setPIDConstantsNickZieg(double ultimateConstant, double responsePeriod)
{
    proportionalConstant = ultimateConstant * 0.33333;
    integralConstant = (0.66666 * ultimateConstant) / responsePeriod;
    derivativeConstant = 0.11111 * ultimateConstant * responsePeriod;
}

#endif // !PID_CPP