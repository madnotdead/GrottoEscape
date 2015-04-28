//////////////////////////////////////////////////////////////////////////
//
//  Name:   FPSCalculator.h
//
//  Desc:   Class that computes frames per second.
//
//  Author: Nicolas Bertoa - nicobertoa@gmail.com
//
//////////////////////////////////////////////////////////////////////////

#ifndef UTILS_FPS_H
#define UTILS_FPS_H

#include <ctime>

#include "Types.h"

namespace Utils
{
    class FPSCalculator
    {
    public:
        FPSCalculator();

        inline void Update();

        inline uint16_t GetFPS() const;

    private:
        static const float sOneSecond; // One second in milliseconds.

        clock_t mStartFrameTime; // Start frame time in milliseconds.

        uint16_t mElapsedFrames; // Current frame.

        uint16_t mFramesPerSecond; // Current fps.
    };
      
    void FPSCalculator::Update()
    {
        // If one second passed, then we update
        // the frames in the last second.
		const clock_t elapsedTime = clock() - mStartFrameTime;
		if(sOneSecond <= elapsedTime)
		{
			// Update fps
			mFramesPerSecond = mElapsedFrames;

			// Reset the current frame and clock.
			mElapsedFrames = 0;
			mStartFrameTime = clock();
        }

        else
			++mElapsedFrames;
	}

    uint16_t FPSCalculator::GetFPS() const 
	{ 
		return mFramesPerSecond; 
	}
}

#endif // UTILS_FPS_H
