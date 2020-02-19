/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/ColorPizza.h"

ColorPizza::ColorPizza(PizzaTime* pt) : _pt{pt}{
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements({_pt});
}

// Called when the command is initially scheduled.
void ColorPizza::Initialize() {
  ReachedTarget = false;
  std::string gameData = frc::DriverStation::GetInstance().GetGameSpecificMessage();
  if (gameData.length() > 0)
  {
    switch (gameData[0])
    {
    case 'B':
      targetColor = 'B';
      break;
    case 'G':
      targetColor = 'G';
      break;
    case 'R':
      targetColor = 'R';
      break;
    case 'Y':
      targetColor = 'Y';
      break;
    default:
      ReachedTarget = true;
      break;
    }
  }
  else
  {
    ReachedTarget = true;
  }
}

// Called repeatedly when this Command is scheduled to run
void ColorPizza::Execute() {
  currColor = _pt->GetColor();
  if(targetColor == "Y"){
    if(currColor == "G"){
      ReachedTarget = true;
    }
  } else if(targetColor == "R"){
    if (currColor == "B")
    {
      ReachedTarget = true;
    }
  }
  else if (targetColor == "G")
  {
    if (currColor == "Y")
    {
      ReachedTarget = true;
    }
  } else {
    if (currColor == "R")
    {
      ReachedTarget = true;
    }
  }
  _pt->ReducedSpin();
}

// Called once the command ends or is interrupted.
void ColorPizza::End(bool interrupted) { _pt->StopSpin(); }

// Returns true when the command should end.
bool ColorPizza::IsFinished() { return ReachedTarget; }
