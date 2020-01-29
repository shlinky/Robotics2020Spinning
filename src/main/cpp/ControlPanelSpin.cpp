

#include "ControlPanelSpin.h"

#include <iostream>

#include <frc/smartdashboard/SmartDashboard.h>

ControlPanelSpin::ControlPanelSpin()
{
    talon = new TalonSRX(TALONPORT);

    numRotations = 3;
}

/**
 * This function is called every robot packet, no matter the mode. Use
 * this for items like diagnostics that you want ran during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
bool ControlPanelSpin::setNumRotations(int num) {
    numRotations = num;
    return true;
}

bool ControlPanelSpin::startSpin() {
    if (mode == SpinMode::Rotation) {
        float rotationAmount = (cpCircum / wheelCircum) * numRotations;
        talon->Set(ControlMode::Position, rotationAmount);
    }
    return true;
}

bool ControlPanelSpin::setSpinMode(enum SpinMode m) {
    mode = m;
    return true;
}

bool ControlPanelSpin::checkIfComplete() {
    return true;
}
