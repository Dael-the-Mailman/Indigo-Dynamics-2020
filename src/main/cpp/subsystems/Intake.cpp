/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Intake.h"

Intake::Intake()
{
    _intake->ConfigFactoryDefault();
    _roller->ConfigFactoryDefault();
    _intake->SetNeutralMode(NeutralMode::Coast);
    _roller->SetNeutralMode(NeutralMode::Coast);
    _intake->SetInverted(true);
}

// This method will be called once per scheduler run
void Intake::Periodic() {}

void Intake::StartIntake()
{
    _intake->Set(ControlMode::PercentOutput, 0.7);
}

void Intake::StopIntake()
{
    _intake->Set(ControlMode::PercentOutput, 0.0);
}

void Intake::StartRoller()
{
    _roller->Set(ControlMode::PercentOutput, 0.7);
}

void Intake::StopRoller()
{
    _roller->Set(ControlMode::PercentOutput, 0.0);
}

bool Intake::IsBroken()
{
    return !input.Get();
}

bool Intake::IsTopBroken(){
    return !topbanner.Get();
}

void Intake::Rotate(double rotation)
{
    _intake->SetSelectedSensorPosition(0);
    _intake->Set(ControlMode::Position, rotation * 51200);
}

void Intake::ReverseIntake()
{
    _intake->Set(ControlMode::PercentOutput, -0.5);
    _roller->Set(ControlMode::PercentOutput, -0.5);
}