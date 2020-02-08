#pragma once

#include <string>

#include <frc/smartdashboard/SendableChooser.h>
#include <frc/buttons/JoystickButton.h>
#include <frc/Joystick.h>
#include <ctre/phoenix.h>
#include <stdlib.h>
#include <frc/util/color.h>
#include <rev/ColorSensorV3.h>
#include <rev/ColorMatch.h>

#define wheelCircum (4 * 3.1)
#define cpCircum (100)
#define ticksPerRotation (50)
#define TALONPORT (20)

enum SpinMode {Rotation = 0, ColorDetection = 1};

class ControlPanelSpin {
 public:
  ControlPanelSpin();
  bool setNumRotations(int num);
  bool setCurrentColorTarget(frc::Color target);
  bool startSpin();
  bool checkIfComplete();
  bool setSpinMode(enum SpinMode m);

  static constexpr frc::Color kBlueTarget = frc::Color(0.143, 0.427, 0.429);
  static constexpr frc::Color kGreenTarget = frc::Color(0.197, 0.561, 0.240);
  static constexpr frc::Color kRedTarget = frc::Color(0.561, 0.232, 0.114);
  static constexpr frc::Color kYellowTarget = frc::Color(0.361, 0.524, 0.113);

 private:
  TalonSRX* talon;
  int numRotations;
  enum SpinMode mode;
  rev::ColorSensorV3* m_colorSensor;
  rev::ColorMatch m_colorMatcher;
  frc::Color currentTarget;
};
