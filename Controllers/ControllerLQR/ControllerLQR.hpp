#ifndef CONTROLLER_LQR
#define CONTROLLER_LQR

#include <ArduinoEigenDense.h>
#include <cstdint>
class ControllerLQR
{
private:
    uint16_t numberOfOutputs;
    uint16_t numberOfStates;
    Eigen::MatrixXd controllerGain;
    Eigen::VectorXd stateVector;
    Eigen::VectorXd outputVector;
    

public:
    ControllerLQR(Eigen::MatrixXd initialControllerGain);
    ControllerLQR(uint16_t numberOfStates_, uint16_t numberOfOutputs_);
    ~ControllerLQR();

    void setControllerGain(Eigen::MatrixXd controllerGain_);
    void setState(Eigen::VectorXd stateVector_);
    void calculateControlOutput();
    Eigen::VectorXd getControlOutput();
};

#endif
