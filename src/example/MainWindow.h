/***************************************************************************//**
 * @file example/MainWindow.h
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
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

////////////////////////////////////////////////////////////////////////////////

#include <QMainWindow>
#include <QTime>
#include <my_parameters.h>
#include <thread.h>
#include <thread_recievepacket.h>
#include <thread_updategui.h>
#include <QtCore>
#include <QtCore>
#include <communication.h>
#include <QMetaObject>

#include <QtCharts/QChartView>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QChartGlobal>
#include <QDateTimeAxis>
#include <QValueAxis>
////////////////////////////////////////////////////////////////////////////////

namespace Ui
{
    class MainWindow;
}


QT_CHARTS_BEGIN_NAMESPACE

class QChartView;
class QChart;

QT_CHARTS_END_NAMESPACE


QT_CHARTS_USE_NAMESPACE

////////////////////////////////////////////////////////////////////////////////

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:

    explicit MainWindow( QWidget *parent = 0 );
    ~MainWindow();

    Thread *mThread;
    Thread_RecievePacket *mRecievePacketThread;
    Thread_updateGUI *mUpdateGUIthread;
    int port=0;
    QByteArray m_datagram = NULL;

protected:

public slots:

    void on_btn_startComm_clicked();
    //Q_INVOKABLE void updateListbox();

    Q_INVOKABLE void updateWidgets();

    Q_INVOKABLE void Make_SplineChart();

    
private slots:

    void on_btn_connect_clicked();

    void on_btn_stopComm_clicked();

    void bitShifting(QByteArray array);

    void recieve_udpPacket();

    void updateGUI();

    void gettingParameters();

    void settingParameters();

    void reset_widgets();
    void closeEvent(QCloseEvent *eve);

    void on_HILS_Start_Stop_clicked();

    void on_Reset_DDS_Domain_clicked();

    QChart *createSpLineChart();

    void update_S_Chart();



private:

    Ui::MainWindow *m_ui;

    int m_timerId;
    int m_steps;

    float m_realTime;

    int nMilliseconds;

    QTime m_time;
    Communication comm;
    My_Parameters parameters;

    QList<int> temp_list;
    QString temp_string;

    unsigned short Heading;
    signed short Pitch;
    signed short Roll;
    unsigned short Airspeed;
    unsigned short Altitude;
    signed  int Vertical_Speed;
    signed short SlipSkid;
    signed short TurnRate;
    unsigned short Pressure;


    QChartView *chartview;

    QDateTimeAxis *dateTimeAxis;
    QChart *chart = new QChart();

    QValueAxis *axis_X;
    QValueAxis *axis_Y;

    QSplineSeries *series;
    QTimer timer;
    qreal m_x = 0.0;
    qreal m_y;
    qreal x;

};

////////////////////////////////////////////////////////////////////////////////

#endif // MAINWINDOW_H
