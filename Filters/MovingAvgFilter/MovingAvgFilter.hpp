#ifndef MOVING_AVG_FILTER
#define MOVING_AVG_FILTER

#include <stdint.h>
#define MAX_NUMBER_OF_TAPS 200

class MovingAvgFilter
{
private:
    double delayTaps[MAX_NUMBER_OF_TAPS];
    uint16_t numberOfTaps;

public:
    MovingAvgFilter();
    MovingAvgFilter(uint16_t numberOfTaps_);
    ~MovingAvgFilter();

    double filterSignal(double inputTap);
};

#endif