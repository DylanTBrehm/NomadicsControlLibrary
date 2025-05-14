
#ifndef PID_CPP
#define PID_CPP

#include "PID.hpp"

PID::PID(double proportionalConstant_, double integralConstant_, double derivativeConstant_)
{
    // Initializes the PID controller with given constants
    proportionalConstant = proportionalConstant_;
    integralConstant = integralConstant_;
    derivativeConstant = derivativeConstant_;

    // Initialize state variables
    state = 0;
    stateDot = 0;

    desiredState = 0;
    desiredStateDot = 0;

    error = 0;
    errorDot = 0;

    // Initialize time variables
    saveTime = 0;

    // Intialize integration variables
    integralOutput = 0;
    integralLowerBound = 0;
    integralUpperBound = 0;
    integralDecayRate = 0.9995;

    // Initialize output variables
    proportionalOutput = 0;
    integralOutput = 0;
    derivativeOutput = 0;
    PIDResult = 0;

    for (int i = 0; i < DERIVATIVE_BUFFER_SIZE; i++)
    {
        derivativeBuffer[i] = 0;
    }
}

PID::PID(PID_Constants_t pidConstants)
{
    // Initializes the PID controller with given constants
    proportionalConstant = pidConstants.proportional;
    integralConstant = pidConstants.integral;
    derivativeConstant = pidConstants.derivative;

    // Initialize state variables
    state = 0;
    stateDot = 0;
    saveState = 0;

    desiredState = 0;
    desiredStateDot = 0;
    saveDesiredState = 0;

    error = 0;
    errorDot = 0;

    // Initialize time variables
    saveTime = 0;

    // Intialize integration variables
    integralOutput = 0;
    integralLowerBound = 0;
    integralUpperBound = 0;
    integralDecayRate = 0.9995;

    // Initialize output variables
    proportionalOutput = 0;
    integralOutput = 0;
    derivativeOutput = 0;
    PIDResult = 0;

    for (int i = 0; i < DERIVATIVE_BUFFER_SIZE; i++)
    {
        derivativeBuffer[i] = 0;
    }
}

PID::PID()
{
    // Initializes the PID controller with default zeros
    proportionalConstant = 0;
    integralConstant = 0;
    derivativeConstant = 0;

    // Initialize state variables
    state = 0;
    stateDot = 0;

    desiredState = 0;
    desiredStateDot = 0;

    error = 0;
    errorDot = 0;

    // Initialize time variables
    saveTime = 0;

    // Intialize integration variables
    integralOutput = 0;
    integralLowerBound = 0;
    integralUpperBound = 0;
    integralDecayRate = 0.9995;

    // Initialize output variables
    proportionalOutput = 0;
    integralOutput = 0;
    derivativeOutput = 0;
    PIDResult = 0;

    for (int i = 0; i < DERIVATIVE_BUFFER_SIZE; i++)
    {
        derivativeBuffer[i] = 0;
    }
}

PID::~PID()
{
}

double PID::updateCtrlState(double state_, double time_)
{
    // setting the state updates all necessary error information
    // must set desired state first
    setTimeSeconds(time_);
    setState(state_);

    calcProportionalOutput();
    calcIntegralOutput();
    calcDerivativeOutput();
    sumPID();

    return PIDResult;
}

double PID::updateCtrlState(double state_, double stateDot_, double time_)
{
    // setting the state updates all necessary error information
    // must set desired state first
    setTimeSeconds(time_);
    setState(state_, stateDot_);

    calcProportionalOutput();
    calcIntegralOutput();
    calcDerivativeOutput();
    sumPID();

    return PIDResult;
}

double PID::updateCtrlSys(double state_, double desiredState_, double time_)
{
    // setting the state updates all necessary error information
    // must set desired state first
    setTimeSeconds(time_);
    setState(state_);
    setDesiredState(desiredState_);

    calcProportionalOutput();
    calcIntegralOutput();
    calcDerivativeOutput();
    sumPID();

    return PIDResult;
}

double PID::updateCtrlSys(double state_, double stateDot_, double desiredState_, double time_)
{
    // setting the state updates all necessary error information
    // must set desired state first
    setTimeSeconds(time_);
    setState(state_, stateDot_);
    setDesiredState(desiredState_);

    calcProportionalOutput();
    calcIntegralOutput();
    calcDerivativeOutput();
    sumPID();

    return PIDResult;
}

void PID::setDesiredState(double desiredState_)
{

    desiredState = desiredState_;
    deltaDesiredState = desiredState - saveDesiredState;
    saveDesiredState = desiredState;
    desiredStateDot = deltaDesiredState / deltaTime;
}

void PID::setState(double state_)
{
    // setting the state updates all necessary error information
    // must set desired state first
    state = state_;
    deltaState = state - saveState;
    saveState = state;
    stateDot = deltaState / deltaTime;

    error = desiredState - state;
    errorDot = desiredStateDot - stateDot;
}

void PID::setState(double state_, double stateDot_)
{
    // setting the state updates all necessary error information
    // must set desired state first
    state = state_;
    deltaState = state - saveState;
    saveState = state;
    stateDot = stateDot_;

    error = desiredState - state;
    errorDot = desiredStateDot - stateDot;

    // derivativeOutput = derivativeConstant * (stateDot_ - saveState);
    // saveState = stateDot_;
}

void PID::setTimeSeconds(double time_)
{
    deltaTime = time_ - saveTime;
    saveTime = time_;
}

void PID::setTimeMillis(uint64_t time_)
{
    deltaTime = (time_ / 1000.0) - saveTime;
    saveTime = (time_ / 1000.0);
}

void PID::setTimeMicros(uint64_t time_)
{
    deltaTime = (time_ / 1000000.0) - saveTime;
    saveTime = (time_ / 1000000.0);
}

void PID::setConstantDeltaTime(double deltaTime_)
{
    deltaTime = deltaTime_;
}

void PID::calcProportionalOutput()
{
    proportionalOutput = proportionalConstant * error;
}

void PID::calcIntegralOutput()
{
    integralOutput = integralOutput * (integralDecayRate) + integralConstant * error * deltaTime;
}

void PID::calcBoundedIntegralOutput(double lowerBound, double upperBound)
{
    calcIntegralOutput();

    if (integralOutput < lowerBound)
    {
        integralOutput = lowerBound;
    }
    else if (upperBound < integralOutput)
    {
        integralOutput = upperBound;
    }
}

void PID::calcDerivativeOutput()
{
    derivativeOutput = derivativeConstant * errorDot;
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

#endif // PID_CPP