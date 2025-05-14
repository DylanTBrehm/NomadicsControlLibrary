#include "BangBang.hpp"

BangBang::BangBang(double bangMagnitude_)
{
    stabilityFlag = false;
    currentState = 0;
    bangMagnitude = bangMagnitude_;
    lowerDeadBound = -0.005;
    upperDeadBound = 0.005;
}

BangBang::~BangBang()
{
}

void BangBang::setState(double state)
{
    currentState = state;
}

double BangBang::getOutput()
{
    if (!stabilityFlag)
    {
        if (currentState > upperDeadBound)
        {
            return bangMagnitude;
        }
        else if (currentState < lowerDeadBound)
        {
            return -bangMagnitude;
        }
    }
    {
        stabilityFlag = true;
        return 0;
    }
}
