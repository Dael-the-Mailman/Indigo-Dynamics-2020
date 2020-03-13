/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/TurnAngle.h"

TurnAngle::TurnAngle(double angle, Drive* drive) : _drive{drive} {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements({_drive});
  targetAngle = angle;
}

// Called when the command is initially scheduled.
void TurnAngle::Initialize() {
  currAngle = _drive->GetAngle();
  error = targetAngle - currAngle;
}

// Called repeatedly when this Command is scheduled to run
void TurnAngle::Execute() {
  currAngle = _drive->GetAngle();
  error = targetAngle - currAngle;
  deriv = currAngle - prevAngle;
  if(abs(error) < 30){
    integral += error;
  } else {
    integral = 0;
  }
  output = (error * kP) + (integral * kI) + (deriv * kD);
  _drive->DriveArcade(0.0, output);
  frc::SmartDashboard::PutString("TurnAngle Status", "Running");
  frc::SmartDashboard::PutNumber("Gyro Error", error);
  prevAngle = currAngle;
}

// Called once the command ends or is interrupted.
void TurnAngle::End(bool interrupted) {
  _drive->DriveArcade(0.0, 0.0);
  frc::SmartDashboard::PutString("TurnAngle Status", "Stopped");
}

// Returns true when the command should end.
bool TurnAngle::IsFinished() {
  if(fabs(error) < 2.0 && fabs(_drive->GetPercentOutput()) < 0.05){
    return true;
  } else {
    return false;
  }
 }
