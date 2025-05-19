#ifndef INTEGRATOR_HPP
#define INTEGRATOR_HPP
#include <Arduino.h>
#include <cmath>

class Integrator
{
private:
    double state;
    double prevState;
    double integralAccumulator;
    double boundWidth;

    double prevTime;
    double time;

    double deltaTime;
    double decayRate;

    bool firstIntegration = true;

public:
    Integrator();
    Integrator(double decayRate_);
    Integrator(double boundWidth_, double decayRate_);
    ~Integrator();

    double integrate(double state_, double time_);
    double boundValue(double value, double lowerBound, double upperBound);

    double getOutput();
    double getDecayRate();
    double getDeltaTime();

    void setDecayRate(double decayRate_);
};

#endif