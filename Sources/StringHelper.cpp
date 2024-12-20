#include "StringHelper.hpp"

namespace CUtils
{
   StringHelper::StringHelper(const std::string& str) : data(str) 
   {

   }

   StringHelper::StringHelper(const char* str) : data(str) 
   {
		
   }

   std::string StringHelper::ToLowerCase() const 
   {
      std::string result = data;
      std::transform(result.begin(), result.end(), result.begin(), ::tolower);
      return result;
   }

   std::string StringHelper::ToUpperCase() const 
   {
      std::string result = data;
      std::transform(result.begin(), result.end(), result.begin(), ::toupper);
      return result;
   }

   std::string StringHelper::Trim() const 
   {
      std::string result = data;
      result.erase(result.begin(), std::find_if(result.begin(), result.end(), [](unsigned char ch) 
      {
         return !std::isspace(ch);
      }));

      result.erase(std::find_if(result.rbegin(), result.rend(), [](unsigned char ch)
      {
         return !std::isspace(ch);
      }).base(), result.end());

      return result;
   }

   std::vector<std::string> StringHelper::Split(char delimiter) const 
   {
      std::vector<std::string> tokens;
      std::string token;
      for (char ch : data) 
      {
        if (ch == delimiter) 
	{
            if (!token.empty()) 
	    {
                tokens.push_back(token);
                token.clear();
            }
        }

        else 
	{
            token += ch;
        }
      }

      if (!token.empty()) 
      {
        tokens.push_back(token);
      }

      return tokens;
   }

   bool StringHelper::Contains(const std::string& substr) const 
   {
      return data.find(substr) != std::string::npos;
   }

   bool StringHelper::StartsWith(const std::string& prefix) const 
   {
      return data.compare(0, prefix.length(), prefix) == 0;
   }

   bool StringHelper::EndsWith(const std::string& suffix) const 
   {
      if (suffix.length() > data.length()) return false;
      return data.compare(data.length() - suffix.length(), suffix.length(), suffix) == 0;
   }

   std::string StringHelper::Replace(const std::string& oldStr, const std::string& newStr) const
   {
      std::string result = data;
      size_t pos = 0;
      while ((pos = result.find(oldStr, pos)) != std::string::npos) 
      {
         result.replace(pos, oldStr.length(), newStr);
         pos += newStr.length();
      }
      return result;
   } 

   int StringHelper::IndexOf(const std::string& substr) const 
   {
      size_t pos = data.find(substr);
      return pos == std::string::npos ? -1 : static_cast<int>(pos);
   }

   int StringHelper::LastIndexOf(const std::string& substr) const 
   {
      size_t pos = data.rfind(substr);
      return pos == std::string::npos ? -1 : static_cast<int>(pos);
   }

   std::string StringHelper::Substring(size_t start, size_t length) const 
   {
      if (start >= data.length()) 
      {
          throw std::out_of_range("Start index out of range");
      }

      return data.substr(start, length);
   }

   std::string StringHelper::ExtractNumericPart() const 
   {
      std::string result;
      bool foundDecimal = false; 

      for (char ch : data) 
      {
        if (std::isdigit(ch)) 
	{
            result += ch;
        }

        else if (ch == '.' && !foundDecimal) 
	{
            result += ch; 
            foundDecimal = true;
        }
      }

      return result;
   }

   bool StringHelper::IsEmpty() const 
   {
      return data.empty();
   }

   size_t StringHelper::Length() const 
   {
      return data.length();
   }

   StringHelper& StringHelper::operator=(const std::string& str) 
   {
      data = str;
      return *this;
   }

   StringHelper& StringHelper::operator=(const char* str) 
   {
      data = str;
      return *this;
   }

   bool StringHelper::operator==(const StringHelper& other) const 
   {
      return data == other.data;
   }

   bool StringHelper::operator!=(const StringHelper& other) const 
   {
      return data != other.data;
   }

   StringHelper::operator std::string() const 
   {
      return data;
   }

   std::optional<int> StringHelper::ToInt() const 
   {
      try 
      {
        size_t pos;
        int result = std::stoi(data, &pos); 
        if (pos != data.length()) 
	{
            return std::nullopt;
        }

        return result;
      }

      catch (const std::invalid_argument&) 
      {
        return std::nullopt;
      }

      catch (const std::out_of_range&) 
      {
        return std::nullopt;
      }
   }

   std::optional<double> StringHelper::ToDouble() const 
   {
      try 
      {
        size_t pos;
        double result = std::stod(data, &pos); 
        if (pos != data.length()) 
	{
            return std::nullopt;
        }

        return result;
      }

      catch (const std::invalid_argument&) 
      {
        return std::nullopt;
      }

      catch (const std::out_of_range&) 
      {
        return std::nullopt;
      }
   }

   std::optional<bool> StringHelper::ToBool() const 
   {
      std::string lowerStr = ToLowerCase(); 

      if (lowerStr == "true" || lowerStr == "1") 
      {
          return true;
      }
      else if (lowerStr == "false" || lowerStr == "0") 
      {
          return false;
      }
      else
      {
          return std::nullopt;
      }
   }
}
