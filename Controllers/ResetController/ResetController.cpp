#include "ResetController.hpp"

ResetController::ResetController(/* args */) : bangBang(3.5)
{
}

ResetController::~ResetController()
{
}

bool ResetController::checkLimits(double railPosition)
{
    double railLimit = 0.2067;
    if (fabs(railPosition) >= railLimit)
    {
        return true;
    }
    else
    {
        return false;
    }
}

double ResetController::getOutput(double railPosition)
{
    bangBang.setState(railPosition);

    return bangBang.getOutput();
}
