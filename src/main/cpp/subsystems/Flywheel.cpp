/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <frc/smartdashboard/SmartDashboard.h>
#include "subsystems/Flywheel.h"

Flywheel::Flywheel()
{
    _flywheel->ConfigFactoryDefault();
    _flywheel->SetNeutralMode(NeutralMode::Coast);
    _flywheel->SetInverted(true);
    // _flywheel->ConfigNominalOutputReverse(0, kTimeoutMs);
    // _flywheel->ConfigNominalOutputForward(0, kTimeoutMs);
    // _flywheel->ConfigPeakOutputForward(1, kTimeoutMs);
    // _flywheel->ConfigPeakOutputReverse(-1, kTimeoutMs);
    // _flywheel->Config_kF(kPIDLoopIdx, kF, kTimeoutMs);
    // _flywheel->Config_kP(kPIDLoopIdx, kP, kTimeoutMs);
    // _flywheel->Config_kI(kPIDLoopIdx, kI, kTimeoutMs);
    // _flywheel->Config_kD(kPIDLoopIdx, kD, kTimeoutMs);
    // _flywheel->Config_IntegralZone(kPIDLoopIdx, 50);
    _flywheel->ClearStickyFaults();
    _flywheel->ConfigOpenloopRamp(2.0);
}

// This method will be called once per scheduler run
void Flywheel::Periodic() {
    frc::SmartDashboard::PutNumber("Flywheel Velocity", _flywheel->GetSelectedSensorVelocity());
    frc::SmartDashboard::PutNumber("Flywheel Error", setpoint - _flywheel->GetSelectedSensorVelocity());
    frc::SmartDashboard::PutNumber("Percentage", _flywheel->GetMotorOutputPercent());
    frc::SmartDashboard::PutNumber("Current Draw", _flywheel->GetSupplyCurrent());
}

void Flywheel::Start()
{
    // _flywheel->Set(ControlMode::Velocity, peakVelocity * percentage);
    currVelo = _flywheel->GetSelectedSensorVelocity();
    error = setpoint - currVelo;
    if(abs(error) < 100){
        integral += error;
    } else {
        integral = 0;
    }
    output = kF*setpoint + kP*error + kI*integral;
    if (output > 1.0){
        output = 1.0;
    } else if(output < -1.0){
        output = -1.0;
    }
    _flywheel->Set(ControlMode::PercentOutput, output);
}

void Flywheel::Stop()
{
    _flywheel->Set(ControlMode::PercentOutput, 0.0);
}

bool Flywheel::ReachedTarget(){
    // double veloError = _flywheel->GetClosedLoopError(kPIDLoopIdx);
    double veloError = setpoint - _flywheel->GetSelectedSensorVelocity();
    if(abs(veloError) < tolerance){
        return true;
    } else {
        return false;
    }
}

void Flywheel::SetTarget(double percentage){
    setpoint = peakVelocity*percentage;
}