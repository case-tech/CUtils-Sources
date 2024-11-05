#include "Hashed.hpp"

namespace CUtils
{
    unsigned int Hashed::bswap32(unsigned int value) const 
    {
        return ((value >> 24) & 0xff) | 
            ((value << 8) & 0xff0000) | 
            ((value >> 8) & 0xff00)   | 
            ((value << 24) & 0xff000000); 
    }

    std::string Hashed::sha256(const std::string& str) const 
    {
        const size_t hash_size = 32; 
        unsigned char hash[hash_size];

        const unsigned int k[] = 
        {
            0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
            0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
            0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
            0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
            0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
            0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
            0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
            0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
            0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
            0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
            0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
            0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
            0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
            0x391c0cb3, 0x4ed8aa17, 0x5b9cca4f, 0x682e6ff3,
            0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
            0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
        };

        size_t len = str.size();
        size_t bit_len = len * 8;
        size_t new_len = len + 1 + ((len % 64 < 56) ? (56 - len % 64) : (120 - len % 64));
        std::string padded(new_len, '\0');
        memcpy(&padded[0], str.c_str(), len);
        padded[len] = 0x80; 
        memcpy(&padded[new_len - 8], &bit_len, 8); 

        unsigned int h[] = 
        {
            0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
            0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19
        };

        for (size_t i = 0; i < padded.size() / 64; ++i) 
        {
            unsigned int w[64] = { 0 };
            for (size_t j = 0; j < 16; ++j) 
            {
                memcpy(&w[j], &padded[i * 64 + j * 4], 4);
                w[j] = bswap32(w[j]); 
            }

            for (size_t j = 16; j < 64; ++j) 
            {
                unsigned int s0 = (w[j - 15] >> 7) | (w[j - 15] << (32 - 7));
                s0 ^= (w[j - 15] >> 18) | (w[j - 15] << (32 - 18));
                s0 ^= (w[j - 15] >> 3);
                unsigned int s1 = (w[j - 2] >> 17) | (w[j - 2] << (32 - 17));
                s1 ^= (w[j - 2] >> 19) | (w[j - 2] << (32 - 19));
                s1 ^= (w[j - 2] >> 10);
                w[j] = w[j - 16] + s0 + w[j - 7] + s1;
            }

            unsigned int a = h[0];
            unsigned int b = h[1];
            unsigned int c = h[2];
            unsigned int d = h[3];
            unsigned int e = h[4];
            unsigned int f = h[5];
            unsigned int g = h[6];
            unsigned int h0 = h[7];

            for (size_t j = 0; j < 64; ++j) 
            {
                unsigned int S1 = (e >> 6) | (e << (32 - 6));
                S1 ^= (e >> 11) | (e << (32 - 11));
                S1 ^= (e >> 25) | (e << (32 - 25));
                unsigned int ch = (e & f) ^ (~e & g);
                unsigned int temp1 = h0 + S1 + ch + k[j] + w[j];
                unsigned int S0 = (a >> 2) | (a << (32 - 2));
                S0 ^= (a >> 13) | (a << (32 - 13));
                S0 ^= (a >> 22) | (a << (32 - 22));
                unsigned int maj = (a & b) ^ (a & c) ^ (b & c);
                unsigned int temp2 = S0 + maj;

                h0 = g;
                g = f;
                f = e;
                e = d + temp1;
                d = c;
                c = b;
                b = a;
                a = temp1 + temp2;
            }

            h[0] += a;
            h[1] += b;
            h[2] += c;
            h[3] += d;
            h[4] += e;
            h[5] += f;
            h[6] += g;
            h[7] += h0;
        }

        std::ostringstream result;
        for (size_t i = 0; i < 8; ++i) 
        {
            result << std::setw(8) << std::setfill('0') << std::hex << bswap32(h[i]);
        }

        return result.str();
    }

    void Hashed::HashAndSave(const std::string& text, const std::string& filename) 
    {
        std::string hash = sha256(text);
        std::ofstream ofs(filename + ".hash");
        if (!ofs) 
        {
            throw std::runtime_error("Cannot open file for writing: " + filename + ".hash");
        }
        ofs << hash;
        ofs.close();
    }

    std::string Hashed::ReadHashFromFile(const std::string& filename) const 
    {
        std::ifstream ifs(filename);
        if (!ifs) 
        {
            throw std::runtime_error("Cannot open file for reading: " + filename);
        }

        std::string hash;
        ifs >> hash;
        ifs.close();
        return hash;
    }

}