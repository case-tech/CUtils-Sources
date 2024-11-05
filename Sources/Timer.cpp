#include "Timer.hpp"

namespace CUtils
{
    Timer::Timer() : isRunning_(false) {}
   
    void Timer::Start() 
    {
        startTime_ = std::chrono::high_resolution_clock::now();
        isRunning_ = true;
    }

    void Timer::Stop() 
    {
        if (isRunning_) 
        {
            endTime_ = std::chrono::high_resolution_clock::now();
            isRunning_ = false;
        }
    }

    void Timer::Reset() 
    {
        isRunning_ = false;
    }

    double Timer::Elapsed() const 
    {
        auto end = isRunning_ ? std::chrono::high_resolution_clock::now() : endTime_;
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - startTime_);
        return duration.count() / 1e6; 
    }

    void Timer::PrintElapsed() const 
    {
        std::cout << "Elapsed time: " << Elapsed() << " seconds\n";
    }
}