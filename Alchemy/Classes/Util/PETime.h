#ifndef Alchemy_Time
#define Alchemy_Time

#include "Common.h"

class PETime {
	public:
		PETime();
		~PETime();
		
		static void init();
		static int GetTime();
		static void StopTime();
		static void StartTime();
		static int GetCurrentTimeInMilli();

	private:
		static int time;
		static int stopTime;
		static int st_StopTime;
		static int ed_StopTime;
		static int realTime;
};

#endif /* defined(Alchemy_Time) */