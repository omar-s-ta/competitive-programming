#ifndef CONTAINER_UTILS
#define CONTAINER_UTILS

template<typename, typename = void>
struct associative_container : std::false_type {};

template<typename T>
struct associative_container<T, std::void_t<typename T::key_type>> : std::true_type {};

template<typename T>
constexpr bool associative_container_v = associative_container<T>::value;

template<typename T>
constexpr bool linear_container_v = !associative_container_v<T>;

template<typename Container, typename T>
std::enable_if_t<linear_container_v<Container>, void>
operator+=(Container& c, T&& t) { for (auto& cv : c) cv += t; }

template<typename Container, typename T>
std::enable_if_t<linear_container_v<Container>, void>
operator-=(Container& c, T&& t) { for (auto& cv : c) cv -= t; }

template<typename Container, typename T>
std::enable_if_t<linear_container_v<Container>, void>
operator*=(Container& c, T&& t) { for (auto& cv : c) cv *= t; }

template<typename Container, typename T>
std::enable_if_t<linear_container_v<Container>, void>
operator/=(Container& c, T&& t) { for (auto& cv : c) cv /= t; }

template<typename T, typename U>
inline std::vector<T> operator+(const std::vector<T>& ts, U&& u) {
  std::vector<T> uts(ts);
  return uts += u, uts;
}
template<typename T, typename U>
inline std::vector<T> operator-(const std::vector<T>& ts, U&& u) {
  std::vector<T> uts(ts);
  return uts -= u, uts;
}
template<typename T, typename U>
inline std::vector<T> operator*(const std::vector<T>& ts, U&& u) {
  std::vector<T> uts(ts);
  return uts *= u, uts;
}
template<typename T, typename U>
inline std::vector<T> operator/(const std::vector<T>& ts, U&& u) {
  std::vector<T> uts(ts);
  return uts /= u, uts;
}

template<typename U, typename V>
inline void operator+=(std::vector<U>& us, const std::vector<V>& vs) {
  const std::size_t n = std::min(us.size(), vs.size());
  for (std::size_t i = 0; i < n; i++) us[i] += vs[i];
}
template<typename U, typename V>
inline void operator-=(std::vector<U>& us, const std::vector<V>& vs) {
  const std::size_t n = std::min(us.size(), vs.size());
  for (std::size_t i = 0; i < n; i++) us[i] -= vs[i];
}
template<typename U, typename V>
inline void operator*=(std::vector<U>& us, const std::vector<V>& vs) {
  const std::size_t n = std::min(us.size(), vs.size());
  for (std::size_t i = 0; i < n; i++) us[i] *= vs[i];
}
template<typename U, typename V>
inline void operator/=(std::vector<U>& us, const std::vector<V>& vs) {
  const std::size_t n = std::min(us.size(), vs.size());
  for (std::size_t i = 0; i < n; i++) us[i] /= vs[i];
}

template<typename U, typename V>
inline std::vector<U> operator+(const std::vector<U>& us, const std::vector<V>& vs) {
  std::vector<U> res(us);
  return res += vs, res;
}
template<typename U, typename V>
inline std::vector<U> operator-(const std::vector<U>& us, const std::vector<V>& vs) {
  std::vector<U> res(us);
  return res -= vs, res;
}
template<typename U, typename V>
inline std::vector<U> operator*(const std::vector<U>& us, const std::vector<V>& vs) {
  std::vector<U> res(us);
  return res *= vs, res;
}
template<typename U, typename V>
inline std::vector<U> operator/(const std::vector<U>& us, const std::vector<V>& vs) {
  std::vector<U> res(us);
  return res /= vs, res;
}

#endif
