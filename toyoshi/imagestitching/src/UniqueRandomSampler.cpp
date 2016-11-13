#include "UniqueRandomSampler.hpp"


std::mt19937 UniqueRandomSampler::create_rand_engine(){
  std::random_device rnd;
  std::vector<std::uint_least32_t> v(10);// 初期化用ベクタ
  std::generate(v.begin(), v.end(), std::ref(rnd));// ベクタの初期化
  std::seed_seq seed(v.begin(), v.end());
  return std::mt19937(seed);// 乱数エンジン
}

std::vector<int> UniqueRandomSampler::make_rand_array_unique(const int size,
							     int rand_min,
							     int rand_max){
  if(rand_min > rand_max) std::swap(rand_min, rand_max);
  const int max_min_diff = static_cast<int>(rand_max - rand_min + 1);
  if(max_min_diff < size) throw std::runtime_error("引数が異常です");

  std::vector<int> tmp;
  auto engine = create_rand_engine();
  std::uniform_int_distribution<int> distribution(rand_min, rand_max);

  const int make_size = static_cast<int>(size*1.2);

  while(tmp.size() < size){
    while(tmp.size() < make_size) tmp.push_back(distribution(engine));
    std::sort(tmp.begin(), tmp.end());
    auto unique_end = std::unique(tmp.begin(), tmp.end());

    if(size < std::distance(tmp.begin(), unique_end)){
      unique_end = std::next(tmp.begin(), size);
    }
    tmp.erase(unique_end, tmp.end());
  }

  std::shuffle(tmp.begin(), tmp.end(), engine);
  return std::move(tmp);
}
