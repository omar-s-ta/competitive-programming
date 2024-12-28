#ifndef ADHOC_UTILS
#define ADHOC_UTILS

template<typename T>
std::pair<T, T> minimum_and_maximum(const std::vector<T>& v) {
  T _min = std::numeric_limits<T>::max();
  T _max = std::numeric_limits<T>::lowest();
  for (const T& vi : v) {
    _min = std::min(vi, _min);
    _max = std::max(vi, _max);
  }
  return { _min, _max };
}

#endif
