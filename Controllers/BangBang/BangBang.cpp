#include "BangBang.hpp"

// BangBang::BangBang(double bangMagnitude_, double deadbandWidth_)
// {
//     currentState = 0;
//     bangMagnitude = bangMagnitude_;
//     deadbandWidth = deadbandWidth_;
// }

// {
//     stabilityFlag = false;
//     currentState = 0;
//     bangMagnitude = bangMagnitude_;
//     lowerDeadBound = lowerDeadBound_;
//     upperDeadBound = upperDeadBound_;
// }

// BangBang

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

// double BangBang::getSemiDeadbandOutput(double state, double deadbandCenter)
// {

//     switch (semiDeadbandState)
//     {
//     case DEAD:
//         deadState();
//     case POSITIVE:
//         if (state < deadbandCenter)
//         {
//             semiDeadbandState = DEAD;
//         }
//         return -bangMagnitude;
//     case NEGATIVE:
//         if (state > deadbandCenter)
//         {
//             semiDeadbandState = DEAD;
//         }
//         return bangMagnitude;
//     }
// }

// double BangBang::deadState()
// {
//     if (state > deadbandCenter + deadbandWidth / 2)
//     {
//         semiDeadbandState = POSITIVE;
//         return 0;
//     }
//     else if (state < deadbandCenter - deadbandWidth / 2)
//     {
//         semiDeadbandState = NEGATIVE;
//         return 0;
//     }
//     else
//     {
//         return 0;
//     }
// }
