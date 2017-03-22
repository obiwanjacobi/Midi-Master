#ifndef __LOCKSCOPE_H__
#define __LOCKSCOPE_H__

#include "avr/common.h"

namespace ATL {

// To be able to remove it for unit tests.
#ifndef ASM_VOLATILE
#define  ASM_VOLATILE(s)  __asm__ volatile (s)
#endif

class LockScope
{
public:
	inline LockScope()
	{
		Enter();
	}
	
	inline ~LockScope()
	{
		Exit();
	}
	
	inline void Enter()
	{
		_sreg = SREG;
		ASM_VOLATILE("cli" ::: "memory");
	}
	
	inline void Exit()
	{
		SREG = _sreg;
		ASM_VOLATILE("" ::: "memory");
	}
		
private:
	uint8_t _sreg;
};

} // ATL

#endif /* __LOCKSCOPE_H__ */