/***************************************************************************//**
 * @file example/MainWindow.cpp
 * @author  Marek M. Cel <marekcel@marekcel.pl>
 *
 * @section LICENSE
 *
 * Copyright (C) 2013 Marek M. Cel
 *
 * This file is part of QFlightInstruments. You can redistribute and modify it
 * under the terms of GNU General Public License as published by the Free
 * Software Foundation; either version 3 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.
 * 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 * Further information about the GNU General Public License can also be found
 * on the world wide web at http://www.gnu.org.
 *
 * ---
 *
 * Copyright (C) 2013 Marek M. Cel
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 ******************************************************************************/
#ifndef MAINWINDOW_CPP
#define MAINWINDOW_CPP
#endif

////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <math.h>
#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <my_parameters.h>
#include <QDebug>
#include <comm.h>
#include <communication.h>
#include <QtCore>
#include <QMessageBox>
#include <QListWidget>
#include <QMetaObject>
#include <QFile>
#include <QProcess>
#include <QDesktopServices>
#include <QDateTimeAxis>
#include <QValueAxis>



////////////////////////////////////////////////////////////////////////////////

using namespace std;

////////////////////////////////////////////////////////////////////////////////

MainWindow::MainWindow( QWidget *parent ) :
    QMainWindow( parent ),
    m_ui( new Ui::MainWindow )

{
    m_ui->setupUi( this );

    QCoreApplication::setApplicationName( QString("CommHub HUD") );
    setWindowTitle( QCoreApplication::applicationName() );

    mThread = new Thread(this);
    connect(mThread,SIGNAL(NumberChanged(int)),this,SLOT(recieve_udpPacket()));

    mUpdateGUIthread = new Thread_updateGUI(this);
    connect(mUpdateGUIthread,SIGNAL(Number_Changed(int)),this,SLOT(updateGUI()));

    m_ui->Status->hide();
    m_ui->footer_banner->setScaledContents(true);


    //my_charts <<chartview;
    //timer.stop();
    chartview = new QChartView(createSpLineChart());
    m_ui->gridLayout_Chart->addWidget(chartview,0,0);

   // series->append(200,0);
    //createSpLineChart();

}

MainWindow::~MainWindow()
{
  mThread->quit();
  mThread->wait();
  mUpdateGUIthread->quit();
  mUpdateGUIthread->wait();
}
void MainWindow::closeEvent(QCloseEvent *event)
{
  mThread->terminate();
  mUpdateGUIthread->terminate();
}

void MainWindow::recieve_udpPacket()
{
  // m_datagram.clear();
   m_datagram= comm.recieve_packet();
   bitShifting(m_datagram);

}

void MainWindow::bitShifting(QByteArray m_datagram)
{

    qDebug()<<"In bitshifting function";

    qDebug()<< m_datagram;
    if(m_datagram.size()==29){
    if((uint8_t)m_datagram[0] == 170){


    Heading = (uint8_t)(m_datagram[13] << 8) ^ (uint8_t)(m_datagram[14]);//*0.25;
    //Heading = (uint8_t)m_datagram[13]  + (uint8_t)(m_datagram[14]);
    // Pitch = (int8_t)(m_datagram[11])  ^ (int8_t)((m_datagram[12]& 0xf)<<8);
    Pitch=(int8_t)(m_datagram[11] << 8) ^ (int8_t)(m_datagram[12]);
    Roll = (int8_t)(m_datagram[9] << 8) ^ (int8_t)(m_datagram[10]);
    Airspeed = (uint8_t)(m_datagram[19] << 8) ^ (uint8_t)(m_datagram[20]);
    Altitude = (uint8_t)(m_datagram[15] << 8) ^ (uint8_t)m_datagram[16];
    Vertical_Speed = (int8_t)(m_datagram[17] <<8) ^ (int8_t)m_datagram[18];
    SlipSkid = (int8_t)(m_datagram[9] << 8) ^ (int8_t)(m_datagram[10]);
    TurnRate = (int8_t)(m_datagram[9] << 8) ^ (int8_t)(m_datagram[10]);
    Pressure = (uint8_t)m_datagram[1] + (uint8_t)m_datagram[1];


     temp_list.append(Heading);
     temp_list.append(Pitch);
     temp_list.append(Roll);
     temp_list.append(Airspeed);
     temp_list.append(Altitude);
     temp_list.append(Vertical_Speed);
     temp_list.append(SlipSkid);
     temp_list.append(TurnRate);
     temp_list.append(Pressure);



}else {
qDebug()<< "Header not matching";
}
}else {
qDebug()<< "Datagram size is erronious";
}
   settingParameters();
   m_datagram.resize(29);

}


