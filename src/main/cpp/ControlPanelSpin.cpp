

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
    
    static constexpr auto i2cPort = frc::I2C::Port::kOnboard;
    m_colorSensor = new rev::ColorSensorV3(i2cPort);

    m_colorMatcher.AddColorMatch(kBlueTarget);
    m_colorMatcher.AddColorMatch(kGreenTarget);
    m_colorMatcher.AddColorMatch(kRedTarget);
    m_colorMatcher.AddColorMatch(kYellowTarget);
}


bool ControlPanelSpin::setNumRotations(int num) {
    numRotations = num;
    return true;
}

bool ControlPanelSpin::setCurrentColorTarget(frc::Color target) {
    currentTarget = target;
    return true;
}

bool ControlPanelSpin::startSpin() {
    if (mode == SpinMode::Rotation) {
        frc::DriverStation::ReportError(std::to_string(talon->GetSelectedSensorPosition(0)));
        if (talon->GetSelectedSensorPosition(0) == 0) {
            float rotationAmount = (cpCircum / wheelCircum) * numRotations * ticksPerRotation;
            talon->Set(ControlMode::Position, rotationAmount);
        }
    }
    else {
        talon->Set(ControlMode::PercentOutput, 0.5);
    }
    return true;
}

bool ControlPanelSpin::setSpinMode(enum SpinMode m) {
    mode = m;
    return true;
}

bool ControlPanelSpin::checkIfComplete() {
    if (mode == SpinMode::Rotation) {
        if (talon->GetSelectedSensorPosition(0) >= ((cpCircum / wheelCircum) * numRotations * ticksPerRotation)) {
            talon->SetSelectedSensorPosition(0, 0);
            return true;
        }
        return false;
    }
    else {
        frc::Color detectedColor = m_colorSensor->GetColor();
        double confidence = 0.0;
        frc::Color matchedColor = m_colorMatcher.MatchClosestColor(detectedColor, confidence);

        if (matchedColor == currentTarget) {
            talon->Set(ControlMode::PercentOutput, 0);
            return true;
        }
        return false;
    }
}
