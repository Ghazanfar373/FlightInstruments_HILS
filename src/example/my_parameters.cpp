#include "my_parameters.h"
#include <iostream>
#include <math.h>
#include <QDebug>
#include <QTimer>
#include <QTime>
#include <QTimerEvent>
#include <thread.h>
#include <QtCore>
#include <communication.h>

My_Parameters::My_Parameters(QObject *parent) : QObject(parent)
{


}

void My_Parameters::setAlpha(float value)
{

    alpha = value;
}

float My_Parameters::getAlpha()
{
    return alpha;
}

float My_Parameters::getBeta() const
{
    return beta;
}

void My_Parameters::setBeta(float value)
{
    beta = value;
}

//**************Parameters not needed yet**************//

float My_Parameters::getSlipSkid() const
{
    return slipSkid;
}

void My_Parameters::setSlipSkid(float value)
{

    slipSkid = value;
}

//**************xxxxxxxxxxxxxxxxxxxxxxx**************//

float My_Parameters::getTurnRate() const
{
    return turnRate;
}

void My_Parameters::setTurnRate(float value)
{

    turnRate = value;
}

//**************Parameters not needed yet**************//

float My_Parameters::getDevH() const
{
    return devH;
}

void My_Parameters::setDevH(float value)
{

    devH = value;
}

float My_Parameters::getDevV() const
{
    return devV;
}

void My_Parameters::setDevV(float value)
{

    devV = value;
}


//**************xxxxxxxxxxxxxxxxxxxxxxx**************//

float My_Parameters::getAirspeed() const
{
    return airspeed;
}

void My_Parameters::setAirspeed(float value)
{

    airspeed = value;
}



//**************Parameters not needed yet**************//


float My_Parameters::getPressure() const
{
    return pressure;
}

void My_Parameters::setPressure(float value)
{

    pressure = value;
}

float My_Parameters::getClimbRate() const
{
    return climbRate;
}

void My_Parameters::setClimbRate(float value)
{

    climbRate = value;
}

float My_Parameters::getMachNo() const
{
    return machNo;
}

void My_Parameters::setMachNo(float value)
{

    machNo = value;
}


//**************xxxxxxxxxxxxxxxxxxxxxxx**************//

float My_Parameters::getAdf() const
{
    return adf;
}

void My_Parameters::setAdf(float value)
{

    adf = value;
}

float My_Parameters::getDme() const
{
    return dme;
}

void My_Parameters::setDme(float value)
{

    dme = value;
}

uint My_Parameters::getHeader() const
{
    return header;
}

void My_Parameters::setHeader(const uint &value)
{
    header = value;
}


//******************PFD Getter Setter********************//


float My_Parameters::getTrim_button() const
{
    return trim_button;
}

void My_Parameters::setTrim_button(float value)
{
    trim_button = value;
}

float My_Parameters::getTheta_dot() const
{
    return Theta_dot;
}

void My_Parameters::setTheta_dot(float value)
{
    Theta_dot = value;
}

float My_Parameters::getPsi_dot() const
{
    return psi_dot;
}

void My_Parameters::setPsi_dot(float value)
{
    psi_dot = value;
}

float My_Parameters::getPhi_dot() const
{
    return phi_dot;
}

void My_Parameters::setPhi_dot(float value)
{
    phi_dot = value;
}

float My_Parameters::getVelocity_knotts() const
{
    return velocity_knotts;
}

void My_Parameters::setVelocity_knotts(float value)
{
    velocity_knotts = value;
}

float My_Parameters::getVertical_velocity() const
{
    return vertical_velocity;
}

void My_Parameters::setVertical_velocity(float value)
{
    vertical_velocity = value;
}

float My_Parameters::getRudder() const
{
    return Rudder;
}

void My_Parameters::setRudder(float value)
{
    Rudder = value;
}

float My_Parameters::getElevator() const
{
    return Elevator;
}

void My_Parameters::setElevator(float value)
{
    Elevator = value;
}

float My_Parameters::getAileron() const
{
    return Aileron;
}

void My_Parameters::setAileron(float value)
{
    Aileron = value;
}

float My_Parameters::getAltitude() const
{
    return Altitude;
}

void My_Parameters::setAltitude(float value)
{
    Altitude = value;
}

float My_Parameters::getRoll()
{
    return Roll;
}

void My_Parameters::setRoll(float value)
{
      Roll = value;
}

float My_Parameters::getPitch() const
{
    return Pitch;
}

void My_Parameters::setPitch(float value)
{
    Pitch = value;
}

float My_Parameters::getHeading() const
{
    return Heading;
}

void My_Parameters::setHeading(float value)
{
    Heading = value;
}


