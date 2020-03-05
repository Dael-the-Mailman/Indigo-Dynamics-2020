/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "subsystems/Limelight.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include <networktables/NetworkTable.h>
#include <networktables/NetworkTableInstance.h>

Limelight::Limelight() {}

// This method will be called once per scheduler run
void Limelight::Periodic() {
    std::shared_ptr<NetworkTable> table = nt::NetworkTableInstance::GetDefault().GetTable("limelight");
    tx = table->GetNumber("tx", 0.0);
    ty = table->GetNumber("ty", 0.0);
    ta = table->GetNumber("ta", 0.0);
    tv = table->GetNumber("tv", 0.0);
    pipe = table->GetNumber("getpipe", 0.0);
    table->PutNumber("stream", pipMode);
    frc::SmartDashboard::PutNumber("TX", tx);
    frc::SmartDashboard::PutNumber("TA", ta);
    frc::SmartDashboard::PutNumber("Pipeline", pipe);
    // printf("tx: %.2f\nty: %.2f\nta: %.2f\ntv: %.2f\n", tx, ty, ta, tv);
}

double Limelight::Gettx(){
    return tx;
}

double Limelight::Getty(){
    return ty;
}

double Limelight::Getta(){
    return ta;
}

double Limelight::Gettv(){
    return tv;
}

void Limelight::LEDOff(){
    std::shared_ptr<NetworkTable> table = nt::NetworkTableInstance::GetDefault().GetTable("limelight");
    table->PutNumber("ledMode", 1);
}

void Limelight::LEDOn(){
    std::shared_ptr<NetworkTable> table = nt::NetworkTableInstance::GetDefault().GetTable("limelight");
    table->PutNumber("ledMode", 3);
}

void Limelight::SetPipeline(int pipeline){
    std::shared_ptr<NetworkTable> table = nt::NetworkTableInstance::GetDefault().GetTable("limelight");
    table->PutNumber("pipeline", pipeline);
}

bool Limelight::WithinThreshold(double xThreshold, double areaThreshold, double targetArea){
    if(abs(Gettx()) < xThreshold && abs(targetArea - Getta()) < areaThreshold){
        return true;
    } else {
        return false;
    }
}

void Limelight::EnablePIP(){
    std::shared_ptr<NetworkTable> table = nt::NetworkTableInstance::GetDefault().GetTable("limelight");
    table->PutNumber("stream", 2);
}

void Limelight::EnablePiPMain(){
    pipMode = 1;
}

void Limelight::EnablePiPSecondary(){
    pipMode = 2;
}