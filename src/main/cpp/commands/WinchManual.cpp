/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/WinchManual.h"

WinchManual::WinchManual(Winch* winch, std::function<double()> percentage) 
  : m_winch{winch}, m_percentage{percentage} {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements({m_winch});
}

// Called when the command is initially scheduled.
void WinchManual::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void WinchManual::Execute() {
  m_winch->Manual(m_percentage());
}

// Called once the command ends or is interrupted.
void WinchManual::End(bool interrupted) {}

// Returns true when the command should end.
bool WinchManual::IsFinished() { return false; }
