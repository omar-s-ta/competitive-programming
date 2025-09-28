#ifndef IO_H
#define IO_H

#include <iostream>
#include <vector>
#include <deque>
#include <array>
#include <cstdio>
#include <utility>
#include <cassert>
#include <cstring>

namespace io {

  template<typename T>
  inline std::istream& operator>>(std::istream& in, std::vector<T>& ts) {
    for (T& t : ts) in >> t;
    return in;
  }
  template<typename T>
  inline std::ostream& operator<<(std::ostream& out, const std::vector<T>& ts) {
    const std::size_t n = ts.size();
    for (std::size_t i = 0; i < n; i++) {
      if (i > 0) out << ' ';
      out << ts[i];
    }
    return out;
  }

  template<typename T>
  inline std::istream& operator>>(std::istream& in, std::deque<T>& ts) {
    for (T& t : ts) in >> t;
    return in;
  }
  template<typename T>
  inline std::ostream& operator<<(std::ostream& out, const std::deque<T>& ts) {
    const std::size_t n = ts.size();
    for (std::size_t i = 0; i < n; i++) {
      if (i > 0) out << ' ';
      out << ts[i];
    }
    return out;
  }

  template<typename T, std::size_t _t_size>
  inline std::istream& operator>>(std::istream& in, std::array<T, _t_size>& ts) {
    for (T& t : ts) in >> t;
    return in;
  }
  template<typename T, std::size_t _t_size>
  inline std::ostream& operator<<(std::ostream& out, const std::array<T, _t_size>& ts) {
    for (std::size_t i = 0; i < _t_size; i++) {
      if (i > 0) out << ' ';
      out << ts[i];
    }
    return out;
  }

  template<typename U, typename V>
  std::istream& operator>>(std::istream& in, std::pair<U, V>& p) { return in >> p.first >> p.second; }
  template<typename U, typename V>
  std::ostream& operator<<(std::ostream& out, const std::pair<U, V>& p) { return out << p.first << ' ' << p.second; }

#if __cplusplus >= 201703L
  template<typename... Ts>
  inline void std_read(std::istream& in, Ts&... ts) {
    (in >> ... >> ts);
  }
#endif
}

#endif
