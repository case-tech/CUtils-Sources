#include "SystemConfiguration.hpp"

namespace CUtils
{
    #ifdef _WIN32 || _WIN64
        #include <windows.h>

        typedef LONG NTSTATUS;
        typedef NTSTATUS(WINAPI* RtlGetVersionPtr)(PRTL_OSVERSIONINFOW);

        std::string SystemConfiguration::GetOSVersion() 
        {
            HMODULE hMod = LoadLibraryW(L"ntdll.dll");
            if (hMod) 
            {
                RtlGetVersionPtr pRtlGetVersion = 
                    (RtlGetVersionPtr)GetProcAddress(hMod, "RtlGetVersion");

                if (pRtlGetVersion != nullptr) 
                {
                    RTL_OSVERSIONINFOW osvi = { 0 };
                    osvi.dwOSVersionInfoSize = sizeof(osvi);

                    if (pRtlGetVersion(&osvi) == (NTSTATUS)0x00000000L) 
                    {
                        std::ostringstream osVersion;
                        osVersion << osvi.dwMajorVersion << "." << 
                            osvi.dwMinorVersion << " (Build " << osvi.dwBuildNumber << ")";
                        FreeLibrary(hMod);
                        return osVersion.str();
                    }
                }

                FreeLibrary(hMod);
            }
            return "Unknown Version";
        }
    #else
        #include <sys/utsname.h>
        #include <unistd.h>
        #include <fstream>
    #endif

    std::string SystemConfiguration::GetOSName() 
    {
        #ifdef _WIN32 || _WIN64
            return "Windows";
        #elif __APPLE__
            return "macOS";
        #elif __linux__
            return "Linux";
        #else
            return "Unknown OS";
        #endif
    }

    std::string SystemConfiguration::GetCPUInfo() 
    {
        #ifdef _WIN32 || _WIN64
            SYSTEM_INFO sysInfo;
            GetSystemInfo(&sysInfo);
            std::ostringstream cpuInfo;
            cpuInfo << "CPU Architecture: ";

            switch (sysInfo.wProcessorArchitecture) 
            {
            case PROCESSOR_ARCHITECTURE_AMD64:
                cpuInfo << "x64 (AMD or Intel)";
                break;
            case PROCESSOR_ARCHITECTURE_ARM:
                cpuInfo << "ARM";
                break;
            case PROCESSOR_ARCHITECTURE_INTEL:
                cpuInfo << "x86";
                break;
            default:
                cpuInfo << "Unknown";
            }

            return cpuInfo.str();

        #elif __APPLE__
            return execCommand("sysctl -n machdep.cpu.brand_string");

        #elif __linux__
            std::ifstream cpuinfo("/proc/cpuinfo");
            std::string line;
            while (std::getline(cpuinfo, line)) 
            {
                if (line.find("model name") != std::string::npos) 
                {
                    return line.substr(line.find(":") + 2);
                }
            }
            return "Unknown CPU";
        #endif
    }

    std::string SystemConfiguration::GetMemoryInfo() 
    {
        #ifdef _WIN32 || _WIN64
            MEMORYSTATUSEX statex;
            statex.dwLength = sizeof(statex);
            GlobalMemoryStatusEx(&statex);
            std::ostringstream memInfo;
            memInfo << "Total Physical Memory: " << 
                (statex.ullTotalPhys / (1024 * 1024)) << " MB";
            return memInfo.str();

        #elif __APPLE__
            return execCommand("sysctl -n hw.memsize");

        #elif __linux__
            std::ifstream meminfo("/proc/meminfo");
            std::string line;
            while (std::getline(meminfo, line)) 
            {
                if (line.find("MemTotal") != std::string::npos) 
                {
                    return line.substr(line.find(":") + 1);
                }
            }
            return "Unknown Memory";
        #endif
    }

    std::string SystemConfiguration::GetDiskInfo() 
    {
        #ifdef _WIN32 || _WIN64
            ULARGE_INTEGER freeBytesAvailable, totalNumberOfBytes;
            GetDiskFreeSpaceExW(L"C:\\", &freeBytesAvailable, &totalNumberOfBytes, NULL);
            std::ostringstream diskInfo;
            diskInfo << "Total Disk Space: " << 
                (totalNumberOfBytes.QuadPart / (1024 * 1024 * 1024)) << " GB";
            return diskInfo.str();

        #elif __APPLE__
            return execCommand("df -h / | awk 'NR==2 {print $2}'");

        #elif __linux__
            return execCommand("df -h --total | grep 'total' | awk '{print $2}'");
        #endif
    }

    #ifdef _WIN32 || _WIN64
    std::string SystemConfiguration::execCommand(const std::string& command) 
    {
        return "Command execution not implemented on Windows.";
    }

    #else
    std::string SystemConfiguration::execCommand(const char* command) 
    {
        std::array<char, 128> buffer;
        std::string result;
        std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command, "r"), pclose);
        if (!pipe) 
        {
            throw std::runtime_error("popen() failed!");
        }
        while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) 
        {
            result += buffer.data();
        }
        return result;
    }
    #endif
}