#include "Encryption.hpp"

namespace CUtils
{
    Encryption::Encryption(Alg algorithm, const std::string& key) : algorithm(algorithm), key(key) 
    {
       if (algorithm == Alg::Vigenere && key.empty()) 
       {
          throw std::invalid_argument("Vigenere cipher requires a key");
       }

       if (algorithm == Alg::XOR && key.empty()) 
       {
          throw std::invalid_argument("XOR cipher requires a key");
       }
       
       if (algorithm == Alg::Transposition && key.empty()) 
       {
          throw std::invalid_argument("Transposition cipher requires a key");
       }
    }

    std::string Encryption::Encrypt(const std::string& plaintext) 
    {
       std::string result;
       switch (algorithm) 
       {
          case Alg::Caesar: 
          {
             int shift = 3;
             for (char c : plaintext) 
	     {
                if (isalpha(c)) 
		{
                    char base = islower(c) ? 'a' : 'A';
                    result += (c - base + shift) % 26 + base;
                }

		else 
		{
                    result += c;
                }
             }
             break;
          }

          case Alg::Vigenere: 
	  {
             for (size_t i = 0; i < plaintext.size(); ++i) 
	     {
                char c = plaintext[i];
                if (isalpha(c)) 
		{
                    char base = islower(c) ? 'a' : 'A';
                    char k = key[i % key.size()];
                    result += (c - base + (tolower(k) - 'a')) % 26 + base;
                }

		else 
		{
                    result += c;
                }
             }
             break;
          }

          case Alg::XOR: 
	  {
             for (size_t i = 0; i < plaintext.size(); ++i) 
	     {
                result += plaintext[i] ^ key[i % key.size()];
             }
             break;
          }

          case Alg::Substitution: 
	  {
            std::string substitution = "zyxwvutsrqponmlkjihgfedcba"; 
            for (char c : plaintext) 
	    {
                if (isalpha(c)) 
		{
                    char base = islower(c) ? 'a' : 'A';
                    result += substitution[(c - base)];
                }

		else 
		{
                    result += c;
                }
            }
            break;
          }

          case Alg::Transposition: 
	  {
            size_t keyLen = key.size();
            for (size_t i = 0; i < keyLen; ++i) 
	    {
                for (size_t j = i; j < plaintext.size(); j += keyLen) 
		{
                    result += plaintext[j];
                }
            }
            break;
          }

          default:
            throw std::invalid_argument("Unsupported encryption algorithm");
       }

       return result;
    }

    std::string Encryption::Decrypt(const std::string& ciphertext) 
    {
       std::string result;
       switch (algorithm) 
       {
          case Alg::Caesar: 
	  {
            int shift = 3; 
            for (char c : ciphertext) 
	    {
                if (isalpha(c)) 
		{
                    char base = islower(c) ? 'a' : 'A';
                    result += (c - base - shift + 26) % 26 + base;
                }

		else 
		{
                    result += c;
                }
            }
            break;
          }

          case Alg::Vigenere: 
	  {
            for (size_t i = 0; i < ciphertext.size(); ++i) 
	    {
                char c = ciphertext[i];
                if (isalpha(c)) 
		{
                    char base = islower(c) ? 'a' : 'A';
                    char k = key[i % key.size()];
                    result += (c - base - (tolower(k) - 'a') + 26) % 26 + base;
                } 

		else 
		{
                    result += c;
                }
            }
            break;
          }

          case Alg::XOR: 
	  {
            for (size_t i = 0; i < ciphertext.size(); ++i) 
	    {
                result += ciphertext[i] ^ key[i % key.size()];
            }
            break;
          }

          case Alg::Substitution: 
	  {
            std::string substitution = "zyxwvutsrqponmlkjihgfedcba"; 
            for (char c : ciphertext) 
	    {
                if (isalpha(c)) 
		{
                    char base = islower(c) ? 'a' : 'A';
                    result += (c - base + 26) % 26 + base;
                }

		else 
		{
                    result += c;
                }
             }

             break;
          }

          case Alg::Transposition: 
	  {
            size_t keyLen = key.size();
            size_t rows = (ciphertext.size() + keyLen - 1) / keyLen;
            result.resize(ciphertext.size(), ' ');
            for (size_t i = 0; i < keyLen; ++i) 
	    {
                for (size_t j = 0; j < rows; ++j) 
		{
                    if (j * keyLen + i < ciphertext.size()) 
		    {
                        result[j * keyLen + i] = ciphertext[i * rows + j];
                    }
                }
            }

            break;
          }

          default:
              throw std::invalid_argument("Unsupported encryption algorithm");
       }

       return result;
    }
}
