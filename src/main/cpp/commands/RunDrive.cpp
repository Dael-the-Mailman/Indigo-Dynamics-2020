/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/RunDrive.h"

RunDrive::RunDrive(Drive *drive, frc::Joystick* joy) : m_drive{drive}, m_joy{joy}
{
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements({m_drive});
}

// Called when the command is initially scheduled.
void RunDrive::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void RunDrive::Execute()
{
  fwd = m_joy->GetRawAxis(1);
  rot = m_joy->GetRawAxis(4);
  if(m_joy->GetRawButton(9)){
    fwd /= 2;
  }
  if(m_joy->GetRawButton(10)){
    rot /= 2;
  }
  m_drive->Arcade(-fwd, rot);
}

// Called once the command ends or is interrupted.
void RunDrive::End(bool interrupted) {}

// Returns true when the command should end.
bool RunDrive::IsFinished() { return false; }
