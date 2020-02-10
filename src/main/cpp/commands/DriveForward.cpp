/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/DriveForward.h"

DriveForward::DriveForward(double inches, Drive *drive) : m_drive{drive}
{
  // Use addRequirements() here to declare subsystem dependencies.
  distance = inches;
  AddRequirements({m_drive});
}

// Called when the command is initially scheduled.
void DriveForward::Initialize()
{
  m_drive->ResetSensors();
}

// Called repeatedly when this Command is scheduled to run
void DriveForward::Execute()
{
  m_drive->DriveDistance(distance);
}

// Called once the command ends or is interrupted.
void DriveForward::End(bool interrupted) {}

// Returns true when the command should end.
bool DriveForward::IsFinished() { return m_drive->IsMagicFinished(); }
