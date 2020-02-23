/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <ctre/Phoenix.h>
#include "Constants.h"

using namespace FlywheelConstants;
class Flywheel : public frc2::SubsystemBase
{
public:
  Flywheel();

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic();

  void Start();

  void Stop();

  bool ReachedTarget(double tol = tolerance);

  void SetTarget(double percentage);

private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
  TalonFX *_flywheel = new TalonFX(flywheelport);
  double setpoint{}, currVelo{}, error{}, output{}, integral{};
};
