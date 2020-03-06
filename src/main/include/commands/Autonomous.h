/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/CommandHelper.h>
#include <frc2/command/SequentialCommandGroup.h>
#include <frc/controller/PIDController.h>
#include <frc/controller/RamseteController.h>
#include <frc/shuffleboard/Shuffleboard.h>
#include <frc/trajectory/Trajectory.h>
#include <frc/trajectory/TrajectoryGenerator.h>
#include <frc/trajectory/constraint/DifferentialDriveVoltageConstraint.h>
#include <frc/Timer.h>
#include <frc2/command/InstantCommand.h>
#include <frc2/command/RamseteCommand.h>
#include <frc2/command/RunCommand.h>
#include <frc2/command/ConditionalCommand.h>
#include <frc2/command/PerpetualCommand.h>
#include <frc2/command/ParallelCommandGroup.h>
#include <frc2/command/ParallelRaceGroup.h>
#include <frc/Filesystem.h>
#include <frc/trajectory/TrajectoryUtil.h>
#include <wpi/Path.h>
#include <wpi/SmallString.h>
#include "subsystems/Drive.h"
#include "subsystems/Intake.h"
#include "subsystems/Flywheel.h"
#include "subsystems/Limelight.h"
#include "Constants.h"

class Autonomous
    : public frc2::CommandHelper<frc2::SequentialCommandGroup,
                                 Autonomous> {
 public:
  Autonomous(Drive* DriveReference, Intake* IntakeReference, frc::Timer* TimerReference, Flywheel* FlywheelReference, Limelight* LimelightReference);
  

 private:
  Drive* drive;
  Intake* intake;
  Flywheel* flywheel;
  Limelight* limelight;
  frc::Timer *timer;
};
