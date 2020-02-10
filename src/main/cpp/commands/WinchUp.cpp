/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/WinchUp.h"

WinchUp::WinchUp(Winch* winch) : m_winch{winch} {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements({m_winch});
}

// Called when the command is initially scheduled.
void WinchUp::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void WinchUp::Execute() {
  m_winch->Automatic();
  printf("Winch Execute Called\n");
}

// Called once the command ends or is interrupted.
void WinchUp::End(bool interrupted) {
  m_winch->Stop();
  printf("Winch Stop Called\nError: %f\n", m_winch->Error());
}

// Returns true when the command should end.
bool WinchUp::IsFinished() { return (m_winch->Error() < 1000); }
