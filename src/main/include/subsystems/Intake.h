/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/DigitalInput.h>
#include <frc2/command/SubsystemBase.h>
#include <ctre/Phoenix.h>
#include "Constants.h"

using namespace IntakeConstants;
class Intake : public frc2::SubsystemBase
{
public:
  Intake();

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic();

  void StartRoller();

  void StopRoller();

  void StartIntake();

  void StopIntake();

  bool IsBroken();

  bool IsTopBroken();
  
  void Rotate(double rotation);

  void ReverseIntake();

  void FullForward();

private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
  TalonFX *_intake = new TalonFX(intakeport);
  TalonFX *_roller = new TalonFX(rollerport);
  frc::DigitalInput input{digitalport};
  frc::DigitalInput topbanner{topbannerport};
};