QChart *MainWindow::createSpLineChart(){

    QObject::connect(&timer, &QTimer::timeout, this, &MainWindow::update_S_Chart);
    timer.setInterval(110);  //left here
    //timer.start();

    series= new QSplineSeries();

//    QDateTime current_Time = QDateTime::currentDateTime();

//    qDebug()<< current_Time;


    //QDateTime momentInTime;
    //momentInTime.setTime(current_Time);


    // series->append(,momentInTime.toLocalTime())
    //series->append(momentInTime.toMSecsSinceEpoch(), values[2].toDouble());
    //qreal x = plotArea().width() / m_axisX->tickCount();


    chart->addSeries(series);

    axis_X = new QValueAxis;
    //axis_X->setLabelFormat("%i");
    axis_X->setTickCount(10);
    axis_X->setTitleText("Current Index");
    axis_X->setRange(0,100);
    chart->addAxis(axis_X, Qt::AlignBottom);
    series->attachAxis(axis_X);

//    dateTimeAxis = new QDateTimeAxis;
//    dateTimeAxis->setTickCount(10);
//    dateTimeAxis->setFormat("hh:mm");
//    //dateTimeAxis->setRange(2,60);
//    //dateTimeAxis->setMin(current_Time.addSecs(-60 / 2));
//    dateTimeAxis->setMax(current_Time.addSecs( 60 / 2));
//    dateTimeAxis->setTitleText("Current Index");
//    chart->addAxis(dateTimeAxis, Qt::AlignBottom);
//    series->attachAxis(dateTimeAxis);


    axis_Y = new QValueAxis;
    //axis_Y->setLabelFormat("%i");
    axis_Y->setTickCount(10);
    axis_Y->setRange(0,10000);
    axis_Y->setTitleText("Altitude");
    chart->addAxis(axis_Y, Qt::AlignLeft);
    series->attachAxis(axis_Y);


    //qreal x = plotArea().width() / m_axisX->tickCount();
    //qreal y = (m_axisX->max() - m_axisX->min()) / m_axisX->tickCount();
    //m_x += y;
    //m_y = QRandomGenerator::global()->bounded(5) - 2.5;
    //m_series->append(m_x, m_y);

     //left here


//    QDateTimeAxis *axis_Y = new QDateTimeAxis;
//    axis_Y->setTickCount(10);
//    //axis_Y->setFormat("MMM yyyy");
//    axis_Y->setTitleText("Current Time");
//    axis_X->setRange(0,10);
//    chart->addAxis(axis_Y, Qt::AlignBottom);
//    series->attachAxis(axis_Y);
    //chart->createDefaultAxes();
    //chart->axisX()->setTitleText("Current Time");
    //chart->axisY()->setTitleText("Data");

    //chart->legend()->setVisible(false);





   // chart->setAnimationOptions(QChart::AnimationOption::AllAnimations);
    chart->legend()->hide();
    //chart->paint();
    chartview = new QChartView(chart);
    chartview->setRenderHint(QPainter::Antialiasing);
    chartview->setRubberBand(QChartView::HorizontalRubberBand);

//    connect(&timer, SIGNAL(timeout()), this, SLOT(update_S_Chart()));
//    timer.setInterval(1000);
//    timer.start();

    //chartview->update();
    //chart->removeSeries(series);

    //chartview->repaint();


    //timer.start();


    return chart;


}

void MainWindow::update_S_Chart()
{
    x = chartview->chart()->plotArea().width() / axis_X->max();
    //m_y = (axis_X->max() - axis_X->min()) / axis_X->tickCount();
    //m_x += m_y;
    chart->scroll(x,0);
}

