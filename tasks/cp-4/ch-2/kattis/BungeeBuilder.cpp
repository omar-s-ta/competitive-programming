#include <algorithm>
#include <array>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <deque>
#include <iostream>
#include <limits>
#include <optional>
#include <print>
#include <stack>
#include <utility>
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
}  // namespace io

using namespace io;

class problem {
 public:
  void solve_no_stack() {
    int n;
    in >> n;
    std::vector<int> heights(n);
    in >> heights;

    if (n < 3) {
      std::println(out, "0");
      return;
    }

    int left = heights[0];
    int max_so_far = 0;
    int min_so_far = heights[0];
    int result = 0;

    for (int i = 1; i < n; i++) {
      if (left > heights[i]) {
        if (heights[i] < min_so_far) {
          min_so_far = heights[i];
          max_so_far = heights[i];
        } else {
          result = std::max(result, heights[i] - min_so_far);
          max_so_far = std::max(max_so_far, heights[i]);
        }
      } else {
        result = std::max(result, left - min_so_far);
        max_so_far = 0;
        min_so_far = heights[i];
        left = heights[i];
      }
    }

    result = std::max(result, std::min(left, max_so_far) - min_so_far);
    std::println(out, "{}", result);
  }

  /**
   * Use monotoniclly-decreasing stack on the heights
   *   - state_t { index of the mountain, lowest depth reached by this mountaint }
   *   - We are sure next element in the stack is less than or equal previous element.
   *   - Once we find a bigger element (right-wall), we emtpy and compute the best height so far.
   *   - if stack is not emtpy, it means the (left-wall) is higher than the current (right-wall)
   */
  void solve() {
    int n;
    in >> n;
    std::vector<int> heights(n);
    in >> heights;

    if (n < 3) {
      std::println(out, "0");
      return;
    }

    struct state_t {
      int index;
      int depth;
    };

    std::stack<state_t> st;
    int result = 0;

    for (int i = 0; i < n; i++) {
      int valley = heights[i];
      while (!st.empty() && heights[st.top().index] < heights[i]) {
        valley = std::min(valley, st.top().depth);
        result = std::max(result, heights[st.top().index] - valley);
        st.pop();
      }
      if (!st.empty()) {
        st.top().depth = std::min(valley, st.top().depth);
        result = std::max(result, heights[i] - st.top().depth);
      }
      st.emplace(i, heights[i]);
    }

    std::println(out, "{}", result);
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
