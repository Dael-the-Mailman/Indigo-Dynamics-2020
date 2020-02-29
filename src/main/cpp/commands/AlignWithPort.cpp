/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/AlignWithPort.h"
#include "commands/BButton.h"
#include "commands/RunIntake.h"
#include "commands/TurnAngle.h"
#include "commands/Shoot.h"
#include "commands/VisionAlignAction.h"
#include "commands/AlignCells.h"

// NOTE:  Consider using this command inline, rather than writing a subclass.
// For more information, see:
// https://docs.wpilib.org/en/latest/docs/software/commandbased/convenience-features.html
AlignWithPort::AlignWithPort(Drive *DriveReference, Intake *IntakeReference, frc::Timer *TimerReference, Flywheel *FlywheelReference, Limelight *LimelightReference)
    : drive{DriveReference}, intake{IntakeReference}, timer{TimerReference}, flywheel{FlywheelReference}, limelight{LimelightReference}
{
  AddRequirements({drive});
  AddRequirements({intake});
  AddRequirements({flywheel});
  AddRequirements({limelight});

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

  frc::Trajectory Get3Cells = frc::TrajectoryGenerator::GenerateTrajectory(
    frc::Pose2d(0_m, 0_m, frc::Rotation2d(0_deg)),
    {},
    frc::Pose2d(4.2_m, 0_m, frc::Rotation2d(0_deg)),
    config);

  frc2::RamseteCommand Get3CellsCommand(
    Get3Cells, [this]() { return drive->GetPose(); },
    frc::RamseteController(AutoConstants::kRamseteB, AutoConstants::kRamseteZeta),
    drive->GetFeedForward(), DriveConstants::kDriveKinematics,
    [this] { return drive->GetWheelSpeeds(); },
    frc2::PIDController(DriveConstants::kPDriveVel, 0.0, DriveConstants::kDDriveVel),
    frc2::PIDController(DriveConstants::kPDriveVel, 0.0, DriveConstants::kDDriveVel),
    [this](auto left, auto right) { drive->TankDriveVolts(left, right); },
    {drive});

  AddCommands(
      frc2::InstantCommand([this] {
        drive->ResetAngle();
        drive->ResetOdometry(frc::Pose2d{0_m, 0_m, frc::Rotation2d(0_deg)});
      }),
      frc2::ParallelRaceGroup(
          TurnAngle(25, drive),
          frc2::RunCommand([this] {
            flywheel->SetTarget(0.60);
            flywheel->Start();
          })),
      Shoot(5.0, 0.54, flywheel, intake, timer),
      frc2::InstantCommand([this] {
        drive->ResetAngle();
      }),
      TurnAngle(155, drive),
      frc2::InstantCommand([this] {
        drive->ResetOdometry(frc::Pose2d{0_m, 0_m, frc::Rotation2d(0_deg)});
      }),
      frc2::ParallelRaceGroup(
          std::move(Get3CellsCommand),
          frc2::RunCommand([this] {
            flywheel->SetTarget(0.6);
            flywheel->Start();
          }),
          RunIntake(intake)),
      TurnAngle(360, drive),
      VisionAlignAction(false, drive, limelight),
      Shoot(5.0, 0.6, flywheel, intake, timer),
      frc2::InstantCommand([this] {
        drive->TankDriveVolts(0_V, 0_V);
      },
                           {}));
}