void MainWindow::settingParameters()
{

    qDebug()<<"In setting parameters function";

    //*************Setting Parameters***************//

    qDebug()<<"Heading" << Heading;
    qDebug()<<"Pitch" << Pitch;
    qDebug()<<"Roll" << Roll;
    qDebug()<<"Airspeed" << Airspeed;
    qDebug()<<"Altitude" << Altitude;
    qDebug()<<"Vertical Speed" << Vertical_Speed;
    qDebug()<<"SlipSkid" << SlipSkid;
    qDebug()<<"Turn Rate" << TurnRate;
    qDebug()<<"Pressure" << Pressure;

    float headval=(Heading*3.0f)-25;
    if(headval>0) parameters.setHeading(headval);
    parameters.setRoll(Roll);
    parameters.setPitch(Pitch);
    float altival=(Altitude*250.0f);
    parameters.setAltitude(altival);
    parameters.setAirspeed(Airspeed*3.2f);
    parameters.setClimbRate(Vertical_Speed*2.0f);
    parameters.setSlipSkid(SlipSkid);
    parameters.setTurnRate(TurnRate);
    parameters.setPressure(Pressure);

    qDebug()<<"Setting series of chart";

    series->append(m_x++, altival);


    //m_x += Altitude*250.0f;0

//    x = chart->plotArea().width() / axis_X->tickCount();
//    m_y = (axis_X->max() - axis_X->min()) / axis_X->tickCount();
//    m_x += m_y;
//    scroll(x,0);

    //chartview->setChart(createSpLineChart());
    //chartview = new QChartView(createSpLineChart());
   // x = chartview->chart()->plotArea().width() / axis_X->tickCount();
   // chart->scroll(x,0);

    //m_y = (axis_X->max() - axis_X->min()) / axis_X->tickCount();
    //m_x += m_y;

    //m_ui->gridLayout_Chart->addWidget(chartview,0,0);



   // timer.start();

    //***************ComboBox Params Testing*******************//

//    if(m_ui->CB_Plot_Parameters->itemText(1) == "Altitude" )
//    {
//      chart->removeSeries(series);
//      series->append(m_x++, altival);
//      axis_Y->setTitleText("Altitude");
//    }
//    else if (m_ui->CB_Plot_Parameters->itemText(2) == "Airspeed") {
//      chart->removeSeries(series);
//      series->append(m_x++, Airspeed*3.2f);
//      axis_Y->setTitleText("Airspeed");
//    }
//    else if (m_ui->CB_Plot_Parameters->itemText(3) == "Pitch") {
//      chart->removeSeries(series);
//      series->append(m_x++, Pitch);
//      axis_Y->setTitleText("Pitch");
//    }


    //***************ComboBox Params Testing*******************//




    //chart->scroll(chart->plotArea().width()/axis_X->max(),0);



}

