/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/Joystick.h>
#include <frc/XboxController.h>
#include <frc/Timer.h>
#include <frc2/command/Command.h>
#include <frc2/command/button/Button.h>
#include <frc2/command/button/JoystickButton.h>
#include <frc2/command/SelectCommand.h>
#include <frc2/command/RunCommand.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include "subsystems/Flywheel.h"
#include "subsystems/Intake.h"
#include "subsystems/Drive.h"
#include "subsystems/Winch.h"
#include "subsystems/Limelight.h"
#include "subsystems/PizzaTime.h"
#include "subsystems/Blinkin.h"
#include "commands/Autonomous.h"
#include "commands/AlignWithPort.h"
#include "commands/OnTheFlyAuton.h"
#include "commands/Shoot3CellsThenBackup.h"
#include "commands/Shoot3CellsThenForward.h"
/**
 * This class is where the bulk of the robot should be declared.  Since
 * Command-based is a "declarative" paradigm, very little robot logic should
 * actually be handled in the {@link Robot} periodic methods (other than the
 * scheduler calls).  Instead, the structure of the robot (including subsystems,
 * commands, and button mappings) should be declared here.
 */
class RobotContainer
{
public:
  RobotContainer();

  frc2::Command *GetAutonomousCommand();

private:
  // The robot's subsystems and commands are defined here...
  Drive m_drive;
  Flywheel m_flywheel;
  Intake m_intake;
  Winch m_winch;
  Limelight m_limelight;
  PizzaTime m_pizzatime;
  frc::Timer m_timer;
  Blinkin m_blinkin;

  frc::Joystick m_joy{0};
  frc::Joystick m_partner{2};

  Autonomous AlignWithNearTrenchAuto;
  AlignWithPort AlignWithPortAuto;
  OnTheFlyAuton OnTheFly;
  Shoot3CellsThenBackup ShootStuff;
  Shoot3CellsThenForward ShootForward;

  frc2::Command* m_autonomousCommand = nullptr;

  enum CommandSelector {SelectAlignWithNearTrench, 
                        SelectAlignWithPort,
                        SelectOnTheFly,
                        SelectShootStuff,
                        SelectShootForward};

  void ConfigureButtonBindings();
};
