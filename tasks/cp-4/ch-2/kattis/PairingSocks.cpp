#include <algorithm>
#include <array>
#include <deque>
#include <iostream>
#include <stack>
#include <string>
#include <vector>

namespace io {

template <typename T>
inline std::istream& operator>>(std::istream& in, std::vector<T>& ts) {
  for (T& t : ts) in >> t;
  return in;
}
template <typename T>
inline std::ostream& operator<<(std::ostream& out, const std::vector<T>& ts) {
  const std::size_t n = ts.size();
  for (std::size_t i = 0; i < n; i++) {
    if (i > 0) out << ' ';
    out << ts[i];
  }
  return out;
}

template <typename T>
inline std::istream& operator>>(std::istream& in, std::deque<T>& ts) {
  for (T& t : ts) in >> t;
  return in;
}
template <typename T>
inline std::ostream& operator<<(std::ostream& out, const std::deque<T>& ts) {
  const std::size_t n = ts.size();
  for (std::size_t i = 0; i < n; i++) {
    if (i > 0) out << ' ';
    out << ts[i];
  }
  return out;
}

template <typename T, std::size_t _t_size>
inline std::istream& operator>>(std::istream& in, std::array<T, _t_size>& ts) {
  for (T& t : ts) in >> t;
  return in;
}
template <typename T, std::size_t _t_size>
inline std::ostream& operator<<(std::ostream& out, const std::array<T, _t_size>& ts) {
  for (std::size_t i = 0; i < _t_size; i++) {
    if (i > 0) out << ' ';
    out << ts[i];
  }
  return out;
}

template <typename U, typename V>
std::istream& operator>>(std::istream& in, std::pair<U, V>& p) {
  return in >> p.first >> p.second;
}
template <typename U, typename V>
std::ostream& operator<<(std::ostream& out, const std::pair<U, V>& p) {
  return out << p.first << ' ' << p.second;
}

#if __cplusplus >= 201703L
template <typename... Ts>
inline void std_read(std::istream& in, Ts&... ts) {
  (in >> ... >> ts);
}
#endif

template <typename T>
inline void std_print(std::ostream& out, T&& t) {
  out << t;
}
template <typename H, typename... T>
inline void std_print(std::ostream& out, H&& h, T&&... t) {
  std_print(out, h);
  out << '\n';
  std_print(out, t...);
  if (sizeof...(t) == 1) out << '\n';
}

inline void delim_print(std::ostream& out, const char*, const char c) { out << c; }
inline void delim_print(std::ostream& out, const char*, const int8_t i) { out << i; }
inline void delim_print(std::ostream& out, const char*, const uint8_t i) { out << i; }
inline void delim_print(std::ostream& out, const char*, const int16_t i) { out << i; }
inline void delim_print(std::ostream& out, const char*, const uint16_t i) { out << i; }
inline void delim_print(std::ostream& out, const char*, const int i) { out << i; }
inline void delim_print(std::ostream& out, const char*, const uint32_t i) { out << i; }
inline void delim_print(std::ostream& out, const char*, const int64_t i) { out << i; }
inline void delim_print(std::ostream& out, const char*, const uint64_t i) { out << i; }
inline void delim_print(std::ostream& out, const char*, const double d) { out << d; }
inline void delim_print(std::ostream& out, const char*, const long double d) { out << d; }
inline void delim_print(std::ostream& out, const char*, const float f) { out << f; }
inline void delim_print(std::ostream& out, const char*, const std::string& s) { out << s; }
template <typename T>
inline void delim_print(std::ostream& out, const char*, T&& t) {
  out << t;
}
template <typename U, typename V>
inline void delim_print(std::ostream& out, const char* delim, const std::pair<U, V>& p) {
  delim_print(out, delim, p.first);
  out << delim;
  delim_print(out, delim, p.second);
}
template <typename T>
inline void delim_print(std::ostream& out, const char* delim, const std::vector<T>& ts) {
  const std::size_t n = ts.size();
  for (std::size_t i = 0; i < n; i++) {
    if (i > 0) out << delim;
    delim_print(out, delim, ts[i]);
  }
}
template <typename T>
inline void delim_print(std::ostream& out, const char* delim, const std::deque<T>& ts) {
  const std::size_t n = ts.size();
  for (std::size_t i = 0; i < n; i++) {
    if (i > 0) out << delim;
    delim_print(out, delim, ts[i]);
  }
}
template <typename H, typename... T>
inline void delim_print(std::ostream& out, const char* delim, H&& h, T&&... t) {
  delim_print(out, delim, h);
  out << delim;
  delim_print(out, delim, t...);
  if (sizeof...(t) == 1) out << '\n';
}
}  // namespace io

using namespace io;

/**
 * Use 2 stacks and simulate the process.
 * Only observation:
 *  - Moving an item from original to auxilary stack,
 *  - Putting it back again to the original stack, without doing any other action is useless.
 */
class problem {
 public:
  void solve() {
    int n;
    in >> n;
    std::vector<int> a(n + n);
    in >> a;
    std::reverse(a.begin(), a.end());
    std::stack<int> stk, aux_stk;
    for (const int& ai : a) {
      stk.emplace(ai);
    }
    int result = 0;
    while (!stk.empty()) {
      const int ai = stk.top();
      if (aux_stk.empty()) {
        stk.pop();
        aux_stk.emplace(ai);
      } else {
        const int aai = aux_stk.top();
        if (aai == ai) {
          stk.pop();
          aux_stk.pop();
        } else {
          stk.pop();
          aux_stk.emplace(ai);
        }
      }
      result += 1;
    }
    if (aux_stk.empty())
      out << result << '\n';
    else
      out << "impossible" << '\n';
  }

  problem(std::istream& in, std::ostream& out) : in(in), out(out) {}

 private:
  std::istream& in;
  std::ostream& out;
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  problem solver(std::cin, std::cout);
  solver.solve();
  return 0;
}
