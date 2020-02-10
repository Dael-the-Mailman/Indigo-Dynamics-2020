/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/RunIntake.h"

RunIntake::RunIntake(Intake *intake) : m_intake{intake}
{
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements({m_intake});
}

// Called when the command is initially scheduled.
void RunIntake::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void RunIntake::Execute()
{
  currState = m_intake->IsBroken();
  currTopState = m_intake->IsTopBroken();
  m_intake->StartRoller();

  if (currState && !currTopState)
  {
    m_intake->StartIntake();
  }
  else if (currState == false && prevState == true && !currTopState)
  {
    m_timer.Reset();
    m_timer.Start();
    while (m_timer.Get() < 0.1)
    {
      m_intake->StartIntake();
    }
    m_timer.Stop();
    m_intake->StopIntake();
  } else if (currState && currTopState){
    m_intake->StopIntake();
    m_intake->StopRoller();
  }
  else
  {
    m_intake->StopIntake();
  }
  prevState = currState;
  
}

// Called once the command ends or is interrupted.
void RunIntake::End(bool interrupted)
{
  m_intake->StopRoller();
  m_intake->StopIntake();
}

// Returns true when the command should end.
bool RunIntake::IsFinished() { return false; }
