#pragma once
#include <vector>
#include "Timer.h"
#include <algorithm>

namespace Utils
{

class TimerManager {
public:
	void registerTimer(Timer& timer) {
		mTimers.push_back(&timer);
	}

	void unregisterTimer(Timer& timer) {
		mTimers.erase(std::find(mTimers.begin(), mTimers.end(), &timer));
	}

	void tik() {
		for(size_t i = 0; i < mTimers.size(); ++i ) {
			mTimers[i]->tik();
		}
	}

private:
	std::vector<Timer*> mTimers;

};

}