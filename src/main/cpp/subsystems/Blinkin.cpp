/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Blinkin.h"

Blinkin::Blinkin() {}

// This method will be called once per scheduler run
void Blinkin::Periodic() {

}

void Blinkin::SolidBlue(){
    LEDDriver->Set(0.87);
}

void Blinkin::Default(){
    LEDDriver->Set(0.99);
}

void Blinkin::SolidIndigo(){
    LEDDriver->Set(0.89);
}

void Blinkin::SolidHotPink(){
    LEDDriver->Set(0.57);
}

void Blinkin::StrobeGold(){
    LEDDriver->Set(-0.07);
}

