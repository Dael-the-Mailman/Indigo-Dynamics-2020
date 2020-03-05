/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/RunPizza.h"

RunPizza::RunPizza(PizzaTime *pt) : _pt{pt}
{
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements({_pt});
}

// Called when the command is initially scheduled.
void RunPizza::Initialize() {
  count = 0;
  ReachedTarget = false;
}

// Called repeatedly when this Command is scheduled to run
void RunPizza::Execute() {
  if(count < 30){
    _pt->StartSpin();
    currColor = _pt->GetColor();
    if(currColor != prevColor){
      count++;
    }
    prevColor = currColor;
  } else {
    ReachedTarget = true;
  }
  frc::SmartDashboard::PutNumber("Pizza Count", count);
  frc::SmartDashboard::PutBoolean("Reached Pizza Target", ReachedTarget);
}

// Called once the command ends or is interrupted.
void RunPizza::End(bool interrupted) {
  _pt->StopSpin();
}

// Returns true when the command should end.
bool RunPizza::IsFinished() { return ReachedTarget; }
