/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/CloseShot.h"

CloseShot::CloseShot(Limelight *limelight, Drive *drive, Flywheel *flywheel)
    : _limelight{limelight}, _drive{drive}, m_flywheel{flywheel}
{
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements({_limelight});
  AddRequirements({_drive});
  AddRequirements({m_flywheel});
}

// Called when the command is initially scheduled.
void CloseShot::Initialize() {
  _limelight->SetPipeline(1);
  m_flywheel->SetTarget(0.52);
}

// Called repeatedly when this Command is scheduled to run
void CloseShot::Execute() {
  if(_limelight->Gettv() < 1.0){
    _drive->DriveArcade(0.0, 0.0);
  } else {
    currTurnError = _limelight->Gettx();
    currFwdError = targetArea - _limelight->Getta();
    turnDerive = currTurnError - prevTurnError;
    if(abs(currTurnError) < 4.0){
      turnIntegral += currTurnError;
      m_flywheel->Stop();
    } else {
      turnIntegral = 0;
    }
    turnOutput = (currTurnError * turnKp) + (turnIntegral * turnKi) + (turnDerive * turnKd);
    fwdOutput = (currFwdError * fwdKp);
    _drive->DriveArcade(fwdOutput, turnOutput);
    m_flywheel->Start();
    prevTurnError = currTurnError;
  }
}

// Called once the command ends or is interrupted.
void CloseShot::End(bool interrupted) {
  _limelight->SetPipeline(2);
  m_flywheel->Stop();
}

// Returns true when the command should end.
bool CloseShot::IsFinished() { return false; }
