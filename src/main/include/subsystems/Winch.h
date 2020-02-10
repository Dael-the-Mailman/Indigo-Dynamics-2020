/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/SubsystemBase.h>
#include "ctre/Phoenix.h"
#include "Constants.h"

using namespace WinchConstants;
class Winch : public frc2::SubsystemBase {
 public:
  Winch();

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic();

  void Automatic();

  void Manual(double percentage);

  void Stop();

  double Error();

 private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
  TalonFX* _winch = new TalonFX(winchport);
};
