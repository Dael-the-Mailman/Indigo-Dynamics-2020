/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "RobotContainer.h"
#include "commands/RunFlywheel.h"
#include "commands/RunIntake.h"
#include "commands/BButton.h"
#include "commands/RunDrive.h"
#include "commands/ReverseIntake.h"
#include "commands/WinchUp.h"
#include "commands/WinchManual.h"
#include "commands/VisionAlign.h"
#include "commands/RunPizza.h"
#include "commands/CloseShot.h"
#include "commands/MediumShot.h"
#include "commands/ColorPizza.h"
#include "commands/LEDHandler.h"
#include "commands/AngleAlign.h"

RobotContainer::RobotContainer() : 
AlignWithNearTrenchAuto(&m_drive, &m_intake, &m_timer, &m_flywheel, &m_limelight),
AlignWithPortAuto(&m_drive, &m_intake, &m_timer, &m_flywheel, &m_limelight),
OnTheFly(&m_drive, &m_intake, &m_timer, &m_flywheel, &m_limelight),
ShootStuff(&m_drive, &m_intake, &m_timer, &m_flywheel, &m_limelight),
ShootForward(&m_drive, &m_intake, &m_timer, &m_flywheel, &m_limelight)
{
  // Initialize all of your commands and subsystems here

  // Configure the button bindings
  ConfigureButtonBindings();
  // m_flywheel.SetDefaultCommand(RunFlywheel(&m_flywheel));
  m_drive.SetDefaultCommand(RunDrive(&m_drive, &m_joy));
  m_winch.SetDefaultCommand(WinchManual(&m_winch, 
                                     [this] { return m_partner.GetRawAxis(3); },
                                     [this] { return m_partner.GetRawAxis(2); }));
  m_flywheel.SetDefaultCommand(RunFlywheel(&m_flywheel, 
                                     [this] { return m_partner.GetRawButton(5); }));
  m_blinkin.SetDefaultCommand(LEDHandler(&m_blinkin, 
                                     [this] { return m_intake.IsBroken();}, 
                                     [this] { return m_intake.IsTopBroken();},
                                     [this] { return m_flywheel.ReachedTarget(300);}));

  //Close shot 52%
  //Medium shot 54%
}

void RobotContainer::ConfigureButtonBindings()
{
  // Configure your button bindings here
  frc2::JoystickButton m_pizzaButton{&m_partner, 1};
  frc2::JoystickButton m_bButton{&m_joy, 3};
  // frc2::JoystickButton m_winchUp{&m_partner, 3};
  frc2::JoystickButton m_yButton{&m_partner, 3};
  // frc2::JoystickButton m_leftShoulder{&m_joy, 5};
  frc2::JoystickButton m_rightShoulder{&m_joy, 6};
  frc2::JoystickButton m_visionAlign{&m_joy, 1};
  frc2::JoystickButton m_closeShot{&m_joy, 4};
  frc2::JoystickButton m_mediumShot{&m_joy, 2};
  frc2::JoystickButton m_colorPizza{&m_partner, 4};
  frc2::JoystickButton m_angleAlign{&m_partner, 6};
  m_pizzaButton.WhenPressed(RunPizza(&m_pizzatime));
  m_bButton.WhileHeld(BButton(&m_intake, &m_flywheel));
  m_yButton.WhileHeld(ReverseIntake(&m_intake));
  // m_leftShoulder.WhileHeld(RunFlywheel(0.8, &m_flywheel));
  m_rightShoulder.WhileHeld(RunIntake(&m_intake));
  m_visionAlign.WhileHeld(VisionAlign(&m_limelight, &m_drive, &m_flywheel));
  // m_winchUp.WhenPressed(WinchUp(&m_winch));
  m_closeShot.WhileHeld(CloseShot(&m_limelight, &m_drive, &m_flywheel, &m_intake));
  m_mediumShot.WhileHeld(MediumShot(&m_limelight, &m_drive, &m_flywheel, &m_intake));
  m_colorPizza.WhenPressed(ColorPizza(&m_pizzatime));
  m_angleAlign.WhileHeld(AngleAlign(&m_drive,&m_limelight, &m_flywheel));
}

frc2::Command *RobotContainer::GetAutonomousCommand()
{
  // An example command will be run in autonomous
  CommandSelector autonChoice = SelectOnTheFly;
  switch (autonChoice)
  {
  case (SelectAlignWithNearTrench):
    m_autonomousCommand = &AlignWithNearTrenchAuto;
    break;
  
  case (SelectAlignWithPort):
    m_autonomousCommand = &AlignWithPortAuto;
    break;

  case (SelectOnTheFly):
    m_autonomousCommand = &OnTheFly;
    break;
  
  case (SelectShootStuff):
    m_autonomousCommand = &ShootStuff;
    break;

  case(SelectShootForward):
    m_autonomousCommand = &ShootForward;
    break;

  default:
    break;
  }
  return m_autonomousCommand;
}
