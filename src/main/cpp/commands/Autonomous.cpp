/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/Autonomous.h"

// NOTE:  Consider using this command inline, rather than writing a subclass.
// For more information, see:
// https://docs.wpilib.org/en/latest/docs/software/commandbased/convenience-features.html
Autonomous::Autonomous(Drive* DriveReference) : drive{DriveReference} {
  AddRequirements({drive});
  frc::DifferentialDriveVoltageConstraint autoVoltageConstraint(
      drive->GetFeedForward(),
      DriveConstants::kDriveKinematics, 10_V);

  frc::TrajectoryConfig config(AutoConstants::kMaxSpeed, AutoConstants::kMaxAcceleration);

  config.SetKinematics(DriveConstants::kDriveKinematics);

  config.AddConstraint(autoVoltageConstraint);

  frc::TrajectoryConfig backwardconfig(AutoConstants::kMaxSpeed, AutoConstants::kMaxAcceleration);

  backwardconfig.SetKinematics(DriveConstants::kDriveKinematics);

  backwardconfig.AddConstraint(autoVoltageConstraint);

  backwardconfig.SetReversed(true);

  frc::Trajectory exampleTrajectory = frc::TrajectoryGenerator::GenerateTrajectory(
      frc::Pose2d(0_m, 0_m, frc::Rotation2d(0_deg)),
      // Pass through these two interior waypoints, making an 's' curve path
      {frc::Translation2d(2_m, 1.53_m)},
      // End 3 meters straight ahead of where we started, facing forward
      frc::Pose2d(5_m, 1.7_m, frc::Rotation2d(0_deg)),
      config);

  frc2::RamseteCommand ramseteCommand(
    exampleTrajectory, [this]() { return drive->GetPose(); },
    frc::RamseteController(AutoConstants::kRamseteB, AutoConstants::kRamseteZeta),
    drive->GetFeedForward(), DriveConstants::kDriveKinematics,
    [this] { return drive->GetWheelSpeeds(); },
    frc2::PIDController(DriveConstants::kPDriveVel, 0.0, DriveConstants::kDDriveVel),
    frc2::PIDController(DriveConstants::kPDriveVel, 0.0, DriveConstants::kDDriveVel),
    [this](auto left, auto right) { drive->TankDriveVolts(left, right); },
    {drive});

  AddCommands(std::move(ramseteCommand),
      frc2::InstantCommand([this] {
    drive->TankDriveVolts(0_V, 0_V); }, {}));
}
