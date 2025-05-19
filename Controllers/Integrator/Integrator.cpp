#include "Integrator.hpp"

Integrator::Integrator()
{
    // Time Variables
    time = 0;
    prevTime = 0;
    deltaTime = 0;

    // State Variables
    prevState = 0;
    state = 0;

    // Integration Variables
    integralAccumulator = 0;
    decayRate = 1;
    boundWidth = 0;
}

Integrator::Integrator(double decayRate_)
{

    // Time Variables
    time = 0;
    prevTime = 0;
    deltaTime = 0;

    // State Variables
    prevState = 0;
    state = 0;

    // Integration Variables
    integralAccumulator = 0;
    decayRate = decayRate_;
    boundWidth = 0;
}

Integrator::Integrator(double boundWidth_, double decayRate_)
{
    // Time Variables
    time = 0;
    prevTime = 0;
    deltaTime = 0;

    // State Variables
    prevState = 0;
    state = 0;

    // Integration Variables
    integralAccumulator = 0;
    decayRate = decayRate_;
    boundWidth = boundWidth_;
}

Integrator::~Integrator()
{
}

double Integrator::integrate(double state_, double time_)
{
    // Update time
    prevTime = time;
    time = time_;

    if (firstIntegration)
    {
        deltaTime = 0;
        firstIntegration = false;
    }
    else
    {
        deltaTime = time - prevTime;
    }

    // Update state
    prevState = state;
    state = state_;

    // Integrate
    integralAccumulator = integralAccumulator * decayRate + ((prevState + state) * deltaTime) / 2;

    // if (boundWidth != 0)
    // {
    //     // Bound the integral accumulator
    //     integralAccumulator = boundValue(integralAccumulator, -boundWidth / 2, boundWidth / 2);
    // }

    return integralAccumulator;
}

// double Integrator::integrate(double state_, double time_)
// {

//     // Update time
//     prevTime = time;
//     time = time_;

//     if (firstIntegration)
//     {
//         deltaTime = 0;
//     }
//     else
//     {
//         deltaTime = (time - prevTime);
//     }

//     integralAccumulator = integralAccumulator * decayRate + state_ * deltaTime;
//     // Update state
//     prevState = state;
//     state = state_;

//     // Integrate

//     // if (boundWidth != 0)
//     // {
//     //     // Bound the integral accumulator
//     //     integralAccumulator = boundValue(integralAccumulator, -boundWidth / 2, boundWidth / 2);
//     // }

//     return integralAccumulator;
// }

double Integrator::boundValue(double value, double lowerBound, double upperBound)
{
    if (value >= upperBound)
    {
        return upperBound;
    }
    else if (value <= lowerBound)
    {
        return lowerBound;
    }
    else
    {
        return value;
    }
}

double Integrator::getOutput()
{
    return integralAccumulator;
}

double Integrator::getDecayRate()
{
    return decayRate;
}

double Integrator::getDeltaTime()
{
    return deltaTime;
}