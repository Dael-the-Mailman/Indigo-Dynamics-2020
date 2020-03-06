/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/OnTheFlyAuton.h"
#include "commands/BButton.h"
#include "commands/RunIntake.h"
#include "commands/TurnAngle.h"
#include "commands/Shoot.h"
#include "commands/VisionAlignAction.h"
#include "commands/AlignCells.h"

// NOTE:  Consider using this command inline, rather than writing a subclass.
// For more information, see:
// https://docs.wpilib.org/en/latest/docs/software/commandbased/convenience-features.html
OnTheFlyAuton::OnTheFlyAuton(Drive *DriveReference, Intake *IntakeReference, frc::Timer *TimerReference, Flywheel *FlywheelReference, Limelight *LimelightReference)
  : drive{DriveReference}, intake{IntakeReference}, timer{TimerReference}, flywheel{FlywheelReference}, limelight{LimelightReference}
{
  AddRequirements({drive});
  AddRequirements({intake});
  AddRequirements({flywheel});
  AddRequirements({limelight});
  // Add your commands here, e.g.
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

  AddCommands(
    frc2::InstantCommand([this]{
      drive->ResetAngle();
      frc::SmartDashboard::PutString("Auton Status", "Not Finished");
    }),
    TurnAngle(180, drive),
    frc2::InstantCommand([this]{
      frc::SmartDashboard::PutString("Auton Status", "Finished");
    })
  );
}
