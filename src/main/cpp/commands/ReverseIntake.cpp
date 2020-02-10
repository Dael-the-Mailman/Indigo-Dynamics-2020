/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/ReverseIntake.h"

ReverseIntake::ReverseIntake(Intake *intake) : m_intake{intake}
{
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements({m_intake});
}

// Called when the command is initially scheduled.
void ReverseIntake::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void ReverseIntake::Execute()
{
  m_intake->ReverseIntake();
}

// Called once the command ends or is interrupted.
void ReverseIntake::End(bool interrupted)
{
  m_intake->StopIntake();
  m_intake->StopRoller();
}

// Returns true when the command should end.
bool ReverseIntake::IsFinished() { return false; }
