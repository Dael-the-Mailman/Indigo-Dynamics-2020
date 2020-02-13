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
class MediumShot
    : public frc2::CommandHelper<frc2::CommandBase, MediumShot> {
 public:
   MediumShot(Limelight *limelight, Drive *drive, Flywheel *flywheel);

   void Initialize() override;

   void Execute() override;

   void End(bool interrupted) override;

   bool IsFinished() override;
 private:
   Limelight *_limelight;
   Drive *_drive;
   Flywheel *_flywheel;
   const double fwdKp{1.6};
   const double fwdKi{};
   const double fwdKd{};
   const double turnKp{-0.015};
   const double turnKi{-0.001};
   const double turnKd{-0.15};
   const double targetArea{0.7};
   double currFwdError{}, prevFwdError{}, fwdIntegral{}, fwdDerive{}, fwdOutput{};
   double currTurnError{}, prevTurnError{}, turnIntegral{}, turnDerive{}, turnOutput{};
};