void MainWindow::gettingParameters()
{
    qDebug()<<"In getting parameters function";

    qDebug()<<"Heading" << parameters.getHeading();
    qDebug()<<"Pitch" << parameters.getPitch();
    qDebug()<<"Roll" << parameters.getRoll();
    qDebug()<<"Airspeed" << parameters.getAirspeed();
    qDebug()<<"Altitude" << parameters.getAltitude();
    qDebug()<<"Vertical Speed" << parameters.getVertical_velocity();
    qDebug()<<"SlipSkid" << parameters.getSlipSkid();
    qDebug()<<"Turn Rate" << parameters.getTurnRate();
    qDebug()<<"Pressure" << parameters.getPressure();

//    m_ui->spinBoxAlpha ->setValue( parameters.getAlpha() );
//    m_ui->spinBoxBeta  ->setValue( parameters.getBeta() );
      m_ui->spinBoxRoll  ->setValue( parameters.getRoll() );
      m_ui->spinBoxPitch ->setValue( parameters.getPitch() );
      m_ui->spinBoxTurn  ->setValue( parameters.getTurnRate() );
      m_ui->spinBoxHead  ->setValue( parameters.getHeading() );
      m_ui->spinBoxSpeed ->setValue( parameters.getAirspeed() );
      m_ui->spinBoxAlt   ->setValue( parameters.getAltitude() );
//    m_ui->spinBoxADF   ->setValue( parameters.getAdf() );
//    m_ui->spinBoxDME   ->setValue( parameters.getDme() );
      m_ui->spinBoxClimb ->setValue(parameters.getClimbRate() );

//    m_ui->widgetSix->setSlipSkid  ( parameters.getSlipSkid()  );
//    m_ui->widgetSix->setTurnRate  ( parameters.getTurnRate()  );
//    m_ui->widgetSix->setClimbRate ( parameters.getClimbRate() );


    m_ui->widgetSix->setwidPFD(parameters.getAlpha(),parameters.getBeta(),parameters.getRoll(),
                               parameters.getPitch(),parameters.getSlipSkid(),parameters.getTurnRate(),parameters.getDevH(),
                               parameters.getDevV(),parameters.getHeading(),parameters.getAirspeed(),parameters.getMachNo(),
                               parameters.getAltitude(),parameters.getPressure(),parameters.getClimbRate());


    m_ui->widgetSix->setHeading   ( parameters.getHeading() );
    m_ui->widgetSix->setPitch     ( parameters.getPitch() );
    m_ui->widgetSix->setAltitude  ( parameters.getAltitude() );
    m_ui->widgetSix->setAirspeed  ( parameters.getAirspeed() );
    m_ui->widgetSix->setRoll      ( parameters.getRoll() );
    m_ui->widgetSix->setClimbRate ( parameters.getClimbRate() );
    m_ui->widgetSix->setSlipSkid  ( parameters.getSlipSkid() );
    m_ui->widgetSix->setTurnRate  ( parameters.getTurnRate() );
//    m_ui->widgetSix->setPressure  ( parameters.getPressure() );
    m_ui->widgetSix->setwidNAV(parameters.getHeading(),parameters.getAdf(), parameters.getDevH(), parameters.getDme());

}

void MainWindow::reset_widgets()
{

    //Resetting widgets to zero

      parameters.setAlpha(0);
      parameters.setBeta(0);
      parameters.setRoll(0);
      parameters.setPitch(0);
      parameters.setHeading(0);
      parameters.setTurnRate(0);
      parameters.setAirspeed(0);
      parameters.setAltitude(0);
      parameters.setClimbRate(0);
      parameters.setSlipSkid(0);
      parameters.setAdf(0);
      parameters.setDevH(0);
      parameters.setDevV(0);
      parameters.setDme(0);
      parameters.setPressure(0);


    m_ui->spinBoxAlpha ->setValue( parameters.getAlpha() );
    m_ui->spinBoxBeta  ->setValue( parameters.getBeta() );
    m_ui->spinBoxRoll  ->setValue( parameters.getRoll() );
    m_ui->spinBoxPitch ->setValue( parameters.getPitch() );
    m_ui->spinBoxTurn  ->setValue( parameters.getTurnRate() );
    m_ui->spinBoxHead  ->setValue( parameters.getHeading() );
    m_ui->spinBoxSpeed ->setValue( parameters.getAirspeed() );
    m_ui->spinBoxAlt   ->setValue( parameters.getAltitude() );
    m_ui->spinBoxADF   ->setValue( parameters.getAdf() );
    m_ui->spinBoxDME   ->setValue( parameters.getDme() );
    m_ui->spinBoxClimb ->setValue( parameters.getClimbRate() );



    m_ui->widgetSix->setSlipSkid  ( parameters.getSlipSkid()  );
    m_ui->widgetSix->setTurnRate  ( parameters.getTurnRate()  );
    m_ui->widgetSix->setClimbRate ( parameters.getClimbRate() );


    m_ui->widgetSix->setwidPFD(parameters.getAlpha(),parameters.getBeta(),parameters.getRoll(),
                               parameters.getPitch(),parameters.getSlipSkid(),parameters.getTurnRate(),parameters.getDevH(),
                               parameters.getDevV(),parameters.getHeading(),parameters.getAirspeed(),parameters.getMachNo(),parameters.getAltitude(),
                               parameters.getPressure(),parameters.getClimbRate());



    m_ui->widgetSix->setwidNAV(parameters.getHeading(),parameters.getAdf(), parameters.getDevH(), parameters.getDme());

    m_ui->widgetSix->setHeading   ( parameters.getHeading() );
    m_ui->widgetSix->setPitch     ( parameters.getPitch() );
    m_ui->widgetSix->setAltitude  ( parameters.getAltitude() );
    m_ui->widgetSix->setAirspeed  ( parameters.getAirspeed() );
    m_ui->widgetSix->setRoll      ( parameters.getRoll() );
    m_ui->widgetSix->setClimbRate ( parameters.getClimbRate() );
    m_ui->widgetSix->setSlipSkid  ( parameters.getSlipSkid() );
    m_ui->widgetSix->setTurnRate  ( parameters.getTurnRate() );
    m_ui->widgetSix->setPressure  ( parameters.getPressure() );


    m_ui->widgetSix->update();
}

