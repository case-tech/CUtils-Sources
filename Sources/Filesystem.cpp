#include "Filesystem.hpp"

namespace CUtils
{
    bool Filesystem::CreateDirectory(const std::string& path) 
    {
        return std::filesystem::create_directory(path);
    }

    bool Filesystem::Remove(const std::string& path) 
    {
        return std::filesystem::remove(path);
    }

    bool Filesystem::Rename(const std::string& oldPath, const std::string& newPath) 
    {
        try 
        {
            std::filesystem::rename(oldPath, newPath);
            return true;
        }

        catch (const std::filesystem::filesystem_error& e) 
        {
            return false;
        }
    }

    bool Filesystem::Exists(const std::string& path) const 
    {
        return std::filesystem::exists(path);
    }

    std::vector<std::string> Filesystem::ListDirectory(const std::string& path) const 
    {
        std::vector<std::string> entries;
        if (!IsDirectory(path)) 
        {
            return entries;
        }

        for (const auto& entry : std::filesystem::directory_iterator(path)) 
        {
            entries.push_back(entry.path().string());
        }
        return entries;
    }

    std::string Filesystem::GetAbsolutePath(const std::string& path) const 
    {
        return std::filesystem::absolute(path).string();
    }

    bool Filesystem::IsDirectory(const std::string& path) const 
    {
        return std::filesystem::is_directory(path);
    }

    bool Filesystem::IsFile(const std::string& path) const 
    {
        return std::filesystem::is_regular_file(path);
    }

    uintmax_t Filesystem::FileSize(const std::string& path) const 
    {
        if (!IsFile(path)) 
        {
            throw std::runtime_error("Path is not a file: " + path);
        }

        return std::filesystem::file_size(path);
    }

    bool Filesystem::Copy(const std::string& from, const std::string& to, bool recursive) 
    {
        try 
        {
            if (recursive && IsDirectory(from)) 
            {
                CopyDirectoryRecursive(from, to);
            }
            else {
                std::filesystem::copy(from, to);
            }
            return true;
        }

        catch (const std::filesystem::filesystem_error& e)
        {
            return false;
        }
    }

    void Filesystem::CopyDirectoryRecursive(const std::filesystem::path& from, 
                                            const std::filesystem::path& to)
    {
        std::filesystem::create_directories(to);
        for (const auto& entry : std::filesystem::directory_iterator(from)) 
        {
            const auto& newFrom = entry.path();
            const auto& newTo = to / entry.path().filename();
            if (std::filesystem::is_directory(newFrom)) 
            {
                CopyDirectoryRecursive(newFrom, newTo);
            }

            else 
            {
                std::filesystem::copy(newFrom, newTo);
            }
        }
    }
}
