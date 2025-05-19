#ifndef BANGBANG_HPP
#define BANGBANG_HPP
#include <Arduino.h>
#include <cmath>

// enum SemiDeadbandState
// {
//     DEAD,
//     POSITIVE,
//     NEGATIVE
// };

class BangBang
{
private:
    double currentState;
    double bangMagnitude;
    double lowerDeadBound;
    double upperDeadBound;
    double deadbandWidth;
    bool stabilityFlag;

    // SemiDeadbandState semiDeadbandState;

public:
    // BangBang(double bangMagnitude_, double deadbandWidth_);
    // BangBang(double bangMagnitude_, double lowerDeadBound_ = -0.005, double upperDeadBound_ = 0.005);
    BangBang(double bangMagnitude_);
    ~BangBang();
    void setState(double state);
    double getOutput();
    double boundOutput(double output);

    double updateSemiDeadbandState(double state, double deadbandCenter);
    double calcSemiDeadbandCtrl(double state, double deadbandCenter);
    double deadState();
    double positiveState();
    double negativeState();
};

#endif