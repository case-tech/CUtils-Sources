#include "Random.hpp"

namespace CUtils
{
   Random::Random() 
   {
      unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
      generator.seed(seed);
   }
   
   int Random::RandomInt(int min, int max) 
   {
      std::uniform_int_distribution<int> distribution(min, max);
      return distribution(generator);
   }

   double Random::RandomDouble(double min, double max) 
   {
      std::uniform_real_distribution<double> distribution(min, max);
      return distribution(generator);
   } 

   double Random::NormalDouble(double mean, double stddev) 
   {
      std::normal_distribution<double> distribution(mean, stddev);
      return distribution(generator);
   }
   
   int Random::BinomialInt(int t, double p) 
   {
      std::binomial_distribution<int> distribution(t, p);
      return distribution(generator);
   }

   bool Random::BernoulliBool(double p) 
   {
      std::bernoulli_distribution distribution(p);
      return distribution(generator);
   }

   int Random::PoissonInt(double mean) 
   {
      std::poisson_distribution<int> distribution(mean);
      return distribution(generator);
   }
}
