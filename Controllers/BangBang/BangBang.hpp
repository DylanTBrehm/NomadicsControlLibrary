#ifndef BANGBANG_HPP
#define BANGBANG_HPP
#include <Arduino.h>
#include <cmath>
class BangBang
{
private:
    double currentState;
    double bangMagnitude;
    double lowerDeadBound;
    double upperDeadBound;
    bool stabilityFlag;

public:
    BangBang(double bangMagnitude_);
    ~BangBang();
    void setState(double state);
    double getOutput();
    double boundOutput(double output);
};

#endif