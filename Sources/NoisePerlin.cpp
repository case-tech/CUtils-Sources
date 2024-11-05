#include "NoisePerlin.hpp"

namespace CUtils
{
    NoisePerlin::NoisePerlin(unsigned int seed) 
    {
        permutation.resize(PERM_SIZE * 2);
        for (int i = 0; i < PERM_SIZE; ++i) 
        {
            permutation[i] = i;
        }

        if (seed > 0) 
        {
            srand(seed);
            for (int i = PERM_SIZE - 1; i > 0; --i) 
            {
                int j = rand() % (i + 1);
                std::swap(permutation[i], permutation[j]);
            }
        }

        for (int i = 0; i < PERM_SIZE; ++i) 
        {
            permutation[i + PERM_SIZE] = permutation[i];
        }
    }

    double NoisePerlin::Fade(double t) const 
    {
        return t * t * t * (t * (t * 6 - 15) + 10);
    }

    double NoisePerlin::Lerp(double t, double a, double b) const 
    {
        return a + t * (b - a);
    }

    double NoisePerlin::Grad(int hash, double x, double y) const 
    {
        int h = hash & 3; 
        double u = h < 2 ? x : y; 
        double v = h < 2 ? y : x; 

        return ((h & 1) ? -u : u) + ((h & 2) ? -v : v); 
    }

    double NoisePerlin::Noise(double x, double y) const 
    {
        int xi = static_cast<int>(std::floor(x)) & 255;
        int yi = static_cast<int>(std::floor(y)) & 255;

        double xf = x - std::floor(x);
        double yf = y - std::floor(y);

        double u = Fade(xf);
        double v = Fade(yf);

        int aa = permutation[permutation[xi] + yi];
        int ab = permutation[permutation[xi] + yi + 1];
        int ba = permutation[permutation[xi + 1] + yi];
        int bb = permutation[permutation[xi + 1] + yi + 1];

        double x1 = Lerp(u, Grad(permutation[aa], xf, yf),
            Grad(permutation[ba], xf - 1, yf));
        double x2 = Lerp(u, Grad(permutation[ab], xf, yf - 1),
            Grad(permutation[bb], xf - 1, yf - 1));

        return (Lerp(v, x1, x2) + 1.0) / 2.0; 
    }
}