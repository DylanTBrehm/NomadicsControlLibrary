#include "Derivative.hpp"

/////////////////////////////////////////////////
////         Construnctors/Destructors       ////
/////////////////////////////////////////////////
Derivative::Derivative(/* args */)
{
    state = 0;
    prevState = 0;
    deltaState = 0;

    time = 0;
    prevTime = 0;
    deltaTime = 0;

    derivative = 0;
    prevDerivative = 0;
}

Derivative::~Derivative()
{
}

/////////////////////////////////////////////////
////             Primary Functions           ////
/////////////////////////////////////////////////

double Derivative::updateDerivative(double state_, double time_)
{
    setState(state_);
    setTime(time_);
    calcDerivative(deltaState, deltaTime);
    return derivative;
}

double Derivative::updateDerivativeLagOut(double state_, double time_)
{
    updateDerivative(state_, time_);
    return prevDerivative;
}

double Derivative::calcDerivative(double deltaState_, double deltaTime_)
{
    prevDerivative = derivative;
    derivative = deltaState / deltaTime;
    return derivative;
}

/////////////////////////////////////////////////
////                 Setters                 ////
/////////////////////////////////////////////////

void Derivative::setState(double state_)
{
    prevState = state;
    state = state_;
    deltaState = state - prevState;
}

void Derivative::setTime(double time_)
{
    prevTime = time;
    time = time_;
    deltaTime = time - prevTime;
}

/////////////////////////////////////////////////
////                 Getters                 ////
/////////////////////////////////////////////////

double Derivative::getDerivative()
{
    return derivative;
}

double Derivative::getPrevDerivative()
{
    return prevDerivative;
}