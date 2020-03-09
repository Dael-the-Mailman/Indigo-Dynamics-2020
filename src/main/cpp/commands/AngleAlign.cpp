/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/AngleAlign.h"

AngleAlign::AngleAlign(Drive *drive, Limelight *limelight, Flywheel *flywheel)
    : _drive{drive}, _limelight{limelight}, _flywheel{flywheel}
{
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements({_drive});
  AddRequirements({_limelight});
  AddRequirements({_flywheel});
}

// Called when the command is initially scheduled.
void AngleAlign::Initialize() {
  _limelight->SetPipeline(2);
  _limelight->EnablePiPMain();
  _flywheel->SetTarget(0.6);
}

// Called repeatedly when this Command is scheduled to run
void AngleAlign::Execute() {
  if (_limelight->Gettv() < 1.0)
  {
    _drive->DriveArcade(0.0, 0.0);
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
    turnOutput = (currTurnError * kP) + (turnIntegral * kI) + (turnDerive * kD);
    _drive->DriveArcade(0.0, turnOutput);
    prevTurnError = currTurnError;
  }
}

// Called once the command ends or is interrupted.
void AngleAlign::End(bool interrupted) {
  _limelight->EnablePiPSecondary();
}

// Returns true when the command should end.
bool AngleAlign::IsFinished() { return false; }
