/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/CloseShot.h"

CloseShot::CloseShot(Limelight *limelight, Drive *drive, Flywheel *flywheel, Intake *intake)
    : _limelight{limelight}, _drive{drive}, m_flywheel{flywheel}, m_intake{intake}
{
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements({_limelight});
  AddRequirements({_drive});
  AddRequirements({m_flywheel});
  AddRequirements({m_intake});
}

// Called when the command is initially scheduled.
void CloseShot::Initialize() {
  _limelight->SetPipeline(1);
  m_flywheel->SetTarget(0.54);
}

// Called repeatedly when this Command is scheduled to run
void CloseShot::Execute() {
  if(_limelight->Gettv() < 1.0){
    _drive->DriveArcade(0.0, 0.0);
  } else {
    currTurnError = _limelight->Gettx();
    currFwdError = targetArea - _limelight->Getta();
    turnDerive = currTurnError - prevTurnError;
    if(currTurnError < 4.0){
      turnIntegral += currTurnError;
    } else {
      turnIntegral = 0;
    }
    turnOutput = (currTurnError * turnKp) + (turnIntegral * turnKi) + (turnDerive * turnKd);
    fwdOutput = (currFwdError * fwdKp);
    _drive->DriveArcade(fwdOutput, turnOutput);
    prevTurnError = currTurnError;
  }
}

// Called once the command ends or is interrupted.
void CloseShot::End(bool interrupted) {
}

// Returns true when the command should end.
bool CloseShot::IsFinished() { return false; }
