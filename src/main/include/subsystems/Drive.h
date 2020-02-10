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

using namespace DriveConstants;
class Drive : public frc2::SubsystemBase
{
public:
  Drive();

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic();

  void Arcade(double xSpeed, double zRotation);

  double SquareInput(double input);

  double ThresholdHandler(double input, double threshold);

  void DriveDistance(double inches);

  bool IsMagicFinished();

  void ResetSensors();

  void DriveArcade(double forward, double rotate);

private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
  TalonFX *_frontright = new TalonFX(frontrightport);
  TalonFX *_frontleft = new TalonFX(frontleftport);
  TalonFX *_backright = new TalonFX(backrightport);
  TalonFX *_backleft = new TalonFX(backleftport);
};
