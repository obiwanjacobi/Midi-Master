//#include "Registers.h"
class Registers;

// default mcu
//#define __AVR_ATmega328P__	// Arduino UNO
#define __AVR_ATmega1284__

#ifndef F_CPU
// assume 1MHz
#define F_CPU 1000000UL
#endif

// imitate DoxyGen to get compatible definitions.
#define __DOXYGEN__
#define __extension__

#ifdef __ATTR_PURE__
#undef __ATTR_PURE__
#endif
#define __ATTR_PURE__

#ifdef __ATTR_CONST__
#undef __ATTR_CONST__
#endif
#define __ATTR_CONST__

#define __ATTR_PROGMEM__



// fake delays
#define _UTIL_DELAY_H_
#define _delay_ms(p) /* p */
#define _delay_us(p) /* p */

// take out original stddef.h header file
#define _STDDEF_H
#define NULL ((void *)0)

// take out original sfr_defs.h header file
#define _AVR_SFR_DEFS_H_

#ifndef __SFR_OFFSET
#  if __AVR_ARCH__ >= 100
#    define __SFR_OFFSET 0x00
#  else
#    define __SFR_OFFSET 0x20
#  endif
#endif

#define _SFR_MEM16(memaddr) Registers::At16(memaddr)
#define _SFR_MEM8(memaddr) Registers::At8(memaddr)
#define _SFR_IO8(memaddr) Registers::At8((memaddr) + __SFR_OFFSET)



// ATL overrides
#define ASM_VOLATILE(s)		// __asm__ volatile (##s);
