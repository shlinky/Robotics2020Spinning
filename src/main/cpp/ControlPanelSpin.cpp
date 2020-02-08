

#include "ControlPanelSpin.h"

#include <iostream>

#include <frc/smartdashboard/SmartDashboard.h>
#include "frc/DriverStation.h"
#include <string>

ControlPanelSpin::ControlPanelSpin()
{
    talon = new TalonSRX(TALONPORT);
    
    numRotations = 3;

    talon->SetSelectedSensorPosition(0, 0);
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
        if (talon->GetSelectedSensorPosition(0) == 0) {
            frc::DriverStation::ReportError(std::to_string(talon->GetSelectedSensorPosition(0)));
            float rotationAmount = (cpCircum / wheelCircum) * numRotations * ticksPerRotation;
            talon->Set(ControlMode::Position, rotationAmount);
        }
    }
    return true;
}

bool ControlPanelSpin::setSpinMode(enum SpinMode m) {
    mode = m;
    return true;
}

bool ControlPanelSpin::checkIfComplete() {
    if (mode == SpinMode::Rotation) {
        if (talon->GetSelectedSensorPosition(0) == ((cpCircum / wheelCircum) * numRotations * ticksPerRotation)) {
            talon->SetSelectedSensorPosition(0, 0);
        }
    }
}
