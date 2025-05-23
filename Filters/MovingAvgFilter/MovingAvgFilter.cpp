#include "MovingAvgFilter.hpp"

MovingAvgFilter::MovingAvgFilter(uint16_t numberOfTaps_)
{
    if (numberOfTaps_ > MAX_NUMBER_OF_TAPS)
    {
        numberOfTaps = numberOfTaps_;
    }
    else
    {
        numberOfTaps = MAX_NUMBER_OF_TAPS;
    }
}

MovingAvgFilter::MovingAvgFilter()
{
    numberOfTaps = 1;
}

MovingAvgFilter::~MovingAvgFilter()
{
}

double MovingAvgFilter::filterSignal(double inputTap)
{
    double accum = inputTap;
    for (int i = 1; i < numberOfTaps; i++)
    {
        delayTaps[i] = delayTaps[i - 1];
        accum = accum + delayTaps[i - 1];
    }
    delayTaps[0] = inputTap;

    return accum / numberOfTaps;
}