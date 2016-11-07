#ifndef __UNIQUE_RANDOM_SAMPLER__
#define __UNIQUE_RANDOM_SAMPLER__

#include <vector>
#include <random>

class UniqueRandomSampler{
  std::mt19937 create_rand_engine();
  std::vector<int> make_rand_array_unique(const int size, int rand_min, int rand_max);
};

#endif
