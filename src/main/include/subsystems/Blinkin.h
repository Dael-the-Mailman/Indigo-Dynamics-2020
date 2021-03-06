/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc/Spark.h>

class Blinkin : public frc2::SubsystemBase {
 public:
  Blinkin();

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic();

  void SolidBlue();

  void SolidIndigo();

  void SolidHotPink();

  void StrobeGold();

  void StrobeRed();

  void SolidGreen();

  void SolidRed();

  void Default();

  void RainbowRainbow();

 private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
  frc::Spark *LEDDriver = new frc::Spark(0);
};
