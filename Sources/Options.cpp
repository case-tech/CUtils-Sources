#include "Options.hpp"

namespace CUtils
{
    Options::Options(int argc, char* argv[]) 
    {
        for (int i = 0; i < argc; ++i) 
        {
            args_.emplace_back(argv[i]);
        }
    }

    void Options::AddOption(const std::string& option, const std::string& description) 
    {
        options_[option] = description;
    }

    bool Options::IsOptionSet(const std::string& option) const 
    {
        return std::find(args_.begin(), args_.end(), option) != args_.end();
    }

    std::string Options::GetOptionValue(const std::string& option) const 
    {
        auto it = std::find(args_.begin(), args_.end(), option);
        if (it != args_.end() && ++it != args_.end()) 
        {
            return *it; 
        }

        return ""; 
    }

    void Options::PrintHelp() const 
    {
        std::cout << "Available options:\n";
        for (const auto& opt : options_) 
        {
            std::cout << "  " << opt.first << ": " << opt.second << "\n";
        }
    }
}