#ifndef __TESTRESULT__
#define __TESTRESULT__

#include "ATL/EnumScope.h"

BeginEnum(MessageMatchResult)
{
	// no result, the detection is not active
	None,
	// the midi message is blocked and should not be processed or sent to the output.
	Blocked,
	// the midi message matched and should be processed further.
	Passed,
	// the midi message did not match but should be sent to the output directly.
	Through,
}
EndEnum(MessageMatchResult)

#endif //__TESTRESULT__