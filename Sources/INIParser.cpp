#include "INIParser.hpp"

namespace CUtils
{
    INIParser::INIParser(const std::string& filename) : filename_(filename) {}

    bool INIParser::Load() 
    {
        std::ifstream file(filename_);
        if (!file.is_open()) 
        {
            return false;
        }

        std::string line, currentSection;
        while (std::getline(file, line)) 
        {
            Trim(line);
            if (line.empty() || line[0] == ';') continue; 

            if (line[0] == '[') 
            {
                size_t end = line.find(']');
                if (end != std::string::npos) 
                {
                    currentSection = line.substr(1, end - 1);
                    Trim(currentSection);
                }
            }

            else 
            {
                size_t equalSign = line.find('=');
                if (equalSign != std::string::npos && !currentSection.empty()) 
                {
                    std::string key = line.substr(0, equalSign);
                    std::string value = line.substr(equalSign + 1);
                    Trim(key);
                    Trim(value);
                    data_[currentSection][key] = value;
                }
            }
        }
        return true;
    }

    bool INIParser::Save() const 
    {
        std::ofstream file(filename_);
        if (!file.is_open()) 
        {
            return false;
        }

        for (const auto& section : data_) 
        {
            file << "[" << section.first << "]\n";
            for (const auto& keyValue : section.second) 
            {
                file << keyValue.first << "=" << keyValue.second << "\n";
            }
        }
        return true;
    }

    std::string INIParser::GetValue(const std::string& section, const std::string& key) const 
    {
        auto secIt = data_.find(section);
        if (secIt != data_.end()) 
        {
            auto keyIt = secIt->second.find(key);
            if (keyIt != secIt->second.end()) 
            {
                return keyIt->second;
            }
        }
        return "";
    }

    void INIParser::SetValue(const std::string& section, const std::string& key, const std::string& value) 
    {
        data_[section][key] = value;
    }

    std::vector<std::string> INIParser::GetSections() const 
    {
        std::vector<std::string> sections;
        for (const auto& section : data_) 
        {
            sections.push_back(section.first);
        }

        return sections;
    }

    std::map<std::string, std::string> INIParser::GetKeys(const std::string& section) const 
    {
        auto secIt = data_.find(section);
        if (secIt != data_.end()) {
            return secIt->second;
        }
        return {};
    }

    void INIParser::Trim(std::string& str) const 
    {
        size_t first = str.find_first_not_of(' ');
        size_t last = str.find_last_not_of(' ');
        str = (first == std::string::npos) ? "" : str.substr(first, last - first + 1);
    }
}