#ifndef BIT_UTILS
#define BIT_UTILS

/**
 * A wrapper around any integral value T for bitwise operations.
 * Can iterate over all values from 0 to (2^n)-1 for `bit_mask<> m(n)`.
 *
 * @tparam T: any integral type
 */
template<typename T = int>
struct bit_mask {
  static_assert(std::is_integral<T>::value, "not integral");

  T value;

  explicit bit_mask(const T _value): value(_value) {}

  inline void set(const int at) {
    value |= (1 << at);
  }
  inline void clear(const int at) {
    value &= ~(1 << at);
  }
  inline void toggle(const int at) {
    value ^= (1 << at);
  }

  inline void clear_least_significant_one() {
    value &= (value - 1);
  }
  inline void set_least_significant_zero() {
    value |= (value + 1);
  }
  inline void clear_least_significant_consecutive_ones() {
    value &= (value + 1);
  }
  inline void set_least_significant_consecutive_zeros() {
    value |= (value - 1);
  }

  inline bool is_set(const int at) const {
    return (value & (1 << at)) != 0;
  }
  inline bool is_power_of_two() const {
    return (value & (value - 1)) == 0;
  }
  inline T least_significant() const {
    return value & -value;
  }
  inline int bit_count() const {
    return bit_count(value);
  }
  inline int low_bit() const {
    return low_bit(value);
  }
  inline int top_bit() const {
    return top_bit(value);
  }

  std::string to_string() const {
    return std::bitset<64>(value).to_string();
  }

  struct iterator {
    T mask;

    explicit iterator(T _mask): mask(_mask) {}

    bit_mask<T> operator*() const {
      return bit_mask<T>(mask);
    }
    iterator& operator++() {
      mask += 1;
      return *this;
    }
    bool operator != (const iterator& other) const { return mask != other.mask; }
  };

  iterator begin() const { return iterator(0); }
  iterator end() const { return iterator(1 << value); }

private:
  inline int bit_count(const T seq) const {
    return seq == 0 ? 0 : 1 + bit_count(seq & (seq - 1));
  }

  // (0, 1, 2, 3, 4) -> (-1, 0, 1, 1, 2)
  inline int top_bit(int x)      const { return (x == 0 ? -1 : 31 - __builtin_clz(x)); }
  inline int top_bit(uint32_t x) const { return (x == 0 ? -1 : 31 - __builtin_clz(x)); }
  inline int top_bit(int64_t x)  const { return (x == 0 ? -1 : 63 - __builtin_clzll(x)); }
  inline int top_bit(uint64_t x) const { return (x == 0 ? -1 : 63 - __builtin_clzll(x)); }

  // (0, 1, 2, 3, 4) -> (-1, 0, 1, 0, 2)
  inline int low_bit(int x)      const { return (x == 0 ? -1 : __builtin_ctz(x)); }
  inline int low_bit(uint32_t x) const { return (x == 0 ? -1 : __builtin_ctz(x)); }
  inline int low_bit(int64_t x)  const { return (x == 0 ? -1 : __builtin_ctzll(x)); }
  inline int low_bit(uint64_t x) const { return (x == 0 ? -1 : __builtin_ctzll(x)); }
};

/**
 * To iterate over all subsets provided by 1's position of the binary representation.
 * @tparam T: any integral type
 */
template<typename T>
struct bit_subset {
  bit_mask<T> mask;

  explicit bit_subset(const T s): mask(s) {}
  explicit bit_subset(const bit_mask<T>& m): mask(m) {}

  struct iterator {
    T mask;
    T subset;

    explicit iterator(T _mask): mask(_mask), subset(_mask) {}

    bit_mask<T> operator*() const {
      return bit_mask<T>(subset);
    }
    iterator& operator++() {
      subset = (mask & (subset - 1));
      return *this;
    }
    bool operator != (const iterator&) const { return subset != 0; }
  };

  iterator begin() const { return iterator(mask.value); }
  iterator end() const { return iterator(0); }
};

/**
 * To iterate over all the 1's in the binary representation, yielding the 0 based index of the next '1' from
 * right to left.
 * @tparam T: any integral type
 */
template<typename T>
struct on_set_bit {
  bit_mask<T> mask;

  explicit on_set_bit(const T s): mask(s) {}
  explicit on_set_bit(const bit_mask<T>& m): mask(m) {}

  struct iterator {
    T mask;

    explicit iterator(T _mask): mask(_mask) {}

    bit_mask<> operator*() const {
      return bit_mask<>(bit_mask<T>(mask).low_bit());
    }
    iterator& operator++() {
      mask &= (mask - 1);
      return *this;
    }
    bool operator != (const iterator&) const { return mask != 0; }
  };

  iterator begin() const { return iterator(mask.value); }
  iterator end() const { return iterator(0); }
};

#endif
