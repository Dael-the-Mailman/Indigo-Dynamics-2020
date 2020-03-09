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
class AngleAlign
    : public frc2::CommandHelper<frc2::CommandBase, AngleAlign> {
 public:
  AngleAlign(Drive* drive, Limelight* limelight, Flywheel* flywheel);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

 private:
  Drive* _drive;
  Limelight* _limelight;
  Flywheel* _flywheel;
  const double kP{-0.018};
  const double kI{-0.001};
  const double kD{-0.15};
  double currTurnError, turnDerive, turnIntegral, prevTurnError, turnOutput{};
};
