#ifndef RESETCONTROLLER_HPP
#define RESETCONTROLLER_HPP

#include <math.h>
#include "../PID/PID.hpp"
#include "../BangBang/BangBang.hpp"

class ResetController
{
private:
    BangBang bangBang;

public:
    ResetController(/* args */);
    ~ResetController();
    bool checkLimits(double railPosition);
    double getOutput(double railPosition);
};

#endif
