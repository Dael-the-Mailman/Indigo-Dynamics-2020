/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/VisionAlignAction.h"

VisionAlignAction::VisionAlignAction(bool isClockwise, Drive *drive, Limelight *limelight)
: _drive{drive}, _limelight{limelight}{
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements({_drive});
  AddRequirements({_drive});
  isCw = isClockwise;
}

// Called when the command is initially scheduled.
void VisionAlignAction::Initialize() {
  _limelight->SetPipeline(2);
}

// Called repeatedly when this Command is scheduled to run
void VisionAlignAction::Execute() {
  if (_limelight->Gettv() < 1.0)
  {
    if(isCw){
      _drive->DriveArcade(0.0, -0.25);
    } else {
      _drive->DriveArcade(0.0, 0.25);
    }
  }
  else
  {
    currTurnError = _limelight->Gettx();
    turnDerive = currTurnError - prevTurnError;
    if (abs(currTurnError < 4.0))
    {
      turnIntegral += currTurnError;
    }
    else
    {
      turnIntegral = 0;
    }
    turnOutput = (currTurnError * turnKp) + (turnIntegral * turnKi) + (turnDerive * turnKd);
    _drive->DriveArcade(0.0, turnOutput);
    prevTurnError = currTurnError;
  }
}

// Called once the command ends or is interrupted.
void VisionAlignAction::End(bool interrupted) {
  _drive->DriveArcade(0.0, 0.0);
}

// Returns true when the command should end.
bool VisionAlignAction::IsFinished() {
  if (fabs(currTurnError) < 0.5 && fabs(_drive->GetPercentOutput()) < 0.05){
    return true;
  } else {
    return false;
  }
}
