/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/BButton.h"

BButton::BButton(Intake *intake, Flywheel* flywheel) 
  : m_intake{intake}, m_flywheel{flywheel}
{
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements({m_intake});
  AddRequirements({m_flywheel});
}

// Called when the command is initially scheduled.
void BButton::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void BButton::Execute()
{
  // if(m_flywheel->ReachedTarget()){
  //   m_intake->StartIntake();
  //   if(m_intake->IsBroken()){
  //     m_intake->StartRoller();
  //   } else {
  //     m_intake->StopRoller();
  //   }
  // } else {
  //   m_intake->StopIntake();
  //   m_intake->StopRoller();
  // }
  m_intake->StartIntake();
}

// Called once the command ends or is interrupted.
void BButton::End(bool interrupted)
{
  m_intake->StopIntake();
  m_intake->StopRoller();
}

// Returns true when the command should end.
bool BButton::IsFinished() { return false; }
