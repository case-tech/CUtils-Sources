#include "Notification.hpp"

namespace CUtils
{
    void SetConsoleColor(int color)  
    {
        #ifdef _WIN32 || _WIN64
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, color);
        #else
            std::cout << "\033[" << color << "m";
        #endif
    }

    void ResetConsoleColor() 
    {
        #ifdef _WIN32 || _WIN64
            SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        #else
            std::cout << "\033[0m"; 
        #endif
    }

    void Notification::notify(NotificationType type, const std::string& message) 
    {
        switch (type) 
        {
        case TYPE_ERROR:
       
            #ifdef _WIN32 || _WIN64
                SetConsoleColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
            #else
                setConsoleColor(31); 
            #endif
                std::cout << "ERROR: " << message << std::endl;
                break;

        case TYPE_WARNING:
            #ifdef _WIN32 || _WIN64
                SetConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            #else
                setConsoleColor(33); 
            #endif
                std::cout << "WARNING: " << message << std::endl;
                break;

        case TYPE_INFO:
            #ifdef _WIN32 || _WIN64
                SetConsoleColor(FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
            #else
                setConsoleColor(0);
            #endif
                std::cout << "INFO: " << message << std::endl;
                break;

        default:
            std::cerr << "Unknown notification type!" << std::endl;
            break;
        }
        ResetConsoleColor(); 
    }
}