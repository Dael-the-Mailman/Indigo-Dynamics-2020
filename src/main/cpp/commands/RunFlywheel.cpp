/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/RunFlywheel.h"

RunFlywheel::RunFlywheel(Flywheel *flywheel, std::function<bool()> button)
    : m_flywheel{flywheel}, shoot{button}
{
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements({m_flywheel});
}

// Called when the command is initially scheduled.
void RunFlywheel::Initialize(){}

// Called repeatedly when this Command is scheduled to run
void RunFlywheel::Execute()
{
  // if(m_joy->GetRawButton(5)){
  //   m_flywheel->Start(0.7);
  // } else {
  //   m_flywheel->Stop();
  // }
  if(shoot()){
    m_flywheel->SetTarget(0.8);
    m_flywheel->Start();
  } else {
    m_flywheel->Stop();
  }
}

// Called once the command ends or is interrupted.
void RunFlywheel::End(bool interrupted) {}

// Returns true when the command should end.
bool RunFlywheel::IsFinished() { return false; }
