/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Winch.h"

Winch::Winch() {
    // _winch->SetSelectedSensorPosition(0);
    // _winch->SetNeutralMode(NeutralMode::Brake);
    // _winch->SetInverted(true);
    // // _winch->Config_kP(kPIDx, kP, kTimeout);
    // // _winch->Config_kD(kPIDx, kD, kTimeout);
    // _winch->ConfigNominalOutputForward(0, kTimeout);
    // _winch->ConfigNominalOutputReverse(0, kTimeout);
    // _winch->ConfigPeakOutputForward(1, kTimeout);
    // _winch->ConfigPeakOutputReverse(0, kTimeout);
}

// This method will be called once per scheduler run
void Winch::Periodic() {}

void Winch::Automatic(){
    double position = _winch->GetSelectedSensorPosition();
    double error = target - position;
    _winch->Set(ControlMode::PercentOutput, error * kP);
}

void Winch::Manual(double percentage){
    _winch->Set(ControlMode::PercentOutput, percentage);
}

void Winch::Stop(){
    _winch->Set(ControlMode::PercentOutput, 0.0);
}

double Winch::Error(){
    double position = _winch->GetSelectedSensorPosition();
    return target - position;
}

