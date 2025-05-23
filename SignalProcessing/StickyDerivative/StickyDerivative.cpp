#include "StickyDerivative.hpp"
/////////////////////////////////////////////////
////         Construnctors/Destructors       ////
/////////////////////////////////////////////////
StickyDerivative::StickyDerivative()
{
    timeTillZero = .1; // Units: [s]
}

/////////////////////////////////////////////////
////             Primary Functions           ////
/////////////////////////////////////////////////

double StickyDerivative::updateDerivative(double state_, double time_)
{
    setState(state_);

    // Calculate derivative only when state changes
    if (prevState != state)
    {
        setTime(time_);
        calcDerivative(deltaState, deltaTime);
    }

    // Set derivative to zero after enough time
    // if ((time_ - time) >= timeTillZero)
    // {
    //     derivative = 0;
    // }

    return derivative;
}