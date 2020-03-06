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

/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class VisionAlignAction
    : public frc2::CommandHelper<frc2::CommandBase, VisionAlignAction> {
 public:
  VisionAlignAction(bool isClockwise, Drive* drive, Limelight* limelight);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

 private:
  bool isCw;
  Drive* _drive;
  Limelight* _limelight;
  const double turnKp{-0.04};
  const double turnKi{-0.0};
  const double turnKd{-0.3};
  double currTurnError, prevTurnError, turnDerive, turnIntegral, turnOutput{};
};
