/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once
#include <frc/util/color.h>
#include <frc/I2C.h>
#include <frc/kinematics/DifferentialDriveKinematics.h>
#include <frc/trajectory/constraint/DifferentialDriveKinematicsConstraint.h>
#include <units/units.h>
#include <wpi/math>

/**
 * The Constants header provides a convenient place for teams to hold robot-wide
 * numerical or boolean constants.  This should not be used for any other
 * purpose.
 *
 * It is generally a good idea to place constants into subsystem- or
 * command-specific namespaces within this header, which can then be used where
 * they are needed.
 */
namespace FlywheelConstants
{
    constexpr int flywheelport = 3;
    constexpr double kF = 0.05; // 0.05
    constexpr double kP = 0.15; // 0.30
    constexpr double kI = 0.0001; // 0.001
    constexpr double kD = 0.0; // 48.0
    constexpr double kFt = 0.06; // 0.000054
    constexpr double kPt = 1.0; // 0.0005
    constexpr double kIt = 0.001; // 0.00001
    constexpr double kDt = 40.0;
    constexpr double peakVelocity = 17000.0;
    constexpr double kTimeoutMs = 10.0;
    constexpr int kSlotIdx = 0;
    constexpr int kPIDLoopIdx = 0;
    constexpr int kPIDLoopIdt = 1;
    constexpr double tolerance = 100.0;
} // namespace FlywheelConstants

namespace IntakeConstants
{
    constexpr int digitalport = 0;
    constexpr int topbannerport = 1;
    constexpr int rollerport = 1;
    constexpr int intakeport = 2;
    constexpr double offsetposition = 51200.0;
} // namespace IntakeConstants

namespace DriveConstants
{
    //Motor ports
    constexpr int frontleftport = 4;
    constexpr int frontrightport = 7;
    constexpr int backleftport = 6;
    constexpr int backrightport = 5;

    //Arcade drive constants
    constexpr double m_quickStopThreshold = 0.2;
    constexpr double m_quickStopAlpha = 0.1;

    //Motion Magic
    constexpr double kF = 0.050;
    constexpr double kP = 0.0;
    constexpr double kI = 0.0;
    constexpr double kD = 0.0;
    constexpr double cruiseVelocity = 10240;
    constexpr double acceleration = 10240;
    constexpr double ticksperinch = (2048 * 10.75) / (6 * 3.141592653589793);
    constexpr double kTimeoutMs = 10.0;
    constexpr int kPIDLoopIdx = 0;
    constexpr int smoothness = 8;
    constexpr double turnMultiplier = 0.6;
    constexpr auto ks = 0.259_V;
    constexpr auto kv = 2.46 * 1_V * 1_s / 1_m;
    constexpr auto ka = 0.172 * 1_V * 1_s * 1_s / 1_m;
    constexpr auto kTrackwidth = 0.608772591_m;
    static const frc::DifferentialDriveKinematics kDriveKinematics{kTrackwidth};

    constexpr bool kGyroReversed = true;
    constexpr double kGearRatio = 10.75;
    constexpr int kEncoderCPR = 2048;
    constexpr double kWheelRadius = 0.0762;
    constexpr double kEncoderDistancePerPulse =
        // Assumes the encoders are directly mounted on the wheel shafts
        (2 * kWheelRadius * wpi::math::pi) / (static_cast<double>(kEncoderCPR) * kGearRatio);
    constexpr double kTicksPer100msToMetersPerSecond = (10 * wpi::math::pi * kWheelRadius) / (static_cast<double>(kEncoderCPR) * kGearRatio);
    constexpr double kPDriveVel = 0.00935;
    constexpr double kDDriveVel = 0.00362;
} // namespace DriveConstants

namespace AutoConstants
{
constexpr auto kMaxSpeed = 4_mps;           //3.78864
constexpr auto kMaxAcceleration = 1_mps_sq; //1.89432

// Reasonable baseline values for a RAMSETE follower in units of meters and
// seconds
constexpr double kRamseteB = 2;
constexpr double kRamseteZeta = 0.7;
} // namespace AutoConstants

namespace WinchConstants{
    constexpr int winchport = 0;
    constexpr double target = 495000.0; //441907
    constexpr double kP = 0.000125;
    constexpr double kD = 0.10;
    constexpr int kPIDx = 0;
    constexpr int kTimeout = 10;
    constexpr int threshold = 1000;
}

namespace SpinConstants{
    constexpr int spinport = 8;
    constexpr auto i2cPort = frc::I2C::Port::kOnboard;
    constexpr frc::Color kBlueTarget = frc::Color(0.22, 0.48, 0.29); // 0.16, 0.45, 0.39
    constexpr frc::Color kGreenTarget = frc::Color(0.18, 0.57, 0.25);
    constexpr frc::Color kRedTarget = frc::Color(0.47, 0.37, 0.15);
    constexpr frc::Color kYellowTarget = frc::Color(0.31, 0.55, 0.13);
}