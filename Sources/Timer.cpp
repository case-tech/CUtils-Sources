#include "Timer.hpp"

namespace CUtils
{
	Timer::Timer()
	{
		start_ = std::chrono::high_resolution_clock::now();
		stop_  = std::chrono::high_resolution_clock::now();
	}

	double Timer::GetMilisecondsElapsed()
	{
		if (isRunning_)
		{
			auto elapsed = std::chrono::duration<double, std::milli>(std::chrono::high_resolution_clock::now() - start_);
			return elapsed.count();
		}
		else
		{
			auto elapsed = std::chrono::duration<double, std::milli>(stop_ - start_);
			return elapsed.count();
		}
	}

	void Timer::Restart()
	{
		isRunning_ = true;
		start_ = std::chrono::high_resolution_clock::now();
	}

	bool Timer::Stop()
	{
		if (!isRunning_)
			return false;
		else
		{
			stop_ = std::chrono::high_resolution_clock::now();
			isRunning_ = false;
			return true;
		}
	}

	bool Timer::Start()
	{
		if (isRunning_)
		{
			return false;
		}
		else
		{
			start_ = std::chrono::high_resolution_clock::now();
			isRunning_ = true;
			return true;
		}
	}
}