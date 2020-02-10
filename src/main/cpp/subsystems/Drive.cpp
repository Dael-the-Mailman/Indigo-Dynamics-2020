/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Drive.h"

Drive::Drive()
{
    //Configure all motors to factory default
    _frontright->ConfigFactoryDefault();
    _backright->ConfigFactoryDefault();
    _frontleft->ConfigFactoryDefault();
    _backleft->ConfigFactoryDefault();

    //Invert right side motors
    _frontright->SetInverted(true);
    _backright->SetInverted(true);

    //Set the motors to brake mode
    _frontright->SetNeutralMode(NeutralMode::Brake);
    _backright->SetNeutralMode(NeutralMode::Brake);
    _frontleft->SetNeutralMode(NeutralMode::Brake);
    _backleft->SetNeutralMode(NeutralMode::Brake);

    //Configure the open loop ramp for smooth operation
    _frontright->ConfigOpenloopRamp(1.0);
    _backright->ConfigOpenloopRamp(1.0);
    _frontleft->ConfigOpenloopRamp(1.0);
    _backleft->ConfigOpenloopRamp(1.0);

    //Configure constants with front right motor as the master
    _frontright->Config_kF(kPIDLoopIdx, kF, kTimeoutMs);
    _frontright->Config_kP(kPIDLoopIdx, kP, kTimeoutMs);
    _frontright->Config_kI(kPIDLoopIdx, kI, kTimeoutMs);
    _frontright->Config_kD(kPIDLoopIdx, kD, kTimeoutMs);
    _frontright->ConfigMotionAcceleration(acceleration, kTimeoutMs);
    _frontright->ConfigMotionCruiseVelocity(cruiseVelocity, kTimeoutMs);
    _frontright->ConfigMotionSCurveStrength(smoothness, kTimeoutMs);

    //Configure Auxillary PID with front right motor as the master
    _frontright->ConfigAuxPIDPolarity(false, kTimeoutMs);

    //Configure Follower motors
    _backleft->Follow(*_frontleft, FollowerType::FollowerType_PercentOutput);
    _backright->Follow(*_frontright, FollowerType::FollowerType_PercentOutput);
}

// This method will be called once per scheduler run
void Drive::Periodic() {}

void Drive::Arcade(double xSpeed, double zRotation)
{
    xSpeed = SquareInput(xSpeed);
    zRotation = SquareInput(zRotation);
    double angularPower;
    double m_quickStopAccumulator{};
    bool overPower;
    bool isQuickTurn = false;
    if (std::abs(xSpeed) < 0.1 && std::abs(zRotation) > 0.1)
    {
        isQuickTurn = true;
    }

    if (isQuickTurn)
    {
        m_quickStopAccumulator = (1 - m_quickStopAlpha) * m_quickStopAccumulator +
                                 m_quickStopAlpha * zRotation * 2;
        overPower = true;
        angularPower = zRotation;
    }
    else
    {
        overPower = false;
        angularPower = std::abs(xSpeed) * zRotation - m_quickStopAccumulator;

        if (m_quickStopAccumulator > 1)
        {
            m_quickStopAccumulator -= 1;
        }
        else if (m_quickStopAccumulator < -1)
        {
            m_quickStopAccumulator += 1;
        }
        else
        {
            m_quickStopAccumulator = 0.0;
        }
    }

    double leftMotorOutput = xSpeed + angularPower;
    double rightMotorOutput = xSpeed - angularPower;

    // If rotation is overpowered, reduce both outputs to within acceptable range
    if (overPower)
    {
        if (leftMotorOutput > 1.0)
        {
            rightMotorOutput -= leftMotorOutput - 1.0;
            leftMotorOutput = 1.0;
        }
        else if (rightMotorOutput > 1.0)
        {
            leftMotorOutput -= rightMotorOutput - 1.0;
            rightMotorOutput = 1.0;
        }
        else if (leftMotorOutput < -1.0)
        {
            rightMotorOutput -= leftMotorOutput + 1.0;
            leftMotorOutput = -1.0;
        }
        else if (rightMotorOutput < -1.0)
        {
            leftMotorOutput -= rightMotorOutput + 1.0;
            rightMotorOutput = -1.0;
        }
    }

    // Normalize the wheel speeds
    double maxMagnitude =
        std::max(std::abs(leftMotorOutput), std::abs(rightMotorOutput));
    if (maxMagnitude > 1.0)
    {
        leftMotorOutput /= maxMagnitude;
        rightMotorOutput /= maxMagnitude;
    }
    _frontright->Set(ControlMode::PercentOutput, rightMotorOutput);
    _frontleft->Set(ControlMode::PercentOutput, leftMotorOutput);
}

double Drive::SquareInput(double input)
{
    return (input >= 0) ? input * input : -1 * input * input;
}

double Drive::ThresholdHandler(double input, double threshold)
{
    return (abs(input) >= threshold) ? input : 0;
}

void Drive::DriveDistance(double inches)
{
    double ticks = inches * ticksperinch;
    _frontright->Set(ControlMode::MotionMagic, ticks);
    _frontleft->Follow(*_frontright, FollowerType::FollowerType_AuxOutput1);
}

bool Drive::IsMagicFinished()
{
    if (abs(_frontright->GetClosedLoopError()) <= ticksperinch * 0.1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Drive::ResetSensors()
{
    _frontleft->SetSelectedSensorPosition(0, kPIDLoopIdx, kTimeoutMs);
    _frontright->SetSelectedSensorPosition(0, kPIDLoopIdx, kTimeoutMs);
}

void Drive::DriveArcade(double forward, double rotate){
    _frontright->Set(ControlMode::PercentOutput, forward + rotate);
    _frontleft->Set(ControlMode::PercentOutput, forward - rotate);
}