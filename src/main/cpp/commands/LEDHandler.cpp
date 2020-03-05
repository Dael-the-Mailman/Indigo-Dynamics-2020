/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/LEDHandler.h"

LEDHandler::LEDHandler(Blinkin *blinkin, std::function<bool()> isBroken,
                       std::function<bool()> isTopBroken, std::function<bool()> reachedTarget)
    : _blinkin{blinkin}, IsBroken{isBroken}, IsTopBroken{isTopBroken}, ReachedTarget{reachedTarget}
{
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements({_blinkin});
}

// Called when the command is initially scheduled.
void LEDHandler::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void LEDHandler::Execute() {
  if(IsBroken() && IsTopBroken() && !ReachedTarget()){
    _blinkin->SolidIndigo();
  }
  else if (!IsBroken() && !IsTopBroken() && ReachedTarget())
  {
    _blinkin->SolidHotPink();

  } else if(IsBroken() && IsTopBroken() && ReachedTarget()){
    _blinkin->StrobeGold();

  } else {
    _blinkin->Default();
    
  }
}

// Called once the command ends or is interrupted.
void LEDHandler::End(bool interrupted) {}

// Returns true when the command should end.
bool LEDHandler::IsFinished() { return false; }
