#ifndef __DATATYPES_H__
#define __DATATYPES_H__

#include "Constants.h"
#include "ATL/AVR/Usart.h"
#include "ATL/AVR/UsartRegisters.h"
#include "ATL/AVR/UsartTransmit.h"
#include "ATL/AVR/UsartOutputStream.h"
#include "ATL/AVR/UsartReceive.h"
#include "ATL/AVR/UsartInputStream.h"
#include "ATL/MidiReader.h"
#include "ATL/MidiWriter.h"
#include "ATL/Collection.h"
#include "ATL/FixedString.h"
#include "ATL/AVR/Delay_Avr.h"
#include "ATL/AVR/DigitalOutputPin.h"
#include "ATL/AVR/Port.h"
#include "ATL/HD44780_Driver.h"
#include "ATL/HD44780_DisplayWriter.h"
#include "ATL/HD44780_Controller.h"
#include "ATL/HD44780_View.h"
#include "ATL/RingBufferFast.h"
#include "ATL/StringStream.h"
#include "ATL/TextWriter.h"
#include "ATL/Time.h"
#include "ATL/Delays.h"
#include "ATL/AVR/TimerCounter.h"
#include "MidiMessageHandler.h"
#include "DummyDigitalPin.h"


using namespace ATL;
using namespace ATL::MCU;

typedef Delays<Time<TimeResolution::Milliseconds>, 8> TaskScheduler;

template<const UsartIds::type UsartId>
class MidiOutPort : public MidiWriter<UsartOutputStream<UsartTransmit<UsartId>, RingBufferFast<uint8_t, MidiTransmitBufferSize> > >
{ };

template<typename StateT>
class MidiInOutPort1T : public Usart<UsartIds::UsartId0, MidiOutPort<UsartIds::UsartId0>, MidiReader<MidiMessageHandler<StateT> > >
{ };

typedef Usart<UsartIds::UsartId1, MidiOutPort<UsartIds::UsartId1> > MidiOutPort2T;

typedef HD44780_DisplayWriter<
            TextWriter< 
			    HD44780_View<
				    HD44780_Controller<
					    HD44780_Driver<
						    DigitalOutputPin<PortC, Pin2>,
						    DigitalOutputPin<PortC, Pin3>,
						    DigitalOutputPin<PortC, Pin4>,
						    DigitalOutputPin<PortC, Pin5>,
						    DigitalOutputPin<PortC, Pin6>,
						    DigitalOutputPin<PortC, Pin7>
					    >
				    >, LcdLines, LcdColumns
			    >
		    > 
        > LCD;

template <const uint8_t MaxSize>
class StringWriter : public TextWriter<StringStream<Collection<FixedString<MaxSize> > > >
{ };

#endif //__DATATYPES_H__