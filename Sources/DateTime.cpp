#include "DateTime.hpp"

namespace CUtils
{
    DateTime::DateTime() 
    {
        currentTime_ = std::time(nullptr);
    }

    DateTime::DateTime(time_t time) : currentTime_(time) 
    {

    }

    std::string DateTime::GetCurrentDateTime() const 
    {
        return Format("%Y-%m-%d %H:%M:%S");
    }

    std::string DateTime::GetCurrentDate() const 
    {
        return Format("%Y-%m-%d");
    }

    std::string DateTime::GetCurrentTime() const 
    {
        return Format("%H:%M:%S");
    }

    void DateTime::SetTime(time_t time) 
    {
        currentTime_ = time;
    }

    time_t DateTime::GetTime() const 
    {
        return currentTime_;
    }

    std::string DateTime::Format(const std::string& format) const 
    {
        std::tm timeinfo = {};
        localtime_s(&timeinfo, &currentTime_); 

        char buffer[80];
        std::strftime(buffer, sizeof(buffer), format.c_str(), &timeinfo);

        return std::string(buffer);
    }

    bool DateTime::operator==(const DateTime& other) const 
    {
        return currentTime_ == other.currentTime_;
    }

    bool DateTime::operator!=(const DateTime& other) const 
    {
        return currentTime_ != other.currentTime_;
    }

    bool DateTime::operator<(const DateTime& other) const 
    {
        return currentTime_ < other.currentTime_;
    }

    bool DateTime::operator>(const DateTime& other) const 
    {
        return currentTime_ > other.currentTime_;
    }

    bool DateTime::operator<=(const DateTime& other) const 
    {
        return currentTime_ <= other.currentTime_;
    }

    bool DateTime::operator>=(const DateTime& other) const 
    {
        return currentTime_ >= other.currentTime_;
    }
}