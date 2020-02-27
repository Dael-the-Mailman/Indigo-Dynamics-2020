/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/Shoot.h"

Shoot::Shoot(double time, double speed, Flywheel* flywheel, Intake* intake, frc::Timer* timer)
: _flywheel{flywheel}, _intake{intake}, _timer{timer} {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements({_flywheel});
  AddRequirements({_intake});
  timeLimit = time;
  targetSpeed = speed;
}

// Called when the command is initially scheduled.
void Shoot::Initialize() {
  _timer->Stop();
  shoot = false;
  _timer->Reset();
  _flywheel->SetTarget(targetSpeed);
  _intake->StopIntake();
  _intake->StopRoller();
  _timer->Start();
}

// Called repeatedly when this Command is scheduled to run
void Shoot::Execute() {
  _flywheel->Start();
  if(_flywheel->ReachedTarget(300)){
    shoot = true;
  }
  if(shoot){
    _intake->StartIntake();
    _intake->StartRoller();
  }
}

// Called once the command ends or is interrupted.
void Shoot::End(bool interrupted) {
  _timer->Stop();
  _flywheel->Stop();
  _intake->StopIntake();
  _intake->StopRoller();
}

// Returns true when the command should end.
bool Shoot::IsFinished() { 
  if(_timer->Get() > timeLimit){
    return true;
  } else {
    return false; 
  }
}
