/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include "subsystems/Limelight.h"
#include "subsystems/Drive.h"
#include "subsystems/Flywheel.h"

/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class VisionAlign
    : public frc2::CommandHelper<frc2::CommandBase, VisionAlign> {
 public:
  VisionAlign(Limelight* limelight, Drive* drive, Flywheel* flywheel);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

  double Clamp(double input, double minval, double maxval);

 private:
  Limelight* m_limelight;
  Drive* m_drive;
  Flywheel* m_flywheel;

  const double STEER_K = 0.015;

  const double DRIVE_K = 0.01;

  const double Kd = 0.15;

  const double Ki = 0.004;

  const double DESIRED_TARGET_AREA = 13.0;
  const double MAX_DRIVE = 0.65;
  const double MAX_STEER = 1.0f;
  double curerror{}, preverror{}, deriv{}, integral{};
};
