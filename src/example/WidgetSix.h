/***************************************************************************//**
 * @file example/WidgetSix.h
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
#ifndef WIDGETSIX_H
#define WIDGETSIX_H

////////////////////////////////////////////////////////////////////////////////

#include <QWidget>

#include "WidgetADI.h"
#include "WidgetALT.h"
#include "WidgetASI.h"
#include "WidgetHSI.h"
#include "WidgetTC.h"
#include "WidgetVSI.h"
#include "WidgetNAV.h"
#include "WidgetPFD.h"
////////////////////////////////////////////////////////////////////////////////

namespace Ui
{
    class WidgetSix;
}

////////////////////////////////////////////////////////////////////////////////

class WidgetSix : public QWidget
{
    Q_OBJECT

public:

    explicit WidgetSix( QWidget *parent = 0 );

    ~WidgetSix();

    void update();

    inline void setRoll( float roll )
    {
        m_widgetADI->setRoll( roll );
    }

    inline void setPitch( float pitch )
    {
        m_widgetADI->setPitch( pitch );
    }

    inline void setAltitude( float altitude )
    {
        m_widgetALT->setAltitude( altitude );
    }

    inline void setPressure( float pressure )
    {
        m_widgetALT->setPressure( pressure );
    }

    inline void setAirspeed( float airspeed )
    {
        m_widgetASI->setAirspeed( airspeed );
    }

    inline void setHeading( float heading )
    {
        m_widgetHSI->setHeading( heading );
    }

    inline void setTurnRate( float turnRate )
    {
        m_widgetTC->setTurnRate( turnRate );
    }

    inline void setSlipSkid( float slipSkid )
    {
        m_widgetTC->setSlipSkid( slipSkid );
    }

    inline void setClimbRate( float climbRate )
    {
        m_widgetVSI->setClimbRate( climbRate );
    }

    inline void setwidNAV(float heading, float adf, float devH, float dme){
        m_widgetNAV->setHeading( heading);
        m_widgetNAV->setHeadingBug ( 0.0f );
        m_widgetNAV->setCourse     ( 0.0f );
        m_widgetNAV->setBearing    ( adf  , true );
        m_widgetNAV->setDeviation  ( devH , true );
        m_widgetNAV->setDistance   ( dme  , true );
    }

    inline void setwidPFD(float alpha,float beta,float roll,float pitch, float slipSkid,float turnRate,float devH,float devV,float heading,float airspeed,float machNo,float altitude,float pressure,float climbRate){
        m_widgetPFD->setFlightPathMarker ( alpha, beta );
        m_widgetPFD->setRoll          ( roll     );
        m_widgetPFD->setPitch         ( pitch     );
        m_widgetPFD->setSlipSkid      ( slipSkid  );
        m_widgetPFD->setTurnRate      ( turnRate / 6.0f );
        m_widgetPFD->setDevH          ( devH      );
        m_widgetPFD->setDevV          ( devV      );
        m_widgetPFD->setHeading       ( heading   );
        m_widgetPFD->setAirspeed      ( airspeed  );
        m_widgetPFD->setMachNo        ( machNo    );
        m_widgetPFD->setAltitude      ( altitude  );
        m_widgetPFD->setPressure      ( pressure  );
        m_widgetPFD->setClimbRate     ( climbRate / 100.0f );
    }
private:

    Ui::WidgetSix *m_ui;

    WidgetADI *m_widgetADI;
    WidgetALT *m_widgetALT;
    WidgetASI *m_widgetASI;
    WidgetHSI *m_widgetHSI;
    WidgetTC  *m_widgetTC;
    WidgetVSI *m_widgetVSI;
    WidgetNAV *m_widgetNAV;
    WidgetPFD *m_widgetPFD;
};

////////////////////////////////////////////////////////////////////////////////

#endif // WIDGETSIX_H
