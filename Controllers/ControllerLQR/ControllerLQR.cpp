#include "controllerLQR.hpp"

ControllerLQR::ControllerLQR(Eigen::MatrixXd controllerGain_)
{
    controllerGain = controllerGain_;
    numberOfOutputs = controllerGain.rows(); 
    numberOfStates = controllerGain.cols();
    stateVector = Eigen::VectorXd::Zero(numberOfStates);
    outputVector = Eigen::VectorXd::Zero(numberOfOutputs);
}

ControllerLQR::ControllerLQR(uint16_t numberOfStates_, uint16_t numberOfOutputs_)
{

    numberOfOutputs = numberOfOutputs_;
    numberOfStates = numberOfStates_;

    controllerGain = Eigen::MatrixXd::Zero(numberOfOutputs_, numberOfStates_);
}

void ControllerLQR::setControllerGain(Eigen::MatrixXd controllerGain_)
{
    controllerGain = controllerGain_;
}

void ControllerLQR::setState(Eigen::VectorXd stateVector_)
{
    stateVector = stateVector_;
}

void ControllerLQR::calculateControlOutput()
{
    outputVector = controllerGain * stateVector;
}

Eigen::VectorXd ControllerLQR::getControlOutput()
{
    return outputVector;
}

ControllerLQR::~ControllerLQR()
{
}