//////////////////////////////////////////////////////////////////////////
//
//  Name:   FPSCalculator.cpp
//
//  Desc:   Class that computes frames per second.
//
//  Author: Nicolas Bertoa - nicobertoa@gmail.com
//
//////////////////////////////////////////////////////////////////////////

#include "FPSCalculator.h"

namespace Utils
{
	const float FPSCalculator::sOneSecond = 1000.0f;
	
	FPSCalculator::FPSCalculator()
		: mStartFrameTime(clock())
		, mElapsedFrames(0)
		, mFramesPerSecond(0)
    {
    }
}
