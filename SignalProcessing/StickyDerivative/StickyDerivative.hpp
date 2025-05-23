#ifndef STICKY_DERIVATIVE_HPP
#define STICKY_DERIVATIVE_HPP
#include "../Derivative/Derivative.hpp"

class StickyDerivative : public Derivative
{

private:
    double timeTillZero;

public:
    // Constructors/Destructors
    StickyDerivative();

    // Primary functions
    double updateDerivative(double state_, double time_);
};

#endif