#ifndef RADIX_SORT_HPP
#define RADIX_SORT_HPP

#include "adhoc_utils.hpp"

/**
 * References:
 *   - https://developer.download.nvidia.com/video/gputechconf/gtc/2020/presentations/s21572-a-faster-radix-sort-implementation.pdf
 *   - https://github.com/thrust/cub/tree/397357e9aca61f244b0aed2e77efca25f8a95d74/cub/block
 *   - https://github.com/nealwu/competitive-programming/blob/master/miscellaneous/radix_sort.cc
 */

inline int log_two_approximate(const uint64_t n) {
  if (n == 0) return 0;
  // get the most-significant-bit
  return 64 - std::countl_zero(n);
}

template<typename T>
void count_sort(const int bits, const int bits_so_far, const T _min, std::vector<T>& buffer, const std::vector<T>& to_sort) {
  const int bitmask = (1 << bits) - 1;
  std::vector<int> pos((1 << bits) + 1, 0);
  for (const T& elem : to_sort) {
    T key = elem - _min;
    const int bucket = int(key >> bits_so_far & bitmask);
    pos[bucket + 1] += 1;
  }
  for (int i = 1; i <= 1 << bits; i++) {
    pos[i] += pos[i - 1];
  }
  for (const T& elem : to_sort) {
    T key = elem - _min;
    const int bucket = int(key >> bits_so_far & bitmask);
    buffer[pos[bucket]] = elem;
    pos[bucket] += 1;
  }
}

template<typename T>
void radix_sort(std::vector<T>& to_sort, const int bits_per_pass = 10) {
  if (to_sort.empty()) {
    return;
  }
  auto [_min, _max] = minimum_and_maximum(to_sort);
  // resembles count_sort [L-R+1] for freq table.
  // max number of bits to cover in each radix sort pass
  int keys_range_bits = log_two_approximate(_max - _min);
  // same as (key_range_bits / bits_per_pass), adding (bits_per_pass / 2) before division is a technique
  // known as rounding to the nearest integer, ensuring that any fractional pass is accounted
  // for by rounding up when necessary to smooth out the number of bits for each pass;
  // e.g., instead of 10 bits, 10 bits, 10 bits, 2 bits, we would rather do 11 bits, 11 bits, 10 bits.
  int passes = std::max((keys_range_bits + bits_per_pass / 2) / bits_per_pass, 1);

  std::vector<T> buffer(to_sort.size());
  int bits_so_far = 0;
  for (int pass = 0; pass < passes; pass++) {
    // add `pass` before division to ensure a balanced distribution of bits
    // across all passes, to distribute any remainder bits evenly over the passes.
    const int bits = (keys_range_bits + pass) / passes;
    count_sort(bits, bits_so_far, _min, buffer, to_sort);
    to_sort.swap(buffer);
    bits_so_far += bits;
  }
}

#endif