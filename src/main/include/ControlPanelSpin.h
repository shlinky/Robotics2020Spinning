#pragma once

#include <string>

#include <frc/smartdashboard/SendableChooser.h>
#include <frc/buttons/JoystickButton.h>
#include <frc/Joystick.h>
#include <ctre/phoenix.h>

#define wheelCircum (4 * 3.1)
#define cpCircum (100)
#define ticksPerRotation (50)
#define TALONPORT (0)

enum SpinMode {Rotation = 0, ColorDetection = 1};

class ControlPanelSpin {
 public:
  ControlPanelSpin();
  bool setNumRotations(int num);
  bool startSpin();
  bool checkIfComplete();
  bool setSpinMode(enum SpinMode m);

 private:
  TalonSRX* talon;
  int numRotations;
  enum SpinMode mode;
};
