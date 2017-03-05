#ifndef __TESTRESULT__
#define __TESTRESULT__

#include "ATL/EnumScope.h"

BeginEnum(MessageTestResult)
{
	// no result, the detection is not active
	None,
	// the midi message is blocked and should not be processed or sent to the output.
	Blocked,
	// the midi message passed the test and should be processed further.
	Passed,
	// the midi message did not pass but should be sent to the output directly.
	Through,
}
EndEnum(MessageTestResult)

#endif //__TESTRESULT__