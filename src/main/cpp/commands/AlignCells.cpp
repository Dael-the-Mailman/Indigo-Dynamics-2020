/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/AlignCells.h"

AlignCells::AlignCells(Intake* intake) : _intake(intake){
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements({_intake});
}

// Called when the command is initially scheduled.
void AlignCells::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void AlignCells::Execute() {
  if(_intake->IsTopBroken()){
    _intake->StopIntake();
    _intake->StopRoller();
  } else {
    _intake->StartIntake();
    _intake->StartRoller();
  }
}

// Called once the command ends or is interrupted.
void AlignCells::End(bool interrupted) {
  _intake->StopIntake();
  _intake->StopRoller();
}

// Returns true when the command should end.
bool AlignCells::IsFinished() { return false; }
