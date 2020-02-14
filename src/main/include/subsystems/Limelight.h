/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/SubsystemBase.h>

class Limelight : public frc2::SubsystemBase {
 public:
  Limelight();

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic();

  double Gettx();

  double Getty();

  double Getta();

  double Gettv();

  void LEDOff();

  void LEDOn();

  void SetPipeline(int pipeline);

  bool WithinThreshold(double xThreshold, double areaThreshold, double targetArea);

 private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
  double tx{}, ty{}, ta{}, tv{}, pipe{};
};
