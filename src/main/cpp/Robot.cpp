/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"

#include <iostream>

#include <frc/smartdashboard/SmartDashboard.h>

#include "frc/DriverStation.h"

void Robot::RobotInit() {
  m_chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
  m_chooser.AddOption(kAutoNameCustom, kAutoNameCustom);
  frc::SmartDashboard::PutData("Auto Modes", &m_chooser);

  joystick = new frc::Joystick(JOYSTICKPORT);
  action = new frc::JoystickButton(joystick, 1);
  action1 = new frc::JoystickButton(joystick, 2);

  cps = ControlPanelSpin();
  cps.setSpinMode(SpinMode::Rotation);
  cps.setCurrentColorTarget(ControlPanelSpin::kRedTarget);
}

/**
 * This function is called every robot packet, no matter the mode. Use
 * this for items like diagnostics that you want ran during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic() {
  
}

void Robot::TeleopInit() {}
void Robot::TeleopPeriodic() {
  if (action->Get()) {
    cps.startSpin();
  }
  if (action1->Get()) {
    if (cps.getSpinMode() == SpinMode::Rotation) {
      cps.setSpinMode(SpinMode::ColorDetection);
    }
    else {
      cps.setSpinMode(SpinMode::Rotation);
    }
  }
  cps.checkIfComplete();
}
#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
