/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/RunDrive.h"

RunDrive::RunDrive(Drive *drive, std::function<double()> forward, std::function<double()> rotation)
    : m_drive{drive}, m_forward{forward}, m_rotation{rotation}
{
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements({m_drive});
}

// Called when the command is initially scheduled.
void RunDrive::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void RunDrive::Execute()
{
  m_drive->Arcade(m_forward(), m_rotation());
}

// Called once the command ends or is interrupted.
void RunDrive::End(bool interrupted) {}

// Returns true when the command should end.
bool RunDrive::IsFinished() { return false; }
