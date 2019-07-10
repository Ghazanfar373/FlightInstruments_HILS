#ifndef MY_PARAMETERS_H
#define MY_PARAMETERS_H

#include <QTime>
#include <QTimer>
#include <thread.h>
#include <QtCore>
#include <communication.h>
#include <QObject>



class My_Parameters : public QObject
{
    Q_OBJECT

public:
    explicit My_Parameters(QObject *parent = nullptr);

    float getAlpha();
    void setAlpha(float value);

    float getBeta() const;
    void setBeta(float value);

    float getSlipSkid() const;
    void setSlipSkid(float value);

    float getTurnRate() const;
    void setTurnRate(float value);

    float getDevH() const;
    void setDevH(float value);

    float getDevV() const;
    void setDevV(float value);

    float getAirspeed() const;
    void setAirspeed(float value);

    float getPressure() const;
    void setPressure(float value);

    float getClimbRate() const;
    void setClimbRate(float value);

    float getMachNo() const;
    void setMachNo(float value);

    float getAdf() const;
    void setAdf(float value);

    float getDme() const;
    void setDme(float value);

    uint getHeader() const;
    void setHeader(const uint &value);

    // PFD Parameters

    float getRoll();
    void setRoll(float value);

    float getPitch() const;
    void setPitch(float value);

    float getHeading() const;
    void setHeading(float value);

    float getAltitude() const;
    void setAltitude(float value);

    float getAileron() const;
    void setAileron(float value);

    float getElevator() const;
    void setElevator(float value);

    float getRudder() const;
    void setRudder(float value);

    float getVertical_velocity() const;
    void setVertical_velocity(float value);

    float getVelocity_knotts() const;
    void setVelocity_knotts(float value);

    float getPhi_dot() const;
    void setPhi_dot(float value);

    float getPsi_dot() const;
    void setPsi_dot(float value);

    float getTheta_dot() const;
    void setTheta_dot(float value);

    float getTrim_button() const;
    void setTrim_button(float value);

signals:

public slots:

private:

    uint header     =  0;
    float alpha     =  0.0f;
    float beta      =  0.0f;
    float slipSkid  =  0.0f;
    float turnRate  =  0.0f;
    float devH      =  0.0f;
    float devV      =  0.0f;
    float airspeed  =  0.0f;
    float pressure  =  0.0f;
    float climbRate =  0.0f;
    float machNo    =  0.0f;
    float adf       =  0.0f;
    float dme       =  0.0f;



    // PFD Parameters

    QString Header = "AA";
    float Aileron  =  0.0;
    float Elevator =  0.0;
    float Rudder   =  0.0;
    float Roll     =  0.0;
    float Pitch    =  0.0;
    float Heading  =  0.0;
    float Altitude =  0.0;
    float vertical_velocity = 0.0;
    float velocity_knotts = 0.0;
    float phi_dot = 0.0;
    float psi_dot = 0.0;
    float Theta_dot = 0.0;
    float trim_button = 0.0;

};

#endif // MY_PARAMETERS_H