void MainWindow::updateGUI()
{
   gettingParameters();



   if (thread()==QThread::currentThread())
   {
      QMetaObject::invokeMethod(this,"updateWidgets", Qt::QueuedConnection);
      //QMetaObject::invokeMethod(this,"Make_SplineChart", Qt::QueuedConnection);

      return;
   }

}

void MainWindow::Make_SplineChart()
{
    //qDebug()<<"Setting Spline Chart";
    //chartview = new QChartView(createSpLineChart());
    //createSpLineChart();
    //m_ui->gridLayout_Chart->addWidget(chartview,0,0);
    //for(unsigned short i=0;i<10;i++){
    //int i=Altitude;
       //series->append(Airspeed,Altitude);
       //qDebug()<< "*******" <<Altitude << "*******";
    //}

}

void MainWindow::updateWidgets()
{

    //createSpLineChart();
    //updateListbox();
    //createChart();
    //chartview = new QChartView(createSpLineChart());
    m_ui->widgetSix->update();
    //createSpLineChart();

}

//void MainWindow::updateListbox()
//{

//    qDebug()<<"updatelistbox function"<<temp_list[0];

//    m_ui->listWidget->addItem("Heading: "+QString::number(Heading));
//    m_ui->listWidget->addItem("Pitch: "+QString::number(Pitch));
//    m_ui->listWidget->addItem("Roll: "+QString::number(Roll));
//    m_ui->listWidget->addItem("Airspeed: "+QString::number(Airspeed));
//    m_ui->listWidget->addItem("Altitude: "+QString::number(Altitude));
//    m_ui->listWidget->addItem("Vertical Speed: "+QString::number(temp_list[5]));
//    m_ui->listWidget->addItem("Slip Skid: "+QString::number(temp_list[6]));
//    m_ui->listWidget->addItem("TurnRate: "+QString::number(temp_list[7]));
//    m_ui->listWidget->addItem("Pressure: "+QString::number(temp_list[8]));

//}

void MainWindow::on_btn_startComm_clicked()
{
    timer.start();

    //Thread 1 Recieving and Spliting Packet

    mThread->start();

    //Thread 2 Updating GUI

    mUpdateGUIthread->start();

}
void MainWindow::on_btn_connect_clicked()
{

    comm.connectToPort();

    QFont font( "Arial", 10, QFont::Normal);
    m_ui->Status->setFont(font);

   if(comm.connect_result)
   {
       m_ui->Status->setText("Connection Established!");
       m_ui->Status->show();
   }

    QPalette _palette;
    _palette.setColor(QPalette::Window, Qt::gray);
    _palette.setColor(QPalette::WindowText, Qt::white);

    m_ui->Status->setAutoFillBackground(true);
    m_ui->Status->setPalette(_palette);

}

void MainWindow::on_btn_stopComm_clicked()
{

      timer.stop();
      reset_widgets();

      mThread->terminate();
      mUpdateGUIthread->terminate();

      comm.disconnectFromPort();

}

void MainWindow::on_HILS_Start_Stop_clicked()
{

    if(m_ui->HILS_Start_Stop->text() == "HILS Start")
    {
        QString fileName = "C:/Users/CommHub/Documents/AvDIPublisher/AvDIPublisher/AvDIPublisher.bat";

        QDesktopServices::openUrl(QUrl(fileName,QUrl::TolerantMode));

        m_ui->HILS_Start_Stop->setEnabled(false);
    }

}


void MainWindow::on_Reset_DDS_Domain_clicked()
{
    QString fileName = "C:/Users/CommHub/Documents/AvDIPublisher/AvDIPublisher/Stop FDMPublisher.bat";

    QDesktopServices::openUrl(QUrl("file:///"+fileName,QUrl::TolerantMode));
}
