/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <ctre/Phoenix.h>
#include <frc/smartdashboard/smartdashboard.h>
#include "Constants.h"
#include "rev/ColorSensorV3.h"
#include "rev/ColorMatch.h"

using namespace SpinConstants;
class PizzaTime : public frc2::SubsystemBase {
 public:
   PizzaTime();

   std::string GetColor();

  void StartSpin();

  void StopSpin();

  void BackwardSpin();

  void ReducedSpin();

   /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
   void Periodic();
  
 private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
  TalonSRX* spin = new TalonSRX(spinport);
  rev::ColorSensorV3 m_colorSensor{i2cPort};
  rev::ColorMatch m_colorMatcher;
};
