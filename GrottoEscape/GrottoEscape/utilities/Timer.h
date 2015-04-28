#pragma once

namespace Utils
{
	class Timer {
	    typedef  void (*TFunc)(void*);
	public:	
		Timer(TFunc func, void* data) : mRunning(false) , mData(data), mCount(0){
			mCallback = func;
		}
		
		void start(size_t timeout) {
			mRunning = true;
			mTimeout = timeout;
		}

		void restart() {
			mTimeout = 0;
		}

		void stop() {
			mRunning = false;
			mTimeout = 0;
		}

		void tik() {
			if(mRunning) {
				if(mTimeout <= mCount) {
					mCallback(mData);
					mCount = 0;
				}
				mCount  += 17;
			}
		}

	private:
		size_t mTimeout;
		size_t mCount;
		TFunc mCallback;
		bool mRunning;
		void* mData;
	};
}

