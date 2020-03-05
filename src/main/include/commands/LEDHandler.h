/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include "subsystems/Blinkin.h"

/**
 * An example command.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class LEDHandler
    : public frc2::CommandHelper<frc2::CommandBase, LEDHandler> {
 public:
  LEDHandler(Blinkin* blinkin, std::function<bool()> isBroken, 
  std::function<bool()> isTopBroken, std::function<bool()> reachedTarget);

  void Initialize() override;

  void Execute() override;

  void End(bool interrupted) override;

  bool IsFinished() override;

 private:
  Blinkin* _blinkin;
  std::function<bool()> IsBroken;
  std::function<bool()> IsTopBroken;
  std::function<bool()> ReachedTarget;
};
