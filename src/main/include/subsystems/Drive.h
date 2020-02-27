/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/ADXRS450_Gyro.h>
#include <frc/Encoder.h>
#include "ctre/phoenix.h"
#include <frc/SpeedControllerGroup.h>
#include <frc/drive/DifferentialDrive.h>
#include <frc/geometry/Pose2d.h>
#include <frc/kinematics/DifferentialDriveOdometry.h>
#include <frc/controller/SimpleMotorFeedforward.h>
#include <frc2/command/SubsystemBase.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <networktables/NetworkTable.h>
#include <networktables/NetworkTableInstance.h>
#include <units/units.h>
#include "Constants.h"

using namespace DriveConstants;
class Drive : public frc2::SubsystemBase
{
public:
  Drive();

  /**
   * Will be called periodically whenever the CommandScheduler runs.
   */
  void Periodic();

  void Arcade(double xSpeed, double zRotation); // Curvature Drive

  double SquareInput(double input); // Squares the input and keeps the sign

  double ThresholdHandler(double input, double threshold); // Handles threshold values

  void DriveArcade(double forward, double rotate); // Actual arcade drive

  void TankDriveVolts(units::volt_t left, units::volt_t right); // Runs the drive with Voltage

  void ResetEncoders(); // Resets encoder values

  void SetMaxOutput(double maxOutput); // Sets the maximum output of drive

  void ResetOdometry(frc::Pose2d pose); // Resets the odometry of the drive

  frc::Rotation2d GetHeading(); // Gets the heading of the gyro

  frc::Pose2d GetPose(); // Gets the pose of the robot

  frc::DifferentialDriveWheelSpeeds GetWheelSpeeds(); // Gets the left and right wheel speeds

  frc::SimpleMotorFeedforward<units::meters> GetFeedForward(); // Returns the feedforward drive object

  units::meter_t LeftPosition(); // Returns the left position of the bot in meters

  units::meter_t RightPosition(); // Returns the right position of the bot in meters

  units::meters_per_second_t LeftSpeed(); // Returns the speed of the left side in meters per second

  units::meters_per_second_t RightSpeed(); // Returns the speed of the right side in meters per second

  double GetAngle();

  void ResetAngle();

  double GetPercentOutput();
  
private:
  // Components (e.g. motor controllers and sensors) should generally be
  // declared private and exposed only through public methods.
  WPI_TalonFX *_frontright = new WPI_TalonFX(frontrightport);
  WPI_TalonFX *_frontleft = new WPI_TalonFX(frontleftport);
  WPI_TalonFX *_backright = new WPI_TalonFX(backrightport);
  WPI_TalonFX *_backleft = new WPI_TalonFX(backleftport);

  frc::DifferentialDrive drive{*_frontleft, *_frontright};

  frc::ADXRS450_Gyro gyro{frc::SPI::Port::kOnboardCS0};
  frc::DifferentialDriveOdometry odometry{GetHeading()};
  frc::SimpleMotorFeedforward<units::meters> feedforward{ks, kv, ka};
};
