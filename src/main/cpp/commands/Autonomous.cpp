/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/Autonomous.h"
#include "commands/BButton.h"
#include "commands/RunIntake.h"
#include "commands/TurnAngle.h"

// NOTE:  Consider using this command inline, rather than writing a subclass.
// For more information, see:
// https://docs.wpilib.org/en/latest/docs/software/commandbased/convenience-features.html
Autonomous::Autonomous(Drive* DriveReference, Intake* IntakeReference, frc::Timer* TimerReference, Flywheel* FlywheelReference) 
: drive{DriveReference}, intake{IntakeReference}, timer{TimerReference}, flywheel{FlywheelReference} {
  AddRequirements({drive});
  AddRequirements({intake});
  AddRequirements({flywheel});

  wpi::SmallString<64> deployDirectory;
  frc::filesystem::GetDeployDirectory(deployDirectory);
  wpi::sys::path::append(deployDirectory, "paths");
  wpi::sys::path::append(deployDirectory, "GetTwoPowerCells.wpilib.json");

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

  frc::Trajectory port = frc::TrajectoryGenerator::GenerateTrajectory(
    frc::Pose2d(0_m, 0_m, frc::Rotation2d(0_deg)),
    // Pass through these two interior waypoints, making an 's' curve path
    {frc::Translation2d(2_m, 0.9_m)},
    // End 3 meters straight ahead of where we started, facing forward
    frc::Pose2d(4_m, 1.7_m, frc::Rotation2d(0_deg)),
    config);

  frc::Trajectory forward = frc::TrajectoryGenerator::GenerateTrajectory(
      // Start at the origin facing the +X direction
      frc::Pose2d(0_m, 0_m, frc::Rotation2d(0_deg)),
      // Pass through these two interior waypoints, making an 's' curve path
      {frc::Translation2d(2_m, 0_m)},
      // End 3 meters straight ahead of where we started, facing forward
      frc::Pose2d(4_m, 0_m, frc::Rotation2d(0_deg)),
      config);

  frc2::RamseteCommand forwardCommand(
    forward, [this]() { return drive->GetPose(); },
    frc::RamseteController(AutoConstants::kRamseteB, AutoConstants::kRamseteZeta),
    drive->GetFeedForward(), DriveConstants::kDriveKinematics,
    [this] { return drive->GetWheelSpeeds(); },
    frc2::PIDController(DriveConstants::kPDriveVel, 0.0, DriveConstants::kDDriveVel),
    frc2::PIDController(DriveConstants::kPDriveVel, 0.0, DriveConstants::kDDriveVel),
    [this](auto left, auto right) { drive->TankDriveVolts(left, right); },
    {drive});

  frc::Trajectory weavedPath = frc::TrajectoryGenerator::GenerateTrajectory(
      {frc::Pose2d(3_m, -0.7_m, frc::Rotation2d(0_deg)),
       frc::Pose2d(4.942_m, -0.931_m, frc::Rotation2d(-10.3_deg)),
       frc::Pose2d(7.038_m, -0.629_m, frc::Rotation2d(-51.7_deg)),
       frc::Pose2d(7.4_m, -1.536_m, frc::Rotation2d(-86.8_deg)),
       frc::Pose2d(6.03_m, -2.241_m, frc::Rotation2d(-152_deg)),
       frc::Pose2d(3_m, -2.4_m, frc::Rotation2d(-180_deg))},
      config);

  // frc::Trajectory weavedPath = frc::TrajectoryUtil::FromPathweaverJson(deployDirectory);

  frc2::RamseteCommand weavedCommand(
    weavedPath, [this]() { return drive->GetPose(); },
    frc::RamseteController(AutoConstants::kRamseteB, AutoConstants::kRamseteZeta),
    drive->GetFeedForward(), DriveConstants::kDriveKinematics,
    [this] { return drive->GetWheelSpeeds(); },
    frc2::PIDController(DriveConstants::kPDriveVel, 0.0, DriveConstants::kDDriveVel),
    frc2::PIDController(DriveConstants::kPDriveVel, 0.0, DriveConstants::kDDriveVel),
    [this](auto left, auto right) { drive->TankDriveVolts(left, right); },
    {drive});

  frc2::RamseteCommand ToPort(
    port, [this]() { return drive->GetPose(); },
    frc::RamseteController(AutoConstants::kRamseteB, AutoConstants::kRamseteZeta),
    drive->GetFeedForward(), DriveConstants::kDriveKinematics,
    [this] { return drive->GetWheelSpeeds(); },
    frc2::PIDController(DriveConstants::kPDriveVel, 0.0, DriveConstants::kDDriveVel),
    frc2::PIDController(DriveConstants::kPDriveVel, 0.0, DriveConstants::kDDriveVel),
    [this](auto left, auto right) { drive->TankDriveVolts(left, right); },
    {drive});

  AddCommands(
      //       flywheel->SetTarget(0.4);
      //   frc2::InstantCommand([this] {
      //       flywheel->Start();
      //       drive->ResetOdometry(frc::Pose2d(0_m, 0_m, frc::Rotation2d(0_deg)));
      //   }),
      //   frc2::ParallelRaceGroup(
      //       RunIntake(intake),
      //       std::move(ramseteCommand)),
      frc2::InstantCommand([this] { drive->ResetOdometry(frc::Pose2d(0_m, 0_m, frc::Rotation2d(0_deg))); }),
      frc2::ParallelRaceGroup(
          RunIntake(intake),
          std::move(forwardCommand)),
      frc2::SequentialCommandGroup(TurnAngle(180, drive)),
      frc2::InstantCommand([this] { 
        drive->ResetOdometry(
          frc::Pose2d(0_m, 0_m, frc::Rotation2d(0_deg))); }),
      frc2::ParallelRaceGroup(
        frc2::RunCommand([this]{
          flywheel->SetTarget(0.54);
          flywheel->Start();
        }),
        std::move(ToPort)),
      
      frc2::InstantCommand([this] { drive->TankDriveVolts(0_V, 0_V); }, {}));
}
