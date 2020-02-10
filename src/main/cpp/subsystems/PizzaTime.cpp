/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/PizzaTime.h"

PizzaTime::PizzaTime() {
    m_colorMatcher.AddColorMatch(kBlueTarget);
    m_colorMatcher.AddColorMatch(kGreenTarget);
    m_colorMatcher.AddColorMatch(kRedTarget);
    m_colorMatcher.AddColorMatch(kYellowTarget);
    spin->ConfigFactoryDefault();
    spin->SetNeutralMode(NeutralMode::Brake);
}

// This method will be called once per scheduler run
void PizzaTime::Periodic() {
    frc::Color detectedColor = m_colorSensor.GetColor();
    std::string colorString;
    double confidence = 0.0;
    frc::Color matchedColor = m_colorMatcher.MatchClosestColor(detectedColor, confidence);
    if (matchedColor == kBlueTarget)
    {
        colorString = "Blue";
    }
    else if (matchedColor == kRedTarget)
    {
        colorString = "Red";
    }
    else if (matchedColor == kGreenTarget)
    {
        colorString = "Green";
    }
    else if (matchedColor == kYellowTarget)
    {
        colorString = "Yellow";
    }
    else
    {
        colorString = "Unknown";
    }
    
    frc::SmartDashboard::PutNumber("Red", detectedColor.red);
    frc::SmartDashboard::PutNumber("Green", detectedColor.green);
    frc::SmartDashboard::PutNumber("Blue", detectedColor.blue);
    frc::SmartDashboard::PutNumber("Confidence", confidence);
    frc::SmartDashboard::PutString("Detected Color", colorString);
}

std::string PizzaTime::GetColor() {
    frc::Color detectedColor = m_colorSensor.GetColor();
    std::string colorString;
    double confidence = 0.0;
    frc::Color matchedColor = m_colorMatcher.MatchClosestColor(detectedColor, confidence);
    if (matchedColor == kBlueTarget)
    {
        colorString = "Blue";
    }
    else if (matchedColor == kRedTarget)
    {
        colorString = "Red";
    }
    else if (matchedColor == kGreenTarget)
    {
        colorString = "Green";
    }
    else if (matchedColor == kYellowTarget)
    {
        colorString = "Yellow";
    }
    else
    {
        colorString = "Unknown";
    }
    return colorString;
}

void PizzaTime::StartSpin(){
    spin->Set(ControlMode::PercentOutput, 1.0);
}

void PizzaTime::StopSpin(){
    spin->Set(ControlMode::PercentOutput, 0.0);
}