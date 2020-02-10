/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/VisionAlign.h"

VisionAlign::VisionAlign(Limelight* limelight,  Drive* drive) 
  : m_limelight{limelight}, m_drive{drive} {
  // Use addRequirements() here to declare subsystem dependencies.
  AddRequirements({m_limelight});
  AddRequirements({m_drive});
}

// Called when the command is initially scheduled.
void VisionAlign::Initialize(){

}

// Called repeatedly when this Command is scheduled to run
void VisionAlign::Execute() {
  if(m_limelight->Gettv() < 1.0){
    m_drive->DriveArcade(0.0, 0.0);
  } else {
    curerror = m_limelight->Gettx();
    deriv = curerror - preverror;
    if(abs(curerror) < 4.0 && abs(curerror) > 0.35){
      integral += curerror;
    } else {
      integral = 0;
    }
    double output = (curerror* -STEER_K) + (integral * -Ki) +(deriv* -Kd);
    double turnCmd = Clamp(output, -MAX_STEER, MAX_STEER);
    // double forwardCmd = (DESIRED_TARGET_AREA - m_limelight->Getta()) * DRIVE_K;
    m_drive->DriveArcade(0.0, turnCmd);
    preverror = curerror;
  }
}

// Called once the command ends or is interrupted.
void VisionAlign::End(bool interrupted) {

}

// Returns true when the command should end.
bool VisionAlign::IsFinished() { return false; }

double VisionAlign::Clamp(double input, double minval, double maxval){
  if(input > maxval) return maxval;
  if(input < minval) return minval;
  return input;
}