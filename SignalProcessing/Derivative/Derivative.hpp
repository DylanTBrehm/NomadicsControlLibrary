#ifndef DERIVATIVE_HPP
#define DERIVATIVE_HPP

class Derivative
{
protected:
    // State variables
    double state;
    double prevState;
    double deltaState;

    // Time variables
    double time;
    double prevTime;
    double deltaTime;

    // Derivative variables
    double derivative;
    double prevDerivative;

public:
    // Constructors/Destructors
    Derivative();
    ~Derivative();

    // Primary functions
    double calcDerivative(double deltaState_, double deltaTime_);
    double updateDerivative(double state_, double time_);
    double updateDerivativeLagOut(double state_, double time_);

    // Setters
    void setTime(double time_);
    void setState(double state_);

    // Getters
    double getDerivative();
    double getPrevDerivative();
};

#endif