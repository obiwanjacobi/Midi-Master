#ifndef __LOCKSCOPE_H__
#define __LOCKSCOPE_H__

#include "avr/common.h"

namespace ATL {

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
		__asm__ volatile ("cli" ::: "memory");
	}
	
	inline void Exit()
	{
		SREG = _sreg;
		__asm__ volatile ("" ::: "memory");
	}
		
private:
	uint8_t _sreg;
};

} // ATL

#endif /* __LOCKSCOPE_H__ */